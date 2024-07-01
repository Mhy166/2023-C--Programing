#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class Mythread : public QThread
{
    Q_OBJECT
public:
    explicit Mythread(QObject *parent = nullptr);
    void run(); //线程处理函数;
signals:

void isDone();

};

#endif // MYTHREAD_H
