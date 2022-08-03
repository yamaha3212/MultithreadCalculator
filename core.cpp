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

void calculator::tryCalculate() {
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

void calculator::getRes() {

    volatile double operandA;
    volatile double operandB;

    while (!QueueRequests.empty()) {

        if ( QueueCommands.empty() ) { return; }
        int op = static_cast<int>(QueueCommands.pop());
        if ( op == 4 && !QueueResults.empty() ) {QueueResults.pop(); continue;}
        else if ( op == 4 ) {continue;}
        if(QueueRequests.size() == 1 && QueueResults.empty()) { return; }
        operandA = QueueResults.empty() ? QueueRequests.pop() : QueueResults.pop();
        operandB = QueueRequests.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        double result = doIt(op, operandA, operandB, &errCode);
        std::cout << "Request lenght: " << QueueRequests.size() << " " << operandA  << " " << op << " " << operandB << " result is: " << result << " exit code: " << errCode << std::endl;
        if (!future.isCanceled()) {
            emit sendResult(result, errCode);
            if (errCode == 3) { terminate(); return; }
            QueueResults.push(result);
        }
    }
}
