#include "widget.h"
#include "ui_widget.h"
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
 static int i=0;
 static int k=10;
 static int add=20;
 int si=200;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    thread=new Mythread(this);
    connect(this,&Widget::destroyed,this,&Widget::stopthread);
    connect(thread,&Mythread::isDone,this,&Widget::dealdone);

     //背景音乐
     QMediaPlayer *musicback;
     musicback=new QMediaPlayer;
     QMediaPlaylist*list=new QMediaPlaylist;
     list->addMedia(QUrl("qrc:/n/Music/Jump Back.mp3"));
     list->setPlaybackMode(QMediaPlaylist::Loop);
     musicback->setPlaylist(list);
     musicback->setVolume(30);
     musicback->play();


     //计时窗口
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle("跳一跳小程序");
    this->resize(1000,1000);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->rebonlabel->hide();
    ui->readyBon->hide();


    //计时器
    mytimer=new QTimer(this);
    connect(mytimer,&QTimer::timeout,
            [=]()
            {
                i++;
                ui->lcdNumber->display(i);
            }
            );



    //按压按钮
    connect(ui->rebon,&QPushButton::clicked,
    [=]()
    {
        i=0;
        ui->lcdNumber->display(i);
    });
    ui->obj1label->move(30,50);
    ui->obj1label->resize(200,200);
    ui->obj1label->hide();
    ui->label->hide();

}


void Widget::stopthread(){
    thread->quit();
    thread->wait();
}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_startbon_pressed()
{
  mytimer->start(k);
  ui->label->resize(si/2,si);

  //压缩动画
   QPropertyAnimation*animation11 = new QPropertyAnimation(ui->label, "geometry");
        animation11->setDuration(500);
        animation11->setStartValue(QRect(100,150, si/2, si));
        animation11->setEndValue(QRect(100, 180, si/2, si));
        animation11->setEasingCurve(QEasingCurve::Linear);
   QPropertyAnimation*animation12 = new QPropertyAnimation(ui->obj1label, "geometry");
        animation12->setDuration(500);
        animation12->setStartValue(QRect(30,250, 200, 200));
        animation12->setEndValue(QRect(30, 280, 200, 170));
        animation12->setEasingCurve(QEasingCurve::Linear);
   QParallelAnimationGroup*group=new QParallelAnimationGroup(this);
   group->addAnimation(animation11);
   group->addAnimation(animation12);
   group->start();
}



void Widget::dealdone()
{
    qsrand(QTime(num%21,num%13,num%50).secsTo(QTime::currentTime()));
    while((num=qrand()%600)<150);
    QString str=QString::number(num-20);str+=" ";str+=QString::number(num+80);
    ui->changebutton->setText(str);
    ui->startbon->show();
    ui->obj2label->move(50+num,50);
    ui->obj2label->resize(200,200);
    ui->obj2label->show();
    animation4 = new QPropertyAnimation(ui->obj2label, "geometry");
    {
        animation4->setDuration(1000);
        animation4->setStartValue(QRect(50+num,50, 200, 200));
        animation4->setEndValue(QRect(50+num,250, 200,200));
        animation4->setEasingCurve(QEasingCurve::OutElastic);
    }
    animation4->start();

}
void Widget::on_startbon_released()
{
    mytimer->stop();
    ui->startbon->hide();
    ui->label->show();
          animation1 = new QPropertyAnimation(ui->label, "geometry");
          animation1->setDuration(500);
          animation1->setStartValue(QRect(100,180, si/2, si));
          animation1->setEndValue(QRect(100+i/2, 50, si/2, si));
          animation1->setEasingCurve(QEasingCurve::OutQuart);
          animation2 = new QPropertyAnimation(ui->label, "geometry");
          animation2->setDuration(500);
          animation2->setStartValue(QRect(100+i/2, 50, si/2, si));
          animation2->setEasingCurve(QEasingCurve::OutQuart);

          animation3 = new QPropertyAnimation(ui->label, "geometry");
                animation3->setDuration(500);
                animation3->setStartValue(QRect(100+i, 150, si/2, si));
                animation3->setEndValue(QRect(100,150,si/2,si));
                animation3->setEasingCurve(QEasingCurve::Linear);
          QPropertyAnimation* animation31 = new QPropertyAnimation(ui->obj2label, "geometry");
                animation31->setDuration(500);
                animation31->setStartValue(QRect(50+num, 250, 200, 200));
                animation31->setEndValue(QRect(30,250,200,200));
                animation31->setEasingCurve(QEasingCurve::Linear);
          QPropertyAnimation* animation32 = new QPropertyAnimation(ui->obj1label, "geometry");
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
    QPropertyAnimation*animation13 = new QPropertyAnimation(ui->obj1label, "geometry");
         animation13->setDuration(500);
         animation13->setStartValue(QRect(30,280, 200, 170));
         animation13->setEndValue(QRect(30, 250, 200, 200));
         animation13->setEasingCurve(QEasingCurve::Linear);
     animation13->start();
    //成功
    if(i<=num+80&&i>=num-20)
    {
        value+=add;
        animation2->setEndValue(QRect(100+i,150,si/2,si));
        angroup->addAnimation(group3);
        angroup->start();
        ui->changebutton->setText("继续");
        ui->proBar->setValue(value);

        //过关
        if(value>=100)
        {
            ui->stackedWidget_2->setCurrentIndex(2);
        }
    }
    //失败
    else{
        if(i>num+80)animation2->setEndValue(QRect(2000,500,si/2,si));
        if(i<num-20)animation2->setEndValue(QRect(num,500,si/2,si));
        angroup->removeAnimation(group3);
        angroup->start();
        ui->changebutton->hide();
    }

}

