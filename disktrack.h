#ifndef DISKTRACK_H
#define DISKTRACK_H

#include<QMainWindow>
class QGroupBox;
class QTable;
class QRadioButton;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class DiskTrack : public QMainWindow
{
    Q_OBJECT
public:
    explicit DiskTrack(QWidget *parent = nullptr);
    ~DiskTrack();

    //定义内置数据结构磁道DISK
    typedef struct DISK{
        int Next_number;    //下一个磁道号
        int distance;       //移动距离
    }DISK;
    int Now_number; //记录当前磁头的位置

    QVector<DISK> disk,disk_sort;

    void DISK_AscStablesort(QVector<DISK> *vector); //对磁道号按照优先级进行升序排序
    void DISK_DescStablesort(QVector<DISK> *vector);    //降序排序

    void getDiskTable();
    void setDiskTable();

    void FCFS();        //先来先服务算法
    void SSTF();        //最短寻道时间优先算法
    void SCAN();        //扫描算法（SCAN）
    void CSCAN();       //循环扫描算法（CSCAN）
    void setResult();

private:
    void createDiskPage();  //创建页面

    QWidget *diskPage;
    QGroupBox *tableGroupBox;
    QTableWidget *diskTable;

    QGroupBox *algorithmGroupBox;
    QRadioButton *FCFSrbutton;  //先来先服务算法单选按钮
    QRadioButton *SSTFrbutton;  //最短寻道时间优先算法单选按钮
    QRadioButton *SCANrbutton;  //扫描算法单选按钮
    QRadioButton *CSCANrbutton; //循环扫描算法单选按钮
    QGroupBox *orderGroupBox;
    QRadioButton *increaserbutton;  //向磁道号增加方向访问单选按钮
    QRadioButton *decreaserbutton;  //向磁道号减少方向访问单选按钮

    QGroupBox *operationGroupBox;
    QLabel *disknumLabel;          //当前磁道号Label
    QLineEdit *numberEdit;      //当前磁道号
    QPushButton *runButton;      //运行按钮
    QPushButton *InitButton;    //初始化按钮

    QGroupBox *resultGroupBox;
    QLabel *moveLabel;          //移动磁道数
    QLabel *move_averageLabel;  //平均寻道长度
private slots:
    void Initclick();
    void Runclick();
    void setorder_on();
    void setorder_off();
};

#endif // DISKTRACK_H
