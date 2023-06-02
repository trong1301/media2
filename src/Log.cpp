// 2W include
#include "include/Log.h"

// C++ include

namespace utils {

void tWLogHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
#if(ENABLE_LOG)
    QByteArray localMsg = msg.toLocal8Bit();
    const char* file = context.file ? context.file : "";
    const char* function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, BLACK "[DEBUG]  [%s:%u] " NONE "%s %s\n", file, context.line, function, localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, GREEN "[INFO]  [%s:%u] " NONE "%s %s\n", file, context.line, function, localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, YELLOW "[WARNING]  [%s:%u] " NONE "%s %s\n", file, context.line, function, localMsg.constData());
        break;
    case QtCriticalMsg:
    case QtFatalMsg:
        fprintf(stderr, L_RED "[ERROR]  [%s:%u] " NONE "%s %s\n", file, context.line, function, localMsg.constData());
        break;
    }
#else
#endif
} /* namespace utils */
}


