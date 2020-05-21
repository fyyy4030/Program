#ifndef VIEWMODEL_H
#define VIEWMODEL_H


#include "Kit.h"
#include "PDFkit.h"
#include "ViewState.h"
#include "SingleContinuousState.h"
#include <QWidget>

class ChildViewer;
class DocWidget;

class ViewModel
{
public:
    ViewModel(ChildViewer* ChildViewer);
    ~ViewModel();

public:
    ChildViewer*         m_ChildViewer;    //子窗口
    Kit*                 m_kit;            //接口

private:
    ViewState*             m_ViewState;    //显示
    double                m_DocMultiple;

public:
    //总页数
    int GetPageCount() { return m_kit->GetPageCount(); }
    //页面真实大小
    QSize GetActruallyPageSize(int nPageNum) { return m_kit->GetActruallyPageSize(nPageNum); }
    //页面图片
    QImage GetActruallyPageImage(int nPageNum) { return m_kit->GetActruallyPageImage(nPageNum); }
    //缩放后大小
    QSize GetPageSize(int nPageNum) { return m_kit->GetPageSize(nPageNum); }
    //缩放后图片
    QImage GetPageImage(int nPageNum) { return m_kit->GetPageImage(nPageNum); }
    //目录
    QDomDocument* GetTOC() {return m_kit->GetTOC(); }

public:
    //获取总页高
    int GetActruallyPageHighCount();
    int GetPageHighCount();
    //获取宽度
    int GetActruallyMaxPageWidth();
    //获取最大宽度
    int GetMaxPageWidth();
    //获取当前页码
    int GetCurPageNum() { return m_ViewState->GetCurPageNum();}
    //跳转
    void GotoPage(int nPageNum) { return m_ViewState->GotoPage(nPageNum);}

public:
    ChildViewer* GetChildViewer() { return m_ChildViewer; }
    //获取缩放倍数
    void SetDocMultiple(double docMultiple);

public:
    //加载页面
    void RenderPages(QPainter* paint);
};

#endif // VIEWMODEL_H
