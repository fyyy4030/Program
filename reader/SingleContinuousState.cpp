#include "SingleContinuousState.h"

class DocWidget;

SingleContinuousState::SingleContinuousState(IChildViewer* childViewer): m_ChildViewer(childViewer)
{
}

SingleContinuousState::~SingleContinuousState()
{
}

void SingleContinuousState::RenderPages(QPainter *paint)
{
    if (paint == NULL)
        return;

    int nScrollHeight = 0;                 //当前窗口的高度坐标
    int nScrollYFlag = 0;                  //当前坐标（画布）
    nScrollHeight = m_ChildViewer->getScrollArea()->size().height();      //当前绘制的剩余窗口高度
    nScrollYFlag  = GetVScrollPos();
    // 当前绘制的页码
    int nPageNum;
    // 当前页码绘制的起始VPos
    int nPageVPos;
    // 当前页码的图片
    QImage img;
    QImage imageCopy;
    int nXDrawPos = 0;
    while (nScrollHeight > 0)
    {
        GetVPos(nScrollYFlag, nPageNum, nPageVPos);
        // 绘制当前页的高度
        int nRenderHeight = GetPageSize(nPageNum).height() + 8 - nPageVPos;
        imageCopy = m_ChildViewer->getPageImage(nPageNum);
        img = imageCopy.copy(0, nPageVPos, GetPageSize(nPageNum).width(), nRenderHeight);
        //绘制起点设置
        QSize docWidget = m_ChildViewer->getDocWidgetSize();
        nXDrawPos = ((docWidget.width() - GetPageSize(nPageNum).width())) / 2;
        //如果页面大于窗口，则缩小一倍
        if (nXDrawPos < 0)
            nXDrawPos = m_ChildViewer->getScrollArea()->verticalScrollBar()->size().width() / 2;
        paint->drawImage(nXDrawPos, nScrollYFlag, img);
        //高度坐标减少
        nScrollHeight -= img.height();
        //画布增加
        nScrollYFlag += img.height();
    }

}

int SingleContinuousState::GetCurPageNum()
{
    //当前页面位置
    int nCurPagePos = GetVScrollPos() + m_ChildViewer->getDocWidgetSize().height() / 2;
    int nPageCount = GetPageCount();
    for (int i = 0; i < nPageCount; i++)
    {
        //当前页坐标小于页面图像高度，返回当前页
        if (nCurPagePos < m_ChildViewer->getPageSize(i).height())
            return i;
        //否则，减去图像高度
        nCurPagePos = nCurPagePos - GetPageSize(i).height() - 8;
    }
    return 1;
}

void SingleContinuousState::GotoPage(int nPageNum)
{
    //滑动到指定页
    int nPageNumHeight = GetPageHeightCount(nPageNum);
    QScrollBar* pScrollBar = m_ChildViewer->getScrollArea()->verticalScrollBar();
    pScrollBar->setValue(nPageNumHeight);
}

int SingleContinuousState::GetVScrollPos()
{
    //垂直滑动条位置
    QScrollBar* pScrollBar = m_ChildViewer->getScrollArea()->verticalScrollBar();

    return pScrollBar->value();
}

int SingleContinuousState::GetHScrollPos()
{
    //水平滑动条位置
    QScrollBar* pScrollBar = m_ChildViewer->getScrollArea()->horizontalScrollBar();
    return pScrollBar->value();
}

int SingleContinuousState::GetPageHeightCount(int nNumPage)
{
    //获取页面高度
    int nHeight = 0;
    for (int i = 0; i < nNumPage; i++)
        nHeight += m_ChildViewer->getPageSize(i).height() + 8;

    return nHeight;
}

bool SingleContinuousState::GetVPos(int nScrollPos, int &nPageNum, int &nPageVStartPos)
{
    int nPageCount = GetPageCount();
    //获取页面位置
    for (int i = 0; i < nPageCount; i++)
    {
        //当滑动条位置小于页面高度
        if (nScrollPos < (GetPageSize(i).height() + 8)){
            nPageNum = i;
            //页面开始位置等于滑动条位置
            nPageVStartPos = nScrollPos;
            break;
        }
        nScrollPos -= (GetPageSize(i).height() + 8);
    }
    nScrollPos += 8;
    return true;
}
