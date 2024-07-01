#include "mythread.h"

Mythread::Mythread(QObject *parent) : QThread(parent)
{

}
void Mythread::run(){
    msleep(1000);
    emit isDone();
}
