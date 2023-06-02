#include <QDir>
#include <QStandardPaths>
// 2W include
#include "include/GuiApplication.h"
#include "include/Log.h"

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

         //Init 2W logging first
    qInstallMessageHandler(utils::tWLogHandler);

    GuiApplication app(argc, argv);

//    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);    //Get list of directories to store Pictures
//    qInfo() << paths;
//    QString path = paths[0];    //Choose the first directory to store our frame
//    qInfo() << path;

//    QDir directory(path);        //Convert into data type which app can understand
//    qInfo() << "EntryList: " << directory.entryList();
//    qInfo() << "path: " << directory.absolutePath();


    return app.exec();
}
