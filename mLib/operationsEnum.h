#pragma once
#include <QtCore>

class Operation : public QObject {

    Q_OBJECT

public:
    enum class operation : int
    {
        SUM = 0,
        SUB,
        DIV,
        MUL,
        RST, // necessary to separate calculation chains
        NOOP // No operation. Init value in QML
    };

    Q_ENUM( operation )
};

