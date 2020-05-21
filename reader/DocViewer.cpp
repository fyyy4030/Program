#include "DocViewer.h"

DocViewer::DocViewer(IDocWidget* DocWidget) : m_IDocWidget(DocWidget)
{
}

DocViewer::~DocViewer()
{
}

void DocViewer::paintEvent(QPaintEvent *e)
{
    //加载pdf
    QPainter* painter = new QPainter(this);
    m_IDocWidget->RenderPages(painter);
}

