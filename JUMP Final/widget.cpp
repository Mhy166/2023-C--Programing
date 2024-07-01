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
#include<QGraphicsRotation>
#include<QMatrix>
#include<QMovie>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QPixmap>
#include<QParallelAnimationGroup>
#include<QSlider>
 static int i=0;
 int k=10;
 int v=0;
 int vo1=50;
 static int add=20;      //进度条
 int dy=0;   //判断是否打开动态模式
 int skin=1; //判断皮肤号
 int max=0;  //记录两模式最高分数
 int normax=0;
 int dyback=1;
 int r=0;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    tithd=new timerthread(this);
    connect(this,&Widget::ti,tithd,&timerthread::tidone);
    connect(tithd,&timerthread::done,this,&Widget::dedone);
    connect(tithd,&timerthread::lcd,this,&Widget::done);
    thread=new Mythread(this);
    connect(this,&Widget::destroyed,this,&Widget::stopthread);
    connect(thread,&Mythread::isDone,this,&Widget::dealdone);

     //背景音乐
     musicback=new QMediaPlayer;
     QMediaPlaylist*list=new QMediaPlaylist;
     list->addMedia(QUrl("qrc:/n/Music/himmel-Code-Paradiso.mp3"));
     list->setPlaybackMode(QMediaPlaylist::Loop);
     musicback->setPlaylist(list);
     musicback->play();


     //计时窗口

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle("跳一跳模拟小程序");
    this->resize(1000,1000);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->rebonlabel->hide();
    ui->readyBon->hide();


    //反应模式计时器


    //按压  按钮
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

    //音效
    music1=new QMediaPlayer;
    QMediaPlaylist*musicl=new QMediaPlaylist;
    musicl->addMedia(QUrl("qrc:/n/Music/press.mp3"));
    music1->setPlaylist(musicl);

    musicst=new QMediaPlayer;
    QMediaPlaylist*musiclst=new QMediaPlaylist;
    musiclst->addMedia(QUrl("qrc:/n/Music/start.mp3"));
    musicst->setPlaylist(musiclst);

    musicce=new QMediaPlayer;
    QMediaPlaylist*musiclce=new QMediaPlaylist;
    musiclce->addMedia(QUrl("qrc:/n/Music/center.mp3"));
    musicce->setPlaylist(musiclce);

    musicde=new QMediaPlayer;
    QMediaPlaylist*musiclde=new QMediaPlaylist;
    musiclde->addMedia(QUrl("qrc:/n/Music/defeat.mp3"));
    musicde->setPlaylist(musiclde);

    musicla=new QMediaPlayer;
    QMediaPlaylist*musiclla=new QMediaPlaylist;
    musiclla->addMedia(QUrl("qrc:/n/Music/la.mp3"));
    musicla->setPlaylist(musiclla);

    musicku=new QMediaPlayer;
    QMediaPlaylist*musiclku=new QMediaPlaylist;
    musiclku->addMedia(QUrl("qrc:/n/Music/kun.mp3"));
    musicku->setPlaylist(musiclku);


    //初始动画
    QMovie*stmovie=new QMovie(":/Photo/start.gif");
    ui->startlabel->setMovie(stmovie);
    ui->startlabel->setScaledContents(1);
    stmovie->start();

    ui->Mainbutton->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->NorBon->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->skinbon->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->DYButton->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->opButton->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->pushButton_8->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->startbon->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->pushButton_7->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->pushButton_2->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->pushButton_3->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->pushButton_4->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->pushButton_5->setStyleSheet("QPushButton{""border-image:url(:/Photo/kun.jpg)""}");
    ui->pushButton_6->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->pushButton->setStyleSheet("QPushButton{""border-image:url(:/Photo/button2.png)""}");
    ui->startbon->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->button->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->readyBon->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->changebutton->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");
    ui->rebon->setStyleSheet("QPushButton{""border-image:url(:/Photo/button1.png)""}");

}

