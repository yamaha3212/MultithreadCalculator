#ifndef MLIB_GLOBAL_H
#define MLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MLIB_LIBRARY)
#  define MLIB_EXPORT Q_DECL_EXPORT
#else
#  define MLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MLIB_GLOBAL_H
