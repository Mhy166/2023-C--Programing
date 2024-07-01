#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include<QTimer>
class timerthread : public QThread
{
    Q_OBJECT
public:
    explicit timerthread(QObject *parent = nullptr);
    QTimer*mytimer;
    void run();
    void tidone();

signals:
    void done(int);
    void lcd(int);
};

#endif // TIMERTHREAD_H
