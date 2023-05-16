#ifndef ADDPROCESS_H
#define ADDPROCESS_H

#include <QWidget>
#include<QRandomGenerator>

namespace Ui {
class AddProcess;
}

class AddProcess : public QWidget
{
    Q_OBJECT

public:
    explicit AddProcess(QWidget *parent = nullptr);
    ~AddProcess();

signals:
    void sendPCB(QString PID,QString status,int priority,int runtime);

private slots:
    void on_btn_add_clicked();

    void on_btn_random_clicked();

    void on_btn_clear_clicked();

private:
    Ui::AddProcess *ui;
};

#endif // ADDPROCESS_H
