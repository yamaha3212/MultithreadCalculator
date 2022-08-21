#include <threadsafequeue.cpp>
#include "core.h"
#include "mlib.h"
#include <thread>
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
    QueueCommands.push(static_cast<Operation::operation>(op));
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

QString calculator::getGenuineOperation(Operation::operation op) {
    switch (op) {
        case Operation::operation::SUM: return "+";
        case Operation::operation::SUB: return "-";
        case Operation::operation::DIV: return "/";
        case Operation::operation::MUL: return "*";
        default: return "err";
    }
}

void calculator::getRes() {

    volatile double operandA;
    volatile double operandB;

    MLib mathlib;

    while (!QueueRequests.empty()) {

        if ( QueueCommands.empty() ) { return; }
        Operation::operation op = QueueCommands.pop();
        if ( op == Operation::operation::RST && !QueueResults.empty() ) {QueueResults.pop(); continue;}
        else if ( op == Operation::operation::RST ) {continue;}
        if(QueueRequests.size() == 1 && QueueResults.empty()) { return; }
        operandA = QueueResults.empty() ? QueueRequests.pop() : QueueResults.pop();
        operandB = QueueRequests.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        //double result = doIt(op, operandA, operandB, &errCode);
        double result = mathlib.doIt(op, operandA, operandB, &errCode);
        emit sendResponse(QString::number(operandA) + " " + getGenuineOperation(op) + " " + QString::number(operandB));
        if (!future.isCanceled()) {
            emit sendResult(result, errCode);
            if (errCode == 3) { terminate(); return; }
            QueueResults.push(result);
        }
    }
}
