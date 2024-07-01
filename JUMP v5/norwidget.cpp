#include "norwidget.h"
#include "ui_norwidget.h"
#include"mythread.h"
#include<QDebug>
#include<QKeyEvent>
#include<QThread>
#include<QTime>
#include<QTextEdit>
#include<QRect>
#include<QEasingCurve>
#include<QPropertyAnimation>
#include<QMatrix>
#include<QMovie>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QParallelAnimationGroup>
static int i1=0;
static int score=0;
Norwidget::Norwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Norwidget)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);
    this->setWindowTitle("正常模式");
    score=0;
    nortimer=new QTimer(this);
    connect(nortimer,&QTimer::timeout,
            [=]()
            {
                i1++;
                ui->lcdNumber->display(i1);
            }
            );
    ui->lcdNumber->hide();
    ui->norlabel->hide();
    ui->norobj1->move(30,50);
    ui->norobj1->resize(200,200);
    QSequentialAnimationGroup*show1=new QSequentialAnimationGroup(this);
    animation41 = new QPropertyAnimation(ui->norobj1, "geometry");
          animation41->setDuration(1000);
          animation41->setStartValue(QRect(30,50, 200, 200));
          animation41->setEndValue(QRect(30,250, 200,200));
          animation41->setEasingCurve(QEasingCurve::OutElastic);
    ui->norlabel->show();
    animation40 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation40->setDuration(1000);
          animation40->setStartValue(QRect(100,0, si/2,si));
          animation40->setEndValue(QRect(100,150, si/2,si));
          animation40->setEasingCurve(QEasingCurve::OutElastic);


          show1->addAnimation(animation41);
          show1->addAnimation(animation40);
          show1->start();
    connect(this,&Norwidget::stsignal,this,&Norwidget::dealsig);
    emit stsignal();
}

Norwidget::~Norwidget()
{
    delete ui;
}

void Norwidget::on_norbackbon_clicked()
{
    this->close();
    emit norbacksignal();
}

void Norwidget::on_NORBON_pressed()
{
    nortimer->start(3);
    ui->norlabel->resize(si/2,si);

    //压缩动画
     QPropertyAnimation*animation11 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation11->setDuration(500);
          animation11->setStartValue(QRect(100,150, si/2, si));
          animation11->setEndValue(QRect(100, 180, si/2, si));
          animation11->setEasingCurve(QEasingCurve::Linear);
     QPropertyAnimation*animation12 = new QPropertyAnimation(ui->norobj1, "geometry");
          animation12->setDuration(500);
          animation12->setStartValue(QRect(30,250, 200, 200));
          animation12->setEndValue(QRect(30, 280, 200, 170));
          animation12->setEasingCurve(QEasingCurve::Linear);
     QParallelAnimationGroup*group=new QParallelAnimationGroup(this);
     group->addAnimation(animation11);
     group->addAnimation(animation12);
     group->start();
}

void Norwidget::on_NORBON_released()
{
    nortimer->stop();
          animation1 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation1->setDuration(200);
          animation1->setStartValue(QRect(100,180, si/2, si));
          animation1->setEndValue(QRect(100+i1/2, 50, si/2, si));
          animation1->setEasingCurve(QEasingCurve::OutQuart);
          animation2 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation2->setDuration(200);
          animation2->setStartValue(QRect(100+i1/2, 50, si/2, si));
          animation2->setEasingCurve(QEasingCurve::OutQuart);

          animation3 = new QPropertyAnimation(ui->norlabel, "geometry");
                animation3->setDuration(500);
                animation3->setStartValue(QRect(100+i1, 150, si/2, si));
                animation3->setEndValue(QRect(100,150,si/2,si));
                animation3->setEasingCurve(QEasingCurve::Linear);
          QPropertyAnimation* animation31 = new QPropertyAnimation(ui->norobj2, "geometry");
                animation31->setDuration(500);
                animation31->setStartValue(QRect(50+num, 250, 200, 200));
                animation31->setEndValue(QRect(30,250,200,200));
                animation31->setEasingCurve(QEasingCurve::Linear);
          QPropertyAnimation* animation32 = new QPropertyAnimation(ui->norobj1, "geometry");
                animation32->setDuration(500);
                animation32->setStartValue(QRect(30, 250, 200, 200));
                animation32->setEndValue(QRect(-1000,250,200,200));
                animation32->setEasingCurve(QEasingCurve::Linear);
          QParallelAnimationGroup*group3=new QParallelAnimationGroup(this);
          group3->addAnimation(animation3);
          group3->addAnimation(animation31);
          group3->addAnimation(animation32);

    angroup=new QSequentialAnimationGroup(this);
    angroup->addAnimation(animation1);
    angroup->addAnimation(animation2);
    QPropertyAnimation*animation13 = new QPropertyAnimation(ui->norobj1, "geometry");
         animation13->setDuration(500);
         animation13->setStartValue(QRect(30,280, 200, 170));
         animation13->setEndValue(QRect(30, 250, 200, 200));
         animation13->setEasingCurve(QEasingCurve::Linear);
         animation13->start();
    //成功
    if(i1<=num+80&&i1>=num-20)
    {
        animation2->setEndValue(QRect(100+i1,150,si/2,si));
        angroup->addAnimation(group3);
        angroup->start();
        Mythread*northread=new Mythread(this);
        northread->start();
        connect(northread,&Mythread::isDone,this,&Norwidget::deal);
    }
    //失败
    else{
        if(i1>num+80)animation2->setEndValue(QRect(1500,200,si/2,si));
        if(i1<num-20)animation2->setEndValue(QRect(num,1000,si/2,si));
        angroup->removeAnimation(group3);
        angroup->start();
        Mythread*northread1=new Mythread(this);
        northread1->start();
        connect(northread1,&Mythread::isDone,this,&Norwidget::deal1);
    }
}
void Norwidget::deal1(){
     on_norbackbon_clicked();
}
void Norwidget::dealsig()
{
    i1=0;
    ui->lcdNumber->display(i1);
    ui->norobj1->move(30,250);
    ui->score->display(score);
    score++;
    qsrand(QTime(num%21,num%13,num%50).secsTo(QTime::currentTime()));
    while((num=qrand()%600)<150);
    QString str=QString::number(num-20);str+=" ";str+=QString::number(num+80);
    //qDebug()<<str;
    ui->norobj2->move(50+num,50);
    ui->norobj2->resize(200,200);
    ui->norobj2->show();
    animation4 = new QPropertyAnimation(ui->norobj2, "geometry");
    {
        animation4->setDuration(1000);
        animation4->setStartValue(QRect(50+num,50, 200, 200));
        animation4->setEndValue(QRect(50+num,250, 200,200));
        animation4->setEasingCurve(QEasingCurve::OutElastic);
    }
        animation4->start();
}
void Norwidget::deal(){
    emit stsignal();
}
