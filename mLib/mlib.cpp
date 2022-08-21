#include "mlib.h"
#include <limits>
#include <cfenv>
#include <thread>
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

enum class error { OVERFLOW_C = 1, UNDERFLOW_C = 2, DIVBYZERO_C = 3, INEXACT_C = 4 };

void checkError(int* errorCode) {
    if (static_cast<bool>(std::fetestexcept(FE_OVERFLOW))) {*errorCode = static_cast<int>(error::OVERFLOW_C); return;}
    if (static_cast<bool>(std::fetestexcept(FE_UNDERFLOW))) {*errorCode = static_cast<int>(error::UNDERFLOW_C); return;}
}

bool isZero(const double pValue, int* errorCode) {
    if (pValue <= std::numeric_limits<double>::epsilon()) { *errorCode = static_cast<int>(error::DIVBYZERO_C); return true; }
    return false;
}

double MLib::doIt(Operation::operation typeWork, double operandA, double operandB, int* errorCode) {

    volatile double result = 0;
    switch (typeWork) {
        case Operation::operation::SUM:
            result = operandA + operandB;
            checkError(errorCode);
            return result;
        case Operation::operation::SUB:
            result = operandA - operandB;
            checkError(errorCode);
            return result;
        case Operation::operation::DIV:
            if (!isZero(operandB, errorCode)) {
                result = operandA / operandB;
                checkError(errorCode);
                return result;
            }
            return std::numeric_limits<double>::max();
        case Operation::operation::MUL:
            result = operandA * operandB;
            checkError(errorCode);
            return result;
        default:
            return 0;
    }
}

MLib::MLib()
{

}
