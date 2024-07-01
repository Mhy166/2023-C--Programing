#include "mythread.h"

Mythread::Mythread(QObject *parent) : QThread(parent)
{

}
void Mythread::run(){
    msleep(500);
    emit isDone();
}