void Widget::on_changebutton_clicked()
{
    thread->start();
    i=0;
    ui->lcdNumber->display(i);
    ui->obj1label->move(30,250);
}

//难度按钮
void Widget::on_eazy_clicked()
{
    ui->readyBon->show();
    k=10;
    add=34;
    ui->level->hide();
}
void Widget::on_hard_clicked()
{
    ui->readyBon->show();
    k=8;
    add=20;
    ui->level->hide();
}
void Widget::on_insane_clicked()
{
    ui->readyBon->show();
    k=5;
    add=20;
    ui->level->hide();
}
void Widget::on_demon_clicked()
{
    ui->readyBon->show();
    k=1;
    add=10;
    ui->level->hide();
}
//主菜单按钮  开始
void Widget::on_Mainbutton_clicked()
{
    //初始化
    ui->stackedWidget->setCurrentIndex(0);
    ui->changebutton->setText("给予通关区间");
    ui->level->show();
    ui->label->move(100,150);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->obj2label->hide();
    ui->obj1label->show();
    ui->label->hide();

    //进度条
    ui->proBar->setMinimum(0);
    ui->proBar->setMaximum(100);
    ui->proBar->resize(850,50);
    value=0;
    ui->proBar->setValue(value);
    //第一个平台落地
    animation41 = new QPropertyAnimation(ui->obj1label, "geometry");
          animation41->setDuration(1000);
          animation41->setStartValue(QRect(30,50, 200, 200));
          animation41->setEndValue(QRect(30,250, 200,200));
          animation41->setEasingCurve(QEasingCurve::OutElastic);
          animation41->start();
}
//重置按钮
void Widget::on_rebon_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->rebonlabel->show();
}
//认输按钮
void Widget::on_button_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void Widget::on_OKButton_clicked()
{
    ui->rebonlabel->show();
   if(k==10) ui->eazy->close();
   if(k==8)  ui->hard->close();
   if(k==5)  ui->insane->close();
   //最终局
   if(k==1)
   {
       this->close();return;
   }
   ui->stackedWidget->setCurrentIndex(1);
   OKwidget*w=new OKwidget;
   w->setFixedSize(1000,1000);
   w->show();
}
void Widget::on_OKButton2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->rebonlabel->show();
}

void Widget::on_readyBon_clicked()
{
    ui->readyBon->hide();
    ui->changebutton->show();
    ui->label->show();
    animation40 = new QPropertyAnimation(ui->label, "geometry");
          animation40->setDuration(1000);
          animation40->setStartValue(QRect(100,0, si/2,si));
          animation40->setEndValue(QRect(100,150, si/2,si));
          animation40->setEasingCurve(QEasingCurve::OutElastic);
    animation40->start();
}

void Widget::on_NorBon_clicked()
{
    Norwidget*norwidget;
    norwidget=new Norwidget;
    connect(norwidget,&Norwidget::norbacksignal,this,&Widget::dealback);
    norwidget->show();
    this->hide();
}
void Widget::dealback()
{
    this->show();
}
