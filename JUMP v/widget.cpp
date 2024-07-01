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
 static int i=0;
 static int k=10;
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
    this->resize(1000,500);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->label->hide();
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

//动画
    animation1 = new QPropertyAnimation(ui->label, "geometry");
          animation1->setDuration(300);
          animation1->setStartValue(QRect(50,200, 100, 100));
          animation1->setEndValue(QRect(200, 20, 100, 100));
          animation1->setEasingCurve(QEasingCurve::OutQuart);
    animation2 = new QPropertyAnimation(ui->label, "geometry");
          animation2->setDuration(200);
          animation2->setStartValue(QRect(200, 20, 100, 100));
          animation2->setEasingCurve(QEasingCurve::OutQuart);
    animation3 = new QPropertyAnimation(ui->label, "geometry");
          animation3->setDuration(1000);
          animation3->setStartValue(QRect(350, 200, 100, 100));
          animation3->setEndValue(QRect(50,200,100,100));
          animation3->setEasingCurve(QEasingCurve::Linear);
    angroup=new QSequentialAnimationGroup(this);
    angroup->addAnimation(animation1);
    angroup->addAnimation(animation2);

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
  ui->label->move(50,200);
  ui->label->resize(100,100);
  ui->label->show();
}
void Widget::dealdone()
{
    qsrand(QTime(num%21,num%13,num%50).secsTo(QTime::currentTime()));
    while((num=qrand()%300)<100);
    QString str=QString::number(num);str+=" ";str+=QString::number(ran);
    ui->changebutton->setText(str);
    ui->startbon->show();
}
void Widget::on_startbon_released()
{
    mytimer->stop();
    ui->startbon->hide();
    ui->label->show();
    //过关
    if(num<=i&&i<=num+ran)
    {

        animation2->setEndValue(QRect(350,200,100,100));
        angroup->addAnimation(animation3);
        angroup->start();
        ui->changebutton->setText("继续");
    }
    //失败
    else{
        animation2->setEndValue(QRect(350,900,100,100));
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


void Widget::on_eazy_clicked()
{
    ui->changebutton->show();
    k=20;
    ran=50;
    ui->level->hide();
}
void Widget::on_hard_clicked()
{
    ui->changebutton->show();
    k=10;
    ran=50;
    ui->level->hide();
}

void Widget::on_insane_clicked()
{
    ui->changebutton->show();
    k=5;
    ran=30;
    ui->level->hide();
}
void Widget::on_demon_clicked()
{
    ui->changebutton->show();
    k=1;
    ran=30;
    ui->level->hide();
}

void Widget::on_Mainbutton_clicked()
{
    //初始化
    ui->stackedWidget->setCurrentIndex(0);
    ui->changebutton->setText("给予通关区间");
    ui->level->show();
    ui->label->move(50,200);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);
}
void Widget::on_rebon_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->rebonlabel->show();
}

void Widget::on_button_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}
