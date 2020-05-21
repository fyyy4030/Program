#include "ChildViewer.h"

ChildViewer::ChildViewer(IMainViewer* iMainViewer) : m_IMainViewer(iMainViewer),m_docstate(SINGLE_CONTINUOUS),
    m_dCurDocMultiple(1)
{
    // 为了使关闭窗口时都关闭
    setAttribute(Qt::WA_DeleteOnClose);
    //文件名
    m_strFileName = m_IMainViewer->getFileName();
    m_splitterMain = new QSplitter(Qt::Horizontal, this);
    //分界线
    m_splitterMain->setHandleWidth(1);
    //加载界面
    m_ViewModel = new ViewModel(this);
    m_navigationBar = new NaviViewer(this);
    m_pDocWidget = new DocWidget(this);
    m_splitterMain->addWidget(m_navigationBar);
    m_splitterMain->addWidget(m_pDocWidget);
    //设置可伸缩
    m_splitterMain->setStretchFactor(1,1);
    m_splitterMain->setAutoFillBackground(true);
    m_splitterMain->show();

    //绑定主界面工具栏
    m_pDocWidgetScrollBar =  m_pDocWidget->getScrollArea()->verticalScrollBar();
    connect(m_pDocWidgetScrollBar, SIGNAL(valueChanged(int)), this, SLOT(lineEditChange()));

}

//用布局重新写
void ChildViewer::resizeEvent(QResizeEvent *event)
{
    m_splitterMain->resize(this->size());
}


ChildViewer::~ChildViewer()
{
}

void ChildViewer::RefreshWindow()
{
    //刷新
    m_pDocWidget->RefreshWindow();
}

void ChildViewer::ZoomIn()
{
    //每次放大1/4
    m_dCurDocMultiple += 0.25;
    m_dCurDocMultiple = m_dCurDocMultiple > 2 ? 2 : m_dCurDocMultiple;
    m_ViewModel->SetDocMultiple(m_dCurDocMultiple);
}

void ChildViewer::ZoomOut()
{
    //每次缩小1/4
    m_dCurDocMultiple -= 0.25;
    m_dCurDocMultiple = m_dCurDocMultiple < 0.25 ? 0.25 : m_dCurDocMultiple;
    m_ViewModel->SetDocMultiple(m_dCurDocMultiple);
}

void ChildViewer::ZoomReset()
{
    //重置大小
    m_dCurDocMultiple = 1;
    m_ViewModel->SetDocMultiple(1);
}

void ChildViewer::PreviousPage()
{
    //上一张
    int nPageNum = getCurPageNum();
    int nCurPageNum = (nPageNum == 0) ? 0 : (nPageNum - 1);
    m_ViewModel->GotoPage(nCurPageNum);
}

void ChildViewer::NextPage()
{
    //下一张
    int nPageNum = getCurPageNum();
    int nPageCount = getPageCount();
    int nCurPageNum = (nPageNum == nPageCount) ? nPageCount : (nPageNum + 1);
    m_ViewModel->GotoPage(nCurPageNum);
}

void ChildViewer::lineEditChange()
{
    //页码框更新
    int nPageNum = getCurPageNum() + 1;
    QLineEdit* lineEdit = m_IMainViewer->getPageNumLineEdit();
    QString strPageNum = QString::number(nPageNum);
    lineEdit->setText(strPageNum);
}
