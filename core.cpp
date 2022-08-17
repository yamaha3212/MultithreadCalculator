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

calculator::calculator(QObject* parent) : QObject(parent) {}

void calculator::setDelay(int delay) {
    calculator::delay = delay;
}

void calculator::pushRequest(double number) {
    QueueRequests.push(number);
}

void calculator::pushOperation(int op) {
    QueueCommands.push(op);
}

void calculator::startCalculateChain() {
    if  (!future.isRunning()) {
        future = QtConcurrent::run(this, &calculator::getRes);
    }
}

void calculator::terminate() {
    future.cancel();
    QueueResults.clear();
    QueueRequests.clear();
    QueueCommands.clear();
    errCode = 0;
}

QString calculator::getGenuneOperation(int op) {
    switch (op) {
        case 0: return "+";
        case 1: return "-";
        case 2: return "/";
        case 3: return "*";
        default: return "err";
    }
}

void calculator::getRes() {

    volatile double operandA;
    volatile double operandB;

    while (!QueueRequests.empty()) {

        if ( QueueCommands.empty() ) { return; }
        int op = QueueCommands.pop();
        if ( op == 4 && !QueueResults.empty() ) {QueueResults.pop(); continue;}
        else if ( op == 4 ) {continue;}
        if(QueueRequests.size() == 1 && QueueResults.empty()) { return; }
        operandA = QueueResults.empty() ? QueueRequests.pop() : QueueResults.pop();
        operandB = QueueRequests.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        double result = doIt(op, operandA, operandB, &errCode);
        emit sendResponse(QString::number(operandA) + " " + getGenuneOperation(op) + " " + QString::number(operandB));
        if (!future.isCanceled()) {
            emit sendResult(result, errCode);
            if (errCode == 3) { terminate(); return; }
            QueueResults.push(result);
        }
    }
}
