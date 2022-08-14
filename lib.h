#pragma once

/*
#ifdef _WIN32
#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif
#else
#define CLASS_DECLSPEC
#endif

CLASS_DECLSPEC */ double doIt (int typeWork, double operandA, double operandB, int* errorCode);
