#ifndef NORWIDGET_H
#define NORWIDGET_H

#include <QWidget>
#include <QTimer>
#include<QSequentialAnimationGroup>
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include<timerthread.h>
namespace Ui {
class Norwidget;
}

class Norwidget : public QWidget
{
    Q_OBJECT
signals:
    void norbacksignal();
    void stsignal();
    void ti();
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

    void on_ScoButton_clicked();
    void stopthread();
    void dedone(int);
private:
    Ui::Norwidget *ui;
    int num;
    int reward;
    int back;
    int backchange=0;
    timerthread*tithd;
    QTimer*ditimer;//动态
    QTimer*scotimer;
    QMediaPlayer *music1;
    QMediaPlayer *musicst;
    QMediaPlayer *musicde;
    QMediaPlayer *musicce;
    QMediaPlayer *musicla;
    QMediaPlayer *musicji;
    QSequentialAnimationGroup*dynamic;

    QSequentialAnimationGroup*angroup;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QPropertyAnimation *animation4;
    QPropertyAnimation *animation40;
    QPropertyAnimation *animation41;
    QPropertyAnimation* animation61;
     QPropertyAnimation* animation62 ;
      QPropertyAnimation* animation63;
    QSequentialAnimationGroup*scodynamic;
};

#endif // NORWIDGET_H
