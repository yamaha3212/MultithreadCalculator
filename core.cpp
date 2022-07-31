#include <threadsafequeue.cpp>
#include "core.h"
#include <iostream>
#include <thread>
#include <lib.h>
#include <mutex>
#include <future>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <string>

int calculator::delay;
int calculator::errCode;
calculator::operation calculator::workType;

calculator::calculator(QObject* parent) : QObject(parent)
{
}

void calculator::getDelay(int delay) {
    calculator::delay = delay;
}

void calculator::pushRequest(double number) {
    QueueRequests1.push(number);
}

void calculator::pushOperation(int op) {
    QueueCommands.push(op);
}

void calculator::tryCalculate() {
    if  (!future.isRunning()) {
        future = QtConcurrent::run(this, &calculator::getRes);
    }
}

void calculator::terminate() {
    future.cancel();
    QueueResults1.clear();
    QueueRequests1.clear();
    QueueCommands.clear();
}

void calculator::getRes() {

    volatile double operandA;
    volatile double operandB;

    while (!QueueRequests1.empty()) {

        if(QueueRequests1.size() == 1 && QueueResults1.empty()) { return; }
        operandA = QueueResults1.empty() ? QueueRequests1.front() : QueueResults1.front();
        if (QueueResults1.empty()) {QueueRequests1.pop();}
        else {QueueResults1.pop();}
        operandB = QueueRequests1.front();
        QueueRequests1.pop();
        if ( QueueCommands.empty() ) { return; }
        int op = static_cast<int>(QueueCommands.front());
        QueueCommands.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        double result = doIt(op, operandA, operandB, &errCode);
        std::cout << "Request lenght: " << QueueRequests1.size() << " " << operandA  << " " << op << " " << operandB << " result is: " << result << " exit code: " << errCode << std::endl;
        if (!future.isCanceled()) {
            emit sendResult(result, errCode);
            if (errCode == 3) { terminate(); return; }
            QueueResults1.push(result);
        }
    }
}
