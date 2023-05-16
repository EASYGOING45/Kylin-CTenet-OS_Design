#ifndef CHOOSEALGO_H
#define CHOOSEALGO_H

#include <QWidget>

namespace Ui {
class chooseAlgo;
}

class chooseAlgo : public QWidget
{
    Q_OBJECT

public:
    explicit chooseAlgo(QWidget *parent = nullptr);
    ~chooseAlgo();
    Ui::chooseAlgo *ui;
private:
};

#endif // CHOOSEALGO_H
