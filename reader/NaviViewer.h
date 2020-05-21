#ifndef NAVIVIEWER_H
#define NAVIVIEWER_H


#include<QWidget>
#include<QSplitter>
#include<QTextEdit>
#include<QTabWidget>
#include<QLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include <QList>

#include "IChildViewer.h"
#include "ThumbnailWidget.h"

class TocTreeItem
{
public:
    explicit TocTreeItem(QString des, TocTreeItem* parentItem = NULL);
    ~TocTreeItem();

    void appendChild(TocTreeItem *child);        //添加
    TocTreeItem *child(int row);                //返回数据
    int childCount() const;                        //计数
    int columnCount() const;
    QString getDescription(int column) const;    //描述
    int row() const;                            //返回行数
    TocTreeItem *parentItem();

private:
    QList<TocTreeItem*>     m_childList;        //孩子列表
    TocTreeItem*             m_parentItem;        //父节点
    QString                 m_description;        //描述
};

class TocTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TocTreeModel(QDomDocument* domdoc, QObject *parent = 0);
    ~TocTreeModel();

    //以下部分参考poppler库，实现对文档信息的读取
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    //返回一个可编辑模型
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    //构造一个无名对象
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    //返回索引
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    //构造索引节点
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    //返回行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    //分析文档
    void parserDom(QDomNode* domNode, TocTreeItem *parent);
    TocTreeItem         *rootItem;
};

class NaviViewer : public QWidget
{
    Q_OBJECT
public:
    NaviViewer(IChildViewer* childviewer);

private:
    IChildViewer* m_IChildViewer;

private:
    QWidget* m_topNBWidget;             //上面的菜单栏
    QTabWidget* m_tabWidget;             //导航栏里边的tab标签
    QWidget* m_OutlineWidget;             //大纲栏
    QTreeWidget* m_OutlineTree;            //大纲树
    QVBoxLayout* m_OutlineLayout;         //大纲树布局
    void ComputerToc(QDomNode* domNode, QTreeWidgetItem* parentWidgetItem);

    QWidget* m_ThumbnailWidget;         //缩略图
    QVBoxLayout* m_ThumbnailLayout;     //缩略图布局

private slots:
    //待实现功能
    void sl_btnClicked();
    void outLineTreeClicked(QTreeWidgetItem*,int);

private:
    //初始化界面
    void InitUI();
    // 初始化目录
    void InitTOC();
    //初始化信号与槽
    void InitConnect();

};

#endif // NAVIVIEWER_H
