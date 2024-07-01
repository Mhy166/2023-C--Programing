#include "timerthread.h"
#include<QDebug>

timerthread::timerthread(QObject *parent) : QThread(parent)
{

}
void timerthread::run(){
    extern int r;
    mytimer=new QTimer;
    connect(mytimer,&QTimer::timeout,
            [=]()
            {
                if(r){extern int u;
                u++;}
                if(!r){
                    extern int v;v++;emit lcd(v);
                }
            }
            );
    if(r)
    {mytimer->start(3);}
    else
    {
        extern int k;
        mytimer->start(k);
    }
    exec();
}
void timerthread::tidone()
{
    extern int r;
            if(r){ extern int u;emit done(u);}
            if(!r){ extern int v;emit done(v);}

}
