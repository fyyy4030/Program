#include "ViewModel.h"
#include "ChildViewer.h"


ViewModel::ViewModel(ChildViewer* ChildViewer) : m_ChildViewer(ChildViewer), m_kit(NULL)
{
    //初始化并获取文件名
    m_kit = new PDFkit();
    QString strFileName = m_ChildViewer->getFileName();
    m_kit->SetFileName(strFileName);
    m_kit->Init();
    m_ViewState = new SingleContinuousState(m_ChildViewer);

}

ViewModel::~ViewModel()
{
}

int ViewModel::GetActruallyPageHighCount()
{
    int nPageHighCount = 0;
    int nPageCount = GetPageCount();
    for (int i = 0; i < nPageCount; i++)
        //获取总页高
        nPageHighCount += (GetActruallyPageSize(i).height() + 8);

    return nPageHighCount;
}

int ViewModel::GetPageHighCount()
{
    int nPageHighCount = 0;
    int nPageCount = GetPageCount();
    for (int i =0; i < nPageCount; i++)
        //缩放后总页高
        nPageHighCount += (GetPageSize(i).height() + 8);

    return nPageHighCount;
}

int ViewModel::GetActruallyMaxPageWidth()
{
    //下边这个函数可以优化，先完成功能吧。
    int nMaxPageWidth = -1;
    for(int i = 0; i < GetPageCount(); i++)
        if (nMaxPageWidth < GetActruallyPageSize(i).width())
            //页宽
            nMaxPageWidth = GetActruallyPageSize(i).width();

    return nMaxPageWidth;
}

int ViewModel::GetMaxPageWidth()
{
    int nMaxPageWidth = -1;
    for (int i = 0; i < GetPageCount(); i++)
        if (nMaxPageWidth < GetPageSize(i).width())
            //缩放后页宽
            nMaxPageWidth = GetPageSize(i).width();

    return nMaxPageWidth;

}

void ViewModel::SetDocMultiple(double docMultiple)
{
    //缩放后倍数
    m_DocMultiple = docMultiple;
    m_kit->SetDocMultiple(docMultiple);
}

void ViewModel::RenderPages(QPainter *painter)
{
    if (painter == NULL || m_ViewState == NULL)
        return;
    //加载页面
    m_ViewState->RenderPages(painter);
}

