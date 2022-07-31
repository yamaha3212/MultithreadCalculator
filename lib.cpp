#include "lib.h"
#include <limits>
#include <cfenv>
#include <thread>
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

namespace  {
enum class error { OVERFLOW = 1, UNDERFLOW = 2, DIVBYZERO = 3, INEXACT = 4 };

void checkError(int* errorCode) {
    if (static_cast<bool>(std::fetestexcept(FE_OVERFLOW))) {*errorCode = static_cast<int>(error::OVERFLOW); return;}
    if (static_cast<bool>(std::fetestexcept(FE_UNDERFLOW))) {*errorCode = static_cast<int>(error::UNDERFLOW); return;}
}

bool isZero(const double pValue, int* errorCode) {
    volatile double epsilon = std::numeric_limits<double>::epsilon();
    volatile bool zero;
    zero = pValue <= epsilon;
    if (zero) { *errorCode = static_cast<int>(error::DIVBYZERO); }
    return zero;
}
}


double doIt(int typeWork, double operandA, double operandB, int* errorCode) {

    volatile double result = 0;
    switch (typeWork) {
        case 0: // SUM
            result = operandA + operandB;
            checkError(errorCode);
            return result;
        case 1: // SUB
            result = operandA - operandB;
            checkError(errorCode);
            return result;
        case 2: // DIV
            if (!isZero(operandB, errorCode)) {
                result = operandA / operandB;
                checkError(errorCode);
                return result;
            }
            return 0;
        case 3: // MUL
            result = operandA * operandB;
            checkError(errorCode);
            return result;
        default:
            return 0;
    }
}
