#pragma once
#include "threadsafequeue.h"
#include <queue>
#include <iostream>
#include <QObject>
#include <thread>
#include <future>
#include <mutex>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QQueue>
#include <QString>

class calculator : public QObject
{

    Q_OBJECT

public:
    explicit calculator(QObject *parent = nullptr);
    QFuture<void> future;
    void getRes();

signals:
    void sendResult(double result, int code);

public slots:
    void pushRequest(double number);
    void pushOperation(int op);
    void tryCalculate();
    void terminate();
    void getDelay(int delay);

private:
    enum class operation { SUM, SUB, DIV, MUL };

    threadSafeQueue<int> QueueCommands;
    threadSafeQueue<double> QueueRequests1;
    threadSafeQueue<double> QueueResults1;

    static int errCode;
    static operation workType;
    static int delay;
};
