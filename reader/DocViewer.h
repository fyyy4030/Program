#ifndef DOCVIEWER_H
#define DOCVIEWER_H

#include <QWidget>
#include <QScrollArea>
#include <QPainter>

#include "IChildViewer.h"
#include "ViewModel.h"
#include "IDocWidget.h"

class DocViewer : public QWidget
{

public:
    DocViewer(IDocWidget* DocWidget);
    ~DocViewer();

public:
    QScrollArea*        m_pscrollarea;
    QScrollBar*         m_pScrollBar;
    IDocWidget*         m_IDocWidget;


public:
    //加载pdf
    void paintEvent(QPaintEvent *e);
    //加载滑动条
    QScrollArea* getScroll(){ return m_pscrollarea;}
};

#endif // DOCVIEWER_H
