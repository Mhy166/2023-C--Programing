#include "mylabal.h"
#include<QMouseEvent>
#include<QKeyEvent>
#include<QDebug>
Mylabal::Mylabal(QWidget *parent) : QLabel(parent)
{
this->hide();
}
void Mylabal::mousePressEvent(QMouseEvent *ev)
{
    int i=ev->x();
    int j=ev->y();
    QString text=QString("<center><h1>Mouse Press:(%1,%2)</h1></center>").arg(i).arg(j);
   this->setText(text);
    if(ev->button()==Qt::LeftButton) qDebug()<<"left";
}
void Mylabal::mouseMoveEvent(QMouseEvent *ev)
{
    QString text=QString("<center><h1>Mouse Press:(%1,%2)</h1></center>").arg(ev->x()).arg(ev->y());

}
void Mylabal::enterEvent(QEvent*e){
    QString text=QString("<center><h1>Mouse Enter</h1></center>");
   this->setText(text);
}
void Mylabal::leaveEvent(QEvent*e){
    QString text=QString("<center><h1>Mouse leave</h1></center>");
   this->setText(text);
}

