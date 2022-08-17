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

signals:
    void sendResult(double result, int code);
    void sendResponse(QString request);

public slots:
    void pushRequest(double number);
    void pushOperation(int op);
    void startCalculateChain();
    void terminate();
    void setDelay(int delay);

private:
    QFuture<void> future;
    void getRes();
    QString getGenuneOperation(int op);

    enum class operation { SUM, SUB, DIV, MUL, RST };

    threadSafeQueue<int> QueueCommands;
    threadSafeQueue<double> QueueRequests;
    threadSafeQueue<double> QueueResults;

    int errCode;
    operation workType;
    int delay;
};
