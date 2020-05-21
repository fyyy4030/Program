#ifndef CHIILDVIEWER_H
#define CHIILDVIEWER_H

#include "ReadDefine.h"
#include "IChildViewer.h"
#include "NaviViewer.h"
#include "ViewModel.h"
#include "DocWidget.h"
#include "IMainViewer.h"

class ChildViewer : public IChildViewer
{
    Q_OBJECT

public:
    ChildViewer(IMainViewer* iMainViewer);
    ~ChildViewer();

public:
    virtual QString getFileName() { return m_strFileName; }
    virtual QScrollArea* getScrollArea() { return m_pDocWidget->getScrollArea(); }
    virtual int getPageCount() { return m_ViewModel->GetPageCount(); }
    virtual QSize getActruallyPageSize(int nPageNum) { return m_ViewModel->GetActruallyPageSize(nPageNum); }
    virtual QImage getActruallyPageImage(int nPageNum) { return m_ViewModel->GetActruallyPageImage(nPageNum); }
    virtual QSize getPageSize(int nPageNum) { return m_ViewModel->GetPageSize(nPageNum); }
    virtual QImage getPageImage(int nPageNum) { return m_ViewModel->GetPageImage(nPageNum); }
    virtual void RenderPages(QPainter *painter) { m_ViewModel->RenderPages(painter); }
    virtual double getCurDocMultiple(){ return m_dCurDocMultiple; }
    virtual int getActruallyPageHighCount() { return m_ViewModel->GetActruallyPageHighCount();}
    virtual int getPageHighCount() { return m_ViewModel->GetPageHighCount(); }
    virtual int getActruallyMaxPageWidth() { return m_ViewModel->GetActruallyMaxPageWidth(); }
    virtual int getMaxPageWidth() {return m_ViewModel->GetMaxPageWidth(); }
    virtual QSize getDocWidgetSize() { return m_pDocWidget->size(); }
    virtual int getCurPageNum() { return m_ViewModel->GetCurPageNum(); }
    virtual QDomDocument* getTOC() { return m_ViewModel->GetTOC(); }

public:
    void ZoomIn();
    void ZoomOut();
    void ZoomReset();
    void PreviousPage();
    void NextPage();
    void GotoPage(int nPageNum) { m_ViewModel->GotoPage(nPageNum);}

public:
    void resizeEvent(QResizeEvent *event);
    void RefreshWindow();             //刷新界面

private:
    ViewModel* m_ViewModel;
    DocState m_docstate;
    double m_dCurDocMultiple;         //当前文档放大倍数

public:
    IMainViewer* m_IMainViewer;        //主窗口
    QString m_strFileName;
    QSplitter* m_splitterMain;        //分裂窗口
    NaviViewer* m_navigationBar;    //左边导航栏
    DocWidget* m_pDocWidget;        //右边绘制widget
    QScrollBar* m_pDocWidgetScrollBar; //右边绘制widget滚动条，消息回调都用这个

public slots:
    void lineEditChange();

};

#endif // CHIILDVIEWER_H
