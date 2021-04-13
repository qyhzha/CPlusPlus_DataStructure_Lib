#ifndef __QDEBUG_H__
#define __QDEBUG_H__

#include "QObject.h"
#include "QString.h"
#include <cstdio>
#include <cstdarg>

namespace qLib
{

#define QDEBUG
#define QDEBUG_OUTPUT_MAX_LENGTH 2048

#ifdef QDEBUG
#define qDebug(format, ...) QDebug::debug(format, ##__VA_ARGS__)
#else
#define qDebug(format, ...)
#endif

class QDebug : public QObject
{
    public :
        typedef void (*QDebugHandler)(const char *);

    protected :
        char *m_buffer;
        int m_length;
        QDebugHandler m_handler;

        void output(const char *buffer);

    public :
        QDebug();
        ~QDebug();

        inline QDebugHandler QInstallDebugHandler(QDebugHandler h)
        {
            QDebugHandler old = m_handler;
            m_handler = h;
            return old;
        }

        QDebug &operator<<(int value);
        QDebug &operator<<(const char *buffer);
        QDebug &operator<<(const QString &string);

        static inline QDebug debug() { return QDebug(); }
        static inline void debug(int value) { debug() << value; }
        static inline void debug(const char *buffer) { debug() << buffer; }
        static inline void debug(const QString &string) { debug() << string; }
};

}

#endif
