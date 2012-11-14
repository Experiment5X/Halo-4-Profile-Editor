#ifndef GPDMODDERDIALOG_H
#define GPDMODDERDIALOG_H

// qt
#include <QObject>
#include <QtPlugin>
#include <QDialog>
#include <QMessageBox>
#include <QUuid>
#include <QDir>
#include <QDataStream>
#include <QByteArray>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDebug>

// other
#include "igpdmodder.h"
#include "BitArray.h"
#include "MemoryStream.h"
#include <botan/sha160.h>
#include <botan/botan.h>

namespace Ui {
class Halo4ProfileDialog;
}

enum Gender
{
    H4_Male = 0,
    H4_Female = 1
};

enum ControlVoiceChat
{
    AllPlayers = 0,
    TeamAndParty = 1
};

struct Halo4_TS1
{
    bool lookInversion;
    bool flightInversion;
    bool autolookCentering;
    bool holdToCrouch;

    bool clenchProtection;
    BYTE buttonLayout;
    BYTE stickLayout;
    BYTE sensitivity; 					// minus one

    DWORD theaterCameraSpeed;
    DWORD theaterCameraTurnSensitivity;
    DWORD theaterCameraPanningToggle;
    DWORD theaterCameraThrust;

    DWORD missionFlags;					// all 0xFFs if no campaign progress
    UINT64 missionStatuses;

    UINT64 coopMissionStatuses;

    time_t lastInCampaign;

    WORD missionsUnlockedFlags;
    BYTE rallyPoints[0x10];

    DWORD terminalFlags;
    Gender gender;
    DWORD armorPrimaryColor;
    DWORD armorSecondaryColor;

    BYTE armorVisorColor;

    BYTE emblemForeground;
    BYTE emblemBackground;
    bool hideEmblemDetails;
    BYTE emblemPrimaryColor;
    BYTE emblemSecondaryColor;
    BYTE emblemTertiaryColor;

    BYTE armorHelmet;
    BYTE armorTorso;

    BYTE armorLeftShoulder;
    BYTE armorRightShoulder;
    BYTE armorForearms;
    BYTE armorLegs;

    wchar_t	serviceTag[5];				// null terminating

    BYTE stance;

    bool playersMuted;

    ControlVoiceChat controlVoiceChat;	// 1 byte in length

    DWORD spartanPoints;

    DWORD experience;
};

struct Mission
{
    QString name;
    QList<int> rallyPointBitOffsets;
};

class Halo4ProfileDialog : public QDialog, IGPDModder
{
    Q_OBJECT
    Q_INTERFACES (IGPDModder)
    
public:
    explicit Halo4ProfileDialog(QWidget *parent = 0);
    ~Halo4ProfileDialog();

    void LoadGPD (GameGPD *gpd, bool *ok = NULL, void *args = NULL);
    QWidget* GetDialog();
    QString ToolAuthor() const;
    QString ToolName() const;
    DWORD TitleID() const;

signals:
    void PluginFinished();
    
private slots:

    void on_listWidget_currentRowChanged(int currentRow);

    void on_cmbxDiffSP_currentIndexChanged(int index);

    void on_cmbxDiffCoOp_currentIndexChanged(int index);

    void on_cmbxRallyPoints_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_chkSP_stateChanged(int arg1);

    void on_chkCoOp_stateChanged(int arg1);

    void on_chkRallyPoints_clicked();

    void on_pushButton_3_clicked();

    void on_txtServiceTag_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::Halo4ProfileDialog *ui;

    GameGPD *gpd;
    QString gpdPath;
    Halo4_TS1 titleSpecific1;
    BitArray *rallyPointBits;
    bool loaded;
    bool spChange;
    bool coopChange;

    SettingEntry tp1;
    SettingEntry tp2;
    SettingEntry tp3;

    MemoryStream *t1Stream;
};

#endif // GPDMODDERDIALOG_H
