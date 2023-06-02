#ifndef LOG_H
#define LOG_H

// Qt include
#include <QDebug>

// C++ include
#include <stdio.h>

// clang-format off
#define NONE                 "\033[0m"
#define BLACK                "\033[0;30m"
#define L_BLACK              "\033[1;30m"
#define RED                  "\033[0;31m"
#define L_RED                "\033[1;31m"
#define GREEN                "\033[0;32m"
#define L_GREEN              "\033[1;32m"
#define BROWN                "\033[0;33m"
#define YELLOW               "\033[1;33m"
#define BLUE                 "\033[0;34m"
#define L_BLUE               "\033[1;34m"
#define PURPLE               "\033[0;35m"
#define L_PURPLE             "\033[1;35m"
#define CYAN                 "\033[0;36m"
#define L_CYAN               "\033[1;36m"
#define GRAY                 "\033[0;37m"
#define WHITE                "\033[1;37m"
// clang-format on

/** Available type from qlogging.h
 *  qDebug
 *  qInfo
 *  qWarning
 *  qCritical = qFatal
 **/

namespace utils {

//!
//! \brief tWLogHandler New 2W pattern logging, ref from old 2W & doc.qt.io/qt-5/qtglobal.html#qInstallMessageHandler
//!
void tWLogHandler(QtMsgType type, const QMessageLogContext&, const QString& msg);

} /* namespace utils */
#endif // LOG_H
