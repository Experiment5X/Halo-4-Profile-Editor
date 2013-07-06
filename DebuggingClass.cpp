#include "DebuggingClass.h"

DebuggingClass::DebuggingClass(QObject *parent) :
    QObject(parent)
{
    Halo4ProfileDialog w;

    QString fileName = QFileDialog::getOpenFileName(0, "Open a Profile", QDesktopServices::storageLocation(QDesktopServices::DesktopLocation), "All Files (*)");
    if (fileName.isNull())
        return;

    profile = new StfsPackage(fileName.toStdString());

    tempPath = QDir::tempPath() + "/" + QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "");
    profile->ExtractFile(QString("%1").arg(w.TitleID(), 8, 16, QChar('0')).toUpper().toStdString() + ".gpd", tempPath.toStdString());

    Arguments *args = new Arguments;
    args->package = profile;
    args->tempFilePath = tempPath;

    GameGpd *gameGPD = new GameGpd(tempPath.toStdString());
    bool ok;
    w.LoadGPD(gameGPD, &ok, args);

    connect(&w, SIGNAL(InjectGPD()), this, SLOT(InjectGPD()));

    if (ok)
        w.exec();
}

void DebuggingClass::InjectGPD()
{
    IGPDModder *gpd = qobject_cast<IGPDModder*>(sender());

    if (!gpd)
        throw "Some shit broke.";

    Arguments *args = (Arguments*)gpd->Arguments;
    try
    {
        args->package->ReplaceFile(args->tempFilePath.toStdString(), QString("%1").arg(gpd->TitleID(), 8, 16, QChar('0')).toUpper().toStdString() + ".gpd");
        args->package->Rehash();

        // todo
        // args->package->Resign(QtHelpers::GetKVPath(args->package->metaData->certificate.ownerConsoleType, this));

        args->package->Close();
        delete args->package;
    }
    catch (string error)
    {
        QMessageBox::critical(NULL, "Couldn't Repalce GPD", "The GPD could not be replaced.\n\n" + QString::fromStdString(error));
        try
        {
            delete args->package;
        }
        catch(...) { }
    }
}
