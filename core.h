#pragma once
#include "threadsafequeue.h"
#include "operationsEnum.h"
#include <QObject>
#include <QFuture>

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
    QString getGenuineOperation(Operation::operation op);

    threadSafeQueue<Operation::operation> QueueCommands;
    threadSafeQueue<double> QueueRequests;
    threadSafeQueue<double> QueueResults;

    int errCode;
    Operation::operation workType;
    int delay;
};
