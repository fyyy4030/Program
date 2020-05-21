#ifndef SINGLECONTINUOUSSTATE_H
#define SINGLECONTINUOUSSTATE_H


#include <QScrollArea>
#include "ViewState.h"

class SingleContinuousState : public ViewState
{
public:
    SingleContinuousState(IChildViewer* childViewer);
    virtual ~SingleContinuousState();

public:
    virtual void RenderPages(QPainter* paint);    //加载页面
    virtual int GetCurPageNum();                //获取当前页面号
    virtual void GotoPage(int nPageNum);        //跳转

public:
    ViewModel*             m_ViewModel;

private:
    IChildViewer*         m_ChildViewer;

private:
    int GetPageCount() { return m_ChildViewer->getPageCount();}
    QSize GetPageSize(int nPageNum) { return m_ChildViewer->getPageSize(nPageNum);}
    //获取垂直位置
    int GetVScrollPos();
    //获取水平位置
    int GetHScrollPos();
    //页面高度
    int GetPageHeightCount(int nNumPage);
    //判断是否正确位置
    bool GetVPos(int nScrollPos, int& nPageNum, int& nPageVPos);
};

#endif // SINGLECONTINUOUSSTATE_H
