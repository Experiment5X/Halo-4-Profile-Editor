// qt
#include <QtGui/QApplication>
#include <QDir>
#include <QUuid>
#include <QFileDialog>
#include <QString>
#include <QDesktopServices>
#include <QObject>

// other
#include "Halo4ProfileDialog.h"
#include "Stfs/StfsPackage.h"
#include "DebuggingClass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DebuggingClass debugClass;

    return a.exec();
}
