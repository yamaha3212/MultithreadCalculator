#ifndef MLIB_H
#define MLIB_H
#include "operationsEnum.h"
#include "mLib_global.h"

class MLIB_EXPORT MLib
{
public:
    MLib();
    double doIt(Operation::operation typeWork, double operandA, double operandB, int* errorCode);
};

#endif // MLIB_H
