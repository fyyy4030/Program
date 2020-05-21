#include "NaviViewer.h"
#include <QProxyStyle>                    //风格样式支持

TocTreeItem::TocTreeItem(QString des, TocTreeItem* parentItem)
{
    //初始化
    m_description = des;
    m_parentItem = parentItem;
    m_childList.clear();
    qDeleteAll(m_childList);
}

TocTreeItem::~TocTreeItem()
{
    qDeleteAll(m_childList);
}

void TocTreeItem::appendChild(TocTreeItem *child)
{
    //添加孩子节点
    m_childList.append(child);
}

TocTreeItem* TocTreeItem::child(int row)
{
    //返回row的数据
    return m_childList.value(row);
}

int TocTreeItem::childCount() const
{
    //返回孩子节点数
    return m_childList.count() > 0 ? m_childList.count() : 0;
}

int TocTreeItem::columnCount() const
{
    return 1;
}

QString TocTreeItem::getDescription(int column) const
{
    //返回描述
    return m_description;
}

int TocTreeItem::row() const
{
    //返回孩子节点
    if (m_parentItem)
        return m_parentItem->m_childList.indexOf(const_cast<TocTreeItem*>(this));//转化常量指针为非常量指针

    return 0;
}
TocTreeItem* TocTreeItem::parentItem()
{
    return m_parentItem;
}

TocTreeModel::TocTreeModel(QDomDocument* domdoc, QObject *parent)
{
    if (domdoc == NULL)
        return;
    //指向第一个孩子节点
    QDomNode domNode = domdoc->firstChild();
    //获取章节名
    rootItem = new TocTreeItem("domNode.toElement().tagName()");
    TocTreeItem* treeItem;
    //获取每个孩子节点的信息
    for(QDomNode childNode = domNode; !childNode.isNull(); childNode = childNode.nextSibling())
    {
        //获取章节名
        QString strDom = childNode.toElement().tagName();
        treeItem = new TocTreeItem(strDom, rootItem);
        //添加
        rootItem->appendChild(treeItem);
        parserDom(&domNode, treeItem);
    }
}

TocTreeModel::~TocTreeModel()
{
    delete rootItem;
}

void TocTreeModel::parserDom(QDomNode* domNode, TocTreeItem* parentItem)
{
    TocTreeItem* treeItem = NULL;
    QString strDom;
    //遍历节点
    for(QDomNode childNode = domNode->firstChild(); !childNode.isNull(); childNode = childNode.nextSibling())
    {
        //获取章节名
        strDom = childNode.toElement().tagName();
        treeItem = new TocTreeItem(strDom, parentItem);
        //添加
        parentItem->appendChild(treeItem);
        parserDom(&childNode, treeItem);
    }

}

int TocTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TocTreeItem*>(parent.internalPointer())->columnCount();            //强制转换并返回列数
    else
        return rootItem->columnCount();
}

int TocTreeModel::rowCount(const QModelIndex &parent) const
{
    TocTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;        //指向根节点
    else
        parentItem = static_cast<TocTreeItem*>(parent.internalPointer());
    //返回孩子节点
    return parentItem->childCount();
}

QVariant TocTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())            //如果无效
        return QVariant();            //构造一个无名对象并返回
    if (role != Qt::DisplayRole)
        return QVariant();
    //强制转换为TocTreeItem型
    TocTreeItem *item = static_cast<TocTreeItem*>(index.internalPointer());
    //返回对象
    return QVariant(item->getDescription(index.column()));
}

Qt::ItemFlags TocTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    //构造索引
    return QAbstractItemModel::flags(index);
}

QVariant TocTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex TocTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();            //无效索引

    TocTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;            //指向根节点
    else
        parentItem = static_cast<TocTreeItem*>(parent.internalPointer());
    //指向第row行的孩子节点
    TocTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);//新建索引
    else
        return QModelIndex();
}

QModelIndex TocTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    //强制转换
    TocTreeItem *childItem = static_cast<TocTreeItem*>(index.internalPointer());
    //指向孩子索引的根
    TocTreeItem *parentItem = childItem->parentItem();
    //如果孩子节点的根是父节点根，无效
    if (parentItem == rootItem)
        return QModelIndex();
    //新建父索引
    return createIndex(parentItem->row(), 0, parentItem);
}

NaviViewer::NaviViewer(IChildViewer* childviewer) : m_IChildViewer(childviewer), m_OutlineTree(NULL)
{
    InitUI();                        //初始化界面
    InitTOC();                        //初始化目录
    InitConnect();                    //初始化链接
}

void NaviViewer::InitUI()
{
    //设置布局
    m_OutlineWidget = new QWidget();
    m_OutlineLayout = new QVBoxLayout();
    m_OutlineWidget->setLayout(m_OutlineLayout);
    m_OutlineLayout->setContentsMargins(1,1,1,1);

    m_ThumbnailWidget = new ThumbnailWidget(m_IChildViewer);
    //添加标签
    m_tabWidget = new QTabWidget();
    m_tabWidget->setTabPosition(QTabWidget::West);
    m_tabWidget->addTab(m_OutlineWidget,"目录");
    m_tabWidget->addTab(m_ThumbnailWidget, "缩略图");

    //垂直分割的布局
    QVBoxLayout* naVLayout = new QVBoxLayout();
    naVLayout->addWidget(m_tabWidget);
    naVLayout->setContentsMargins(1, 1, 1, 1);
    this->setLayout(naVLayout);
}

void NaviViewer::InitTOC()
{
    //获取目录
    QDomDocument* domdoc = m_IChildViewer->getTOC();
    if (domdoc == NULL)
        return;

    m_OutlineTree = new QTreeWidget();
    //设置背景样式
    m_OutlineTree->setStyleSheet( "QTreeView::item:hover{background-color:rgb(0,255,0,50)}"
                               "QTreeView::item:selected{background-color:rgb(255,0,0,100)}");
    //显示目录
    QTreeView* treeView = new QTreeView();
    TocTreeModel* treeModel = new TocTreeModel(domdoc);
    treeView->setModel(treeModel);
    m_OutlineLayout->addWidget(treeView);
}

void NaviViewer::InitConnect()
{
    //信号设置
    if (m_OutlineTree)
        connect(m_OutlineTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(outLineTreeClicked(QTreeWidgetItem*,int)));
}

void NaviViewer::ComputerToc(QDomNode* domNode, QTreeWidgetItem* parentWidgetItem)
{
    QTreeWidgetItem* treeWidgetItem = NULL;
    QString strDom;
    //树状列表
    for(QDomNode childNode = domNode->firstChild(); !childNode.isNull(); childNode = childNode.nextSibling())
    {
        //获取名称
        strDom = childNode.toElement().tagName();
        //存入树状列表
        treeWidgetItem = new QTreeWidgetItem(parentWidgetItem, QStringList(strDom));
        ComputerToc(&childNode, treeWidgetItem);
    }

}

void NaviViewer::sl_btnClicked()
{
    //待增添功能
}

void NaviViewer::outLineTreeClicked(QTreeWidgetItem* item, int n)
{
    //待增添功能
}

