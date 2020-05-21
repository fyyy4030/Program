#include "DocWidget.h"
#include <QVBoxLayout>

DocWidget::DocWidget(IChildViewer* childviewer):m_IChildViewer(childviewer)
{
    //背景色
    setStyleSheet("background-color:gray");
    //绘制滑动条
    m_pScrollArea = new QScrollArea();
    m_pDocViewer = new DocViewer(this);
    //绘制页面
    m_pScrollArea->setWidget(m_pDocViewer);
    //垂直布局
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    layout->addWidget(m_pScrollArea);
    layout->setContentsMargins(1,1,1,1);
    m_pScrollBar = m_pScrollArea->verticalScrollBar();
    m_pScrollArea->setAlignment(Qt::AlignCenter);
}

DocWidget::~DocWidget()
{
}

//让qscroll自动适配页面大小。
void DocWidget::resizeEvent(QResizeEvent* e)
{
    _resize();
}

void DocWidget::RefreshWindow()
{
    update();
    _resize();
}

void DocWidget::_resize()
{
    //上边的逻辑是窗口小于页面大小时做的处理。得加上一个滚动条的大小，这样页面会比较好看。
    if (m_IChildViewer->getMaxPageWidth() > m_pScrollArea->size().width())
        m_pDocViewer->resize(m_IChildViewer->getMaxPageWidth() + m_pScrollBar->size().width(), m_IChildViewer->getPageHighCount());
    else
        m_pDocViewer->resize(m_pScrollArea->size().width() - m_pScrollBar->size().width(), m_IChildViewer->getPageHighCount());
}
