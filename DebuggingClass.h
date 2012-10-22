#ifndef DEBUGGINGCLASS_H
#define DEBUGGINGCLASS_H

// qt
#include <QObject>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>

// other
#include "igpdmodder.h"
#include "Halo4ProfileDialog.h"
#include "Stfs/StfsPackage.h"

struct Arguments
{
    StfsPackage *package;
    QString tempFilePath;
};

class DebuggingClass : public QObject
{
    Q_OBJECT
public:
    explicit DebuggingClass(QObject *parent = 0);
    
signals:
    
public slots:
    void InjectGPD();

private:
    StfsPackage *profile;
    QString tempPath;
};

#endif // DEBUGGINGCLASS_H