void Widget::stopthread(){
    thread->quit();
    thread->wait();
}
Widget::~Widget()
{
    delete ui;
}
void Widget::dedone(int j){
    i=j;
}
void Widget::done(int j){
    ui->lcdNumber->display(j);
}
void Widget::on_startbon_pressed()
{
  tithd->start();
  ui->label->resize(40,110);
  music1->play();

  //压缩动画
   QPropertyAnimation*animation11 = new QPropertyAnimation(ui->label, "geometry");
        animation11->setDuration(500);
        animation11->setStartValue(QRect(130,250, 40,110));
        animation11->setEndValue(QRect(125, 280, 50,90));
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
    //提供下一个块
    qsrand(QTime(num%21,num%13,num%50).secsTo(QTime::currentTime()));
    while((num=qrand()%600)<200);
    QString str=QString::number(num);str+=" ";str+=QString::number(num+60);
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
    musicla->play();

}
void Widget::on_startbon_released()
{
    music1->stop();
    tithd->quit();
    emit ti();
    v=0;
    ui->startbon->hide();
    ui->label->show();
    //释放后起跳动画
          animation1 = new QPropertyAnimation(ui->label, "geometry");
          animation1->setDuration(500);
          animation1->setStartValue(QRect(125, 280, 50,90));
          animation1->setEndValue(QRect(130+i/2, 50, 40,110));
          animation1->setEasingCurve(QEasingCurve::OutQuart);
          animation2 = new QPropertyAnimation(ui->label, "geometry");
          animation2->setDuration(500);
          animation2->setStartValue(QRect(130+i/2, 50, 40,110));
          animation2->setEasingCurve(QEasingCurve::OutQuart);
          animation3 = new QPropertyAnimation(ui->label, "geometry");
          animation3->setDuration(500);
          animation3->setStartValue(QRect(130+i, 250, 40,110));
          animation3->setEndValue(QRect(130,250,40,110));
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
    if(i<=num+60&&i>=num)
    {
        if(skin==5)
        {
            musicku->play();
            QMovie*fymovie=new QMovie(":/Photo/kun.gif");
            ui->label->setMovie(fymovie);
            ui->label->setScaledContents(1);
            ui->label_2->setMovie(fymovie);
            ui->label_2->setScaledContents(1);
            fymovie->start();
        }

        value+=add;
        animation2->setEndValue(QRect(130+i,250,40,110));
        angroup->addAnimation(group3);
        angroup->start();
        ui->changebutton->setText("继续");
        ui->proBar->setValue(value);
        musicla->play();
        //过关
        if(value>=100)
        {
            ui->stackedWidget_2->setCurrentIndex(2);
            musicce->play();
        }
    }
    //失败
    else{
        if(skin==5)musicji->play();
        if(i>num+60)animation2->setEndValue(QRect(130+i,300,40,110));
        if(i<num)animation2->setEndValue(QRect(130+i,300,40,110));
        angroup->removeAnimation(group3);
        angroup->start();
        ui->changebutton->hide();
        if(skin!=5)musicde->play();
    }
}
//提供下一个块的“信号”
void Widget::on_changebutton_clicked()
{
    thread->start();
    i=0;
    ui->lcdNumber->display(i);
    ui->obj1label->move(30,250);
    if(skin==5){QPixmap p(":/Photo/chara4.png");
    ui->label->setPixmap(p);}
    backchange++;

    if(dyback==1)
    {
        QMovie*fymovie=new QMovie(":/Photo/background4.gif");
        ui->label_2->setMovie(fymovie);
        ui->label_2->setScaledContents(1);
        fymovie->start();
        if(backchange%2==0)
       {
            QMovie*fymovie=new QMovie(":/new/prefix1/Photo/back2.gif");
            ui->label_2->setMovie(fymovie);
            ui->label_2->setScaledContents(1);
            fymovie->start();
       }
        if(backchange%2==1)
       {
            QMovie*fymovie=new QMovie(":/new/prefix1/Photo/back.gif");
            ui->label_2->setMovie(fymovie);
            ui->label_2->setScaledContents(1);
            fymovie->start();
       }
    }
    else{
        QPixmap s(":/Photo/background2.jpg");
        ui->label_2->setPixmap(s);
    }
}

//难度按钮
void Widget::on_eazy_clicked()
{
    ui->readyBon->show();
    k=8;
    add=34;
    ui->level->hide();
}
void Widget::on_hard_clicked()
{
    ui->readyBon->show();
    k=5;
    add=20;
    ui->level->hide();
}
void Widget::on_insane_clicked()
{
    ui->readyBon->show();
    k=3;
    add=20;
    ui->level->hide();
}
void Widget::on_demon_clicked()
{
    ui->readyBon->show();
    k=1;
    add=20;
    ui->level->hide();
}

