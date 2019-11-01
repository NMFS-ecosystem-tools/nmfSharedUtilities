#ifndef NMFMORTALITYMODEL_GLOBAL_H
#define NMFMORTALITYMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NMFMORTALITYMODEL_LIBRARY)
#  define NMFMORTALITYMODELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NMFMORTALITYMODELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NMFMORTALITYMODEL_GLOBAL_H