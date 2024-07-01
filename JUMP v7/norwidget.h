#ifndef NORWIDGET_H
#define NORWIDGET_H

#include <QWidget>
#include <QTimer>
#include<QSequentialAnimationGroup>
#include<QPropertyAnimation>
#include<QMediaPlayer>
namespace Ui {
class Norwidget;
}

class Norwidget : public QWidget
{
    Q_OBJECT
signals:
    void norbacksignal();
    void stsignal();
public:

    explicit Norwidget(QWidget *parent = nullptr);
    ~Norwidget();

private slots:
    void on_norbackbon_clicked();
    void dealsig();
    void on_NORBON_pressed();
    void deal();
    void deal1();
    void on_NORBON_released();

private:
    Ui::Norwidget *ui;
    int num;
    int si=200;
    QTimer*nortimer;
    QTimer*ditimer;//动态
    QMediaPlayer *music;
    QSequentialAnimationGroup*angroup;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QPropertyAnimation *animation4;
    QPropertyAnimation *animation40;
    QPropertyAnimation *animation41;
};

#endif // NORWIDGET_H
