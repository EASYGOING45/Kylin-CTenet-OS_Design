#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QWidget>

namespace Ui {
class ProcessManager;
}

class ProcessManager : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessManager(QWidget *parent = nullptr);
    ~ProcessManager();
private:
    //枚举进程
    void enumProcess();

    //获取进程表选中的进程ID
    uint getPid();

    //提升权限
    void upRole();

    //清空进程表
    void clearProcTab();

    //清空DLL表
    void clearDllTab();

signals:
    //刷新进程表
    void refreshProcTab();

private slots:
    void on_btn_CreateProcess_clicked();

    void on_btn_FinishProcess_clicked();

    void on_btn_PauseProcess_clicked();

    void on_btn_ReProcess_clicked();

    void on_btn_ViewDLL_clicked();

    void on_btn_Exit_clicked();

    void on_btn_RefreshProcess_clicked();

    void on_btn_RefreshDLL_clicked();

private:
    Ui::ProcessManager *ui;
};

#endif // PROCESSMANAGER_H
