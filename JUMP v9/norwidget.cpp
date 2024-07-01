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
 int score;
extern int dy;
extern int max;
extern int normax;
static int k=0;
Norwidget::Norwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Norwidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
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
    animation40 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation40->setDuration(1000);
          animation40->setStartValue(QRect(130,0, 40,110));
          animation40->setEndValue(QRect(130,200, 40,110));
          animation40->setEasingCurve(QEasingCurve::OutElastic);
          show1->addAnimation(animation41);
          show1->addAnimation(animation40);
          show1->start();
    connect(this,&Norwidget::stsignal,this,&Norwidget::dealsig);
    k=0;
    emit stsignal();
    k=1;
    ui->norlabel->show();

    music=new QMediaPlayer;
    QMediaPlaylist*musicl=new QMediaPlaylist;
    musicl->addMedia(QUrl("qrc:/n/Music/jump.mp3"));
    music->setPlaylist(musicl);
    music->setVolume(200);
    ui->scochara->resize(40,110);
    extern int skin;
   if(skin==1)
    {
        QPixmap p(":/Photo/character.png");
        ui->norlabel->setPixmap(p);
        ui->scochara->setPixmap(p);
    }
   if(skin==2)
    {
        QPixmap p(":/Photo/chara2.png");
        ui->norlabel->setPixmap(p);
        ui->scochara->setPixmap(p);
    }
   if(skin==3)
    {
        QPixmap p(":/Photo/chara3.png");
        ui->norlabel->setPixmap(p);
        ui->scochara->setPixmap(p);
    }
   if(skin==4)
    {
        QPixmap p(":/Photo/chara5.png");
        ui->norlabel->setPixmap(p);
        ui->scochara->setPixmap(p);
    }
   if(skin==5)
    {
        QPixmap p(":/Photo/chara4.png");
        ui->norlabel->setPixmap(p);
        ui->scochara->setPixmap(p);
    }
   if(skin==6)
    {
        QPixmap p(":/Photo/chara6.png");
        ui->norlabel->setPixmap(p);
        ui->scochara->setPixmap(p);
    }

}

Norwidget::~Norwidget()
{
    delete ui;
}

void Norwidget::on_norbackbon_clicked()
{

    ui->scolabel->move(435,400);
    ui->stackedWidget->setCurrentIndex(1);
    scotimer=new QTimer(this);
    connect(scotimer,&QTimer::timeout,
            [=]()
            {
       animation61 = new QPropertyAnimation(ui->scochara, "geometry");
              animation61->setDuration(100);
              animation61->setStartValue(QRect(435, 400, 200, 200));
              animation61->setEndValue(QRect(435,410,200,190));
              animation61->setEasingCurve(QEasingCurve::OutQuart);
       animation62 = new QPropertyAnimation(ui->scochara, "geometry");
              animation62->setDuration(200);
              animation62->setStartValue(QRect(435,410,200,190));
              animation62->setEndValue(QRect(435,200,200,200));
              animation62->setEasingCurve(QEasingCurve::OutQuart);
       animation63 = new QPropertyAnimation(ui->scochara, "geometry");
              animation63->setDuration(200);
              animation63->setStartValue(QRect(435,200,200,200));
              animation63->setEndValue(QRect(435,400,200,200));
              animation63->setEasingCurve(QEasingCurve::OutQuart);
        scodynamic=new QSequentialAnimationGroup(this);
        scodynamic->addAnimation(animation61);
        scodynamic->addAnimation(animation62);
        scodynamic->addAnimation(animation63);
        scodynamic->start();
            }
            );
    scotimer->start(500);
}