//主菜单反应模式按钮
void Widget::on_Mainbutton_clicked()
{
    r=0;
    //初始化
    ui->stackedWidget->setCurrentIndex(0);
    ui->changebutton->setText("给予通关区间");
    ui->level->show();
    ui->label->move(130,250);
    ui->startbon->hide();
    ui->changebutton->hide();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->obj2label->hide();
    ui->obj1label->show();
    ui->label->hide();
    ui->button->hide();
    QMovie*omovie=new QMovie(":/Photo/loser.gif");
    ui->overlabel->setMovie(omovie);
    ui->overlabel->setScaledContents(1);
    omovie->start();
    if(!bgm)musicback->pause();
    QPixmap s(":/Photo/background2.jpg");
    ui->label_2->setPixmap(s);
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
    musicback->play();
    ui->rebonlabel->show();
}
//认输按钮 本按钮后才会有重置按钮
void Widget::on_button_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}
//过关后以下一模式返回的按钮
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
//过关后保留原模式的按钮
void Widget::on_OKButton2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->rebonlabel->show();
}
//准备按钮=棋子出场
void Widget::on_readyBon_clicked()
{
    ui->readyBon->hide();
    ui->changebutton->show();
    ui->label->show();
    ui->button->show();
    animation40 = new QPropertyAnimation(ui->label, "geometry");
          animation40->setDuration(1000);
          animation40->setStartValue(QRect(130,0, 40,110));
          animation40->setEndValue(QRect(130,250, 40,110));
          animation40->setEasingCurve(QEasingCurve::OutElastic);
    animation40->start();
    musicst->play();
}
//正常模式按钮
void Widget::on_NorBon_clicked()
{
    r=1;
    dy=0;
    Norwidget*norwidget;
    norwidget=new Norwidget;
    connect(norwidget,&Norwidget::norbacksignal,this,&Widget::dealback);
    norwidget->show();
    this->hide();
    if(!bgm)musicback->pause();
}

//动态模式按钮
void Widget::on_DYButton_clicked()
{
    r=1;
    dy=1;
    Norwidget*norwidget;
    norwidget=new Norwidget;
    connect(norwidget,&Norwidget::norbacksignal,this,&Widget::dealback);
    norwidget->show();
    this->hide();
    if(!bgm)musicback->pause();

}
//处理两模式窗口关闭后的事情
void Widget::dealback()
{
    this->show();
    musicback->play();
}
//皮肤按钮
void Widget::on_pushButton_clicked()
{
    skin=1;
    QPixmap p(":/Photo/character.png");
    ui->label->setPixmap(p);
    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_pushButton_2_clicked()
{
    skin=2;
    QPixmap p(":/Photo/chara2.png");
    ui->label->setPixmap(p);
    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_pushButton_3_clicked()
{
    skin=3;
    QPixmap p(":/Photo/chara3.png");
    ui->label->setPixmap(p);
    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_pushButton_4_clicked()
{
    skin=4;
    QPixmap p(":/Photo/chara5.png");
    ui->label->setPixmap(p);
    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_pushButton_5_clicked()
{
    skin=5;
    QPixmap p(":/Photo/chara4.png");
    ui->label->setPixmap(p);
    ui->stackedWidget->setCurrentIndex(1);
    musicji=new QMediaPlayer;
    QMediaPlaylist*musiclji=new QMediaPlaylist;
    musiclji->addMedia(QUrl("qrc:/n/Music/niganma.mp3"));
    musicji->setPlaylist(musiclji);
    musicji->play();
}
void Widget::on_pushButton_6_clicked()
{
    skin=6;
    QPixmap p(":/Photo/chara6.png");
    ui->label->setPixmap(p);
    ui->stackedWidget->setCurrentIndex(1);
}
//主菜单的皮肤按钮
void Widget::on_skinbon_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//设置按钮
void Widget::on_opButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    connect(ui->backmusic,&QSlider::valueChanged,
            [=]()
    {
        int vo=ui->backmusic->value();
        musicback->setVolume(vo);
    }
            );
    connect(ui->musicSlider,&QSlider::valueChanged,
            [=]()
    {
        vo1=ui->musicSlider->value();
        musicla->setVolume(vo1);
        musicst->setVolume(vo1);
        music1->setVolume(vo1);
        musicce->setVolume(vo1);
        musicde->setVolume(vo1);
        musicce->play();
    }
            );
    connect(ui->checkBox,&QCheckBox::stateChanged,
            [=]()
    {
        if(ui->checkBox->checkState()==Qt::Checked)bgm=0;
        else{bgm=1;}
    }
    );
    connect(ui->checkBox_2,&QCheckBox::stateChanged,
            [=]()
    {
        if(ui->checkBox_2->checkState()==Qt::Checked)dyback=0;
        else{dyback=1;}
    }
    );
}
//设置按钮返回
void Widget::on_pushButton_7_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);

}

