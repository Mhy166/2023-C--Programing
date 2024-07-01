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

    //计时窗口
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle("跳一跳小程序");
    this->resize(1000,1000);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);

    //ui->label->hide();


    ui->rebonlabel->hide();
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
    //ui->widget->setStyleSheet("QWidget{background-color:rgb(206, 210, 221)};");
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
  ui->label->move(100,0);
  ui->label->show();
  ui->label->resize(si/2,si);
  ui->label->show();
  animation40 = new QPropertyAnimation(ui->label, "geometry");
        animation40->setDuration(1000);
        animation40->setStartValue(QRect(100,0, si/2,si));
        animation40->setEndValue(QRect(100,150, si/2,si));
        animation40->setEasingCurve(QEasingCurve::OutElastic);
  animation40->start();
}



void Widget::dealdone()
{
    qsrand(QTime(num%21,num%13,num%50).secsTo(QTime::currentTime()));
    while((num=qrand()%600)<150);
    QString str=QString::number(num);str+=" ";str+=QString::number(num+ran);
    ui->changebutton->setText(str);
    ui->startbon->show();

    ui->obj2label->move(30+num+ran/2,50);
    ui->obj2label->resize(200,200);
    ui->obj2label->show();
    animation4 = new QPropertyAnimation(ui->obj2label, "geometry");
    {
        animation4->setDuration(1000);
        animation4->setStartValue(QRect(30+num+ran/2,50, 200, 200));
        animation4->setEndValue(QRect(30+num+ran/2,250, 200,200));
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
          animation1->setStartValue(QRect(100,150, si/2, si));
          animation1->setEndValue(QRect(100+i/2, 50, si/2, si));
          animation1->setEasingCurve(QEasingCurve::OutQuart);
    animation2 = new QPropertyAnimation(ui->label, "geometry");
          animation2->setDuration(500);
          animation2->setStartValue(QRect(100+i/2, 50, si/2, si));
          animation2->setEasingCurve(QEasingCurve::OutQuart);
    animation3 = new QPropertyAnimation(ui->label, "geometry");
          animation3->setDuration(1000);
          animation3->setStartValue(QRect(100+i, 150, si/2, si));
          animation3->setEndValue(QRect(100,150,si/2,si));
          animation3->setEasingCurve(QEasingCurve::Linear);
    angroup=new QSequentialAnimationGroup(this);
    angroup->addAnimation(animation1);
    angroup->addAnimation(animation2);
    //成功
    if(num<=i&&i<=num+ran)
    {
        value+=add;
        animation2->setEndValue(QRect(100+i,150,si/2,si));
        //angroup->addAnimation(animation3);
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
        animation2->setEndValue(QRect(100+i,500,si/2,si));
        angroup->removeAnimation(animation3);
        angroup->start();
        ui->changebutton->hide();
    }

}

void Widget::on_changebutton_clicked()
{
    thread->start();
    i=0;
    ui->lcdNumber->display(i);

}

//难度按钮
void Widget::on_eazy_clicked()
{
    ui->changebutton->show();
    k=10;
    ran=50;
    add=34;
    ui->level->hide();
}
void Widget::on_hard_clicked()
{
    ui->changebutton->show();
    k=8;
    ran=50;
    add=20;
    ui->level->hide();
}
void Widget::on_insane_clicked()
{
    ui->changebutton->show();
    k=5;
    ran=50;
    add=20;
    ui->level->hide();
}
void Widget::on_demon_clicked()
{
    ui->changebutton->show();
    k=1;
    ran=50;
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