void Norwidget::on_NORBON_pressed()
{
    music->play();
    nortimer->start(3);
    ui->norlabel->resize(40,110);
    //压缩动画
     QPropertyAnimation*animation11 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation11->setDuration(500);
          animation11->setStartValue(QRect(130,200, 40,110));
          animation11->setEndValue(QRect(125, 240, 50,90));
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
    music->stop();
    nortimer->stop();
    ditimer->stop();
          animation1 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation1->setDuration(200);
          animation1->setStartValue(QRect(125, 240, 50,90));
          animation1->setEndValue(QRect(130+i1/2, 30,40,110));
          animation1->setEasingCurve(QEasingCurve::OutQuart);
          animation2 = new QPropertyAnimation(ui->norlabel, "geometry");
          animation2->setDuration(200);
          animation2->setStartValue(QRect(130+i1/2, 30,40,110));
          animation2->setEasingCurve(QEasingCurve::OutQuart);

          animation3 = new QPropertyAnimation(ui->norlabel, "geometry");
                animation3->setDuration(500);
                animation3->setStartValue(QRect(130+i1, 200,40,110));
                animation3->setEndValue(QRect(130,200,40,110));
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
        animation2->setEndValue(QRect(130+i1,200,40,110));
        angroup->addAnimation(group3);
        angroup->start();
        Mythread*northread=new Mythread(this);
        northread->start();
        connect(northread,&Mythread::isDone,this,&Norwidget::deal);
    }
    //失败
    else{
            if(dy)
            {
                if(max<=score)max=score;
            }
            else{
                if(normax<=score)normax=score;
            }
        QString strsco=QString::number(max);
        ui->label_norsco->setText(strsco);
        QString strsco1=QString::number(normax);
        ui->label_nordysco->setText(strsco1);
        if(i1>num+80)animation2->setEndValue(QRect(1500,200,40,110));
        if(i1<num-20)animation2->setEndValue(QRect(num,1000,40,110));
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
    extern int dy;
    ui->norobj1->move(30,250);
    static int count=0; 
    if(k){
    if(i1<=num+50&&i1>=num+10)score+=2*++count;
    else{
        score++;
        count=0;
    }
    }
    ui->score->display(score);
    i1=0;
    ui->lcdNumber->display(i1);
    qsrand(QTime(num%21,num%13,num%50).secsTo(QTime::currentTime()));
    while((num=qrand()%600)<200);
    //QString str=QString::number(num-20);str+=" ";str+=QString::number(num+80);
    ui->norobj2->move(50+num,50);
    ui->norobj2->resize(200,200);
    ui->norobj2->show();
    ditimer=new QTimer(this);

    if(dy)
    {
    connect(ditimer,&QTimer::timeout,
            [=]()
            {
                QPropertyAnimation* animation51 = new QPropertyAnimation(ui->norobj2, "geometry");
                      animation51->setDuration(125);
                      animation51->setStartValue(QRect(50+num, 250, 200, 200));
                      animation51->setEndValue(QRect(150+num,250,200,200));
                      animation51->setEasingCurve(QEasingCurve::OutQuart);
                QPropertyAnimation* animation52 = new QPropertyAnimation(ui->norobj2, "geometry");
                      animation52->setDuration(125);
                      animation52->setStartValue(QRect(150+num, 250, 200, 200));
                      animation52->setEndValue(QRect(50+num,250,200,200));
                      animation52->setEasingCurve(QEasingCurve::OutQuart);
                QPropertyAnimation* animation53 = new QPropertyAnimation(ui->norobj2, "geometry");
                      animation53->setDuration(125);
                      animation53->setStartValue(QRect(50+num, 250, 200, 200));
                      animation53->setEndValue(QRect(num-100,250,200,200));
                      animation53->setEasingCurve(QEasingCurve::OutQuart);
                QPropertyAnimation* animation54 = new QPropertyAnimation(ui->norobj2, "geometry");
                      animation54->setDuration(125);
                      animation54->setStartValue(QRect(num-100, 250, 200, 200));
                      animation54->setEndValue(QRect(50+num,250,200,200));
                      animation54->setEasingCurve(QEasingCurve::OutQuart);
                QSequentialAnimationGroup*dynamic=new QSequentialAnimationGroup(this);
                dynamic->addAnimation(animation51);
                dynamic->addAnimation(animation52);
                dynamic->addAnimation(animation53);
                dynamic->addAnimation(animation54);
                dynamic->start();
                    }
                    );
    }
    animation4 = new QPropertyAnimation(ui->norobj2, "geometry");
    {
        animation4->setDuration(1000);
        animation4->setStartValue(QRect(50+num,50, 200, 200));
        animation4->setEndValue(QRect(50+num,250, 200,200));
        animation4->setEasingCurve(QEasingCurve::OutElastic);
    }
        animation4->start();
     ditimer->start(500);



}
void Norwidget::deal(){
    emit stsignal();
}

void Norwidget::on_ScoButton_clicked()
{
    //scotimer->stop();
    this->close();
    emit norbacksignal();
}
