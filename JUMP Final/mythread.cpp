#include "mythread.h"

Mythread::Mythread(QObject *parent) : QThread(parent)
{

}
void Mythread::run(){
    //线程
    msleep(1000);
    emit isDone();
}
