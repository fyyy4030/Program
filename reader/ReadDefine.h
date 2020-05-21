#ifndef READDEFINE
#define READDEFINE
#include <QWidget>
#include <QSplitter>                    //拆分窗口支持
#include <QTabWidget>                    //分页显示支持
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>                    //滚动窗口支持
#include <QScrollBar>                    //滚动条支持
#include <QString>
#include <QImage>
#include <QDomDocument>                    //读取 XML 文件支持
#include <QPainter>                        //绘制支持
#include <QListWidget>                    //列表部件支持
#include <QTimer>                        //计时器
#include <QTreeWidget>                    //树形控件支持
#include "float.h"

//文档状态
enum DocState
{
    SINGLE_CONTINUOUS,
    UNSINGLE_CONTINUOUS,
    DOUBLE_CONTINUOUS,
    UNDOUBLE_CONTINUOUS
};

//用于PDF中TOC的数据结构
typedef struct _TOCInfo
{
public:
    QString strDestination;
    QString strDestinationName;
    QString strExternalFileName;
    bool bIsOpen;
}TOCInfo;

#define DELETE_POINT(p){delete p; p = NULL;}
#define DELETE_ARRAY(p){delete[](p); (p) = NULL;}
#endif // READDEFINE

