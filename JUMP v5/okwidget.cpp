#include "okwidget.h"
#include<QMovie>
#include<QLabel>
OKwidget::OKwidget(QWidget *parent) : QWidget(parent)
{
    QMovie*okmovie=new QMovie(":/Photo/OK.gif");
    QLabel*oklabel0=new QLabel(this);
    oklabel0->resize(1000,1000);
    oklabel0->setMovie(okmovie);
    oklabel0->setScaledContents(1);
    okmovie->start();
}
