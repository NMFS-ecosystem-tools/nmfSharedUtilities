#ifndef NMFDATABASE_GLOBAL_H
#define NMFDATABASE_GLOBAL_H

//#include <QtCore/qglobal.h>

#if defined(NMFDATABASE_LIBRARY)
#  define NMFDATABASESHARED_EXPORT Q_DECL_EXPORT
#else
#  define NMFDATABASESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NMFDATABASE_GLOBAL_H
