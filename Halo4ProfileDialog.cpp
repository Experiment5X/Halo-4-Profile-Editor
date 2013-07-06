#include "Halo4ProfileDialog.h".h"
#include "ui_Halo4ProfileDialog.h"

Mission halo4Missions[] =
{
    { "Prologue", QList<int>() },
    { "Dawn", QList<int>() },
    { "Requiem", QList<int>() },
    { "Forerunner", QList<int>() },
    { "Infinity", QList<int>() },
    { "Reclaimer", QList<int>() },
    { "Shutdown", QList<int>() },
    { "Composer", QList<int>() },
    { "Midnight", QList<int>() },
    { "Epilogue", QList<int>() },
};

QString rallyPoints[] =
{
    "Alpha",
    "Bravo",
    "Charlie",
    "Delta"
};

Halo4ProfileDialog::Halo4ProfileDialog(QWidget *parent) : QDialog(parent), ui(new Ui::Halo4ProfileDialog), loaded(false), gpd(NULL), t1Stream(NULL)
{
    // add all of the rally point bit offsets
    halo4Missions[1].rallyPointBitOffsets.push_back(11);
    halo4Missions[1].rallyPointBitOffsets.push_back(18);

    halo4Missions[2].rallyPointBitOffsets.push_back(7);
    halo4Missions[2].rallyPointBitOffsets.push_back(2);

    halo4Missions[3].rallyPointBitOffsets.push_back(59);
    halo4Missions[3].rallyPointBitOffsets.push_back(57);
    halo4Missions[3].rallyPointBitOffsets.push_back(54);
    halo4Missions[3].rallyPointBitOffsets.push_back(50);

    halo4Missions[4].rallyPointBitOffsets.push_back(47);
    halo4Missions[4].rallyPointBitOffsets.push_back(44);
    halo4Missions[4].rallyPointBitOffsets.push_back(41);

    halo4Missions[5].rallyPointBitOffsets.push_back(35);
    halo4Missions[5].rallyPointBitOffsets.push_back(92);

    halo4Missions[6].rallyPointBitOffsets.push_back(87);
    halo4Missions[6].rallyPointBitOffsets.push_back(84);
    halo4Missions[6].rallyPointBitOffsets.push_back(83);
    halo4Missions[6].rallyPointBitOffsets.push_back(82);

    halo4Missions[7].rallyPointBitOffsets.push_back(41);
    halo4Missions[7].rallyPointBitOffsets.push_back(68);

    halo4Missions[8].rallyPointBitOffsets.push_back(127);
    halo4Missions[8].rallyPointBitOffsets.push_back(126);
    halo4Missions[8].rallyPointBitOffsets.push_back(125);

    halo4Missions[9].rallyPointBitOffsets.push_back(115);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
}

Q_EXPORT_PLUGIN2(Halo4Profile, Halo4ProfileDialog)

void Halo4ProfileDialog::LoadGPD(GameGpd *gpd, bool *ok, void *args)
{
    Arguments = args;

    tp1 = gpd->GetSetting(TitleSpecific1);
    tp2 = gpd->GetSetting(TitleSpecific2);
    tp3 = gpd->GetSetting(TitleSpecific3);

    if (tp1.type == 0 || tp2.type == 0 || tp3.type == 0)
    {
        QMessageBox::critical(this, "Settings Missing", "This profile is missing setting data require to use this tool.");
        *ok = false;
        return;
    }

    // read the data from the setting
    t1Stream = new MemoryIO(tp1.binaryData.data, tp1.binaryData.length);

    t1Stream->SetPosition(8);
    titleSpecific1.lookInversion = t1Stream->ReadByte();
    titleSpecific1.flightInversion = t1Stream->ReadByte();
    titleSpecific1.autolookCentering = t1Stream->ReadByte();
    titleSpecific1.holdToCrouch = t1Stream->ReadByte();

    t1Stream->SetPosition(0x0D);
    titleSpecific1.clenchProtection = t1Stream->ReadByte();
    titleSpecific1.buttonLayout = t1Stream->ReadByte();
    titleSpecific1.stickLayout = t1Stream->ReadByte();
    titleSpecific1.sensitivity = t1Stream->ReadByte();

    t1Stream->SetPosition(0x10);
    titleSpecific1.theaterCameraSpeed = t1Stream->ReadDword();
    titleSpecific1.theaterCameraTurnSensitivity = t1Stream->ReadDword();
    titleSpecific1.theaterCameraPanningToggle = t1Stream->ReadDword();
    titleSpecific1.theaterCameraThrust = t1Stream->ReadDword();

    t1Stream->SetPosition(0x2C);
    titleSpecific1.missionFlags = t1Stream->ReadDword();
    titleSpecific1.missionStatuses = t1Stream->ReadUInt64();

    t1Stream->SetPosition(0x50);
    titleSpecific1.coopMissionStatuses = t1Stream->ReadUInt64();

    t1Stream->SetPosition(0x74);
    titleSpecific1.lastInCampaign = t1Stream->ReadDword();

    t1Stream->SetPosition(0x86);
    titleSpecific1.missionsUnlockedFlags = t1Stream->ReadWord() | 1;

    t1Stream->ReadBytes(titleSpecific1.rallyPoints, 0x10);

    // the rally points are store as bit flags, so let's treat them as such
    rallyPointBits = new BitArray(titleSpecific1.rallyPoints, 0x10);

    t1Stream->SetPosition(0xF4);
    titleSpecific1.terminalFlags = t1Stream->ReadDword();
    titleSpecific1.gender = t1Stream->ReadDword();
    titleSpecific1.armorPrimaryColor = t1Stream->ReadDword();
    titleSpecific1.armorSecondaryColor = t1Stream->ReadDword();

    t1Stream->SetPosition(0x107);
    titleSpecific1.armorVisorColor = t1Stream->ReadByte();

    t1Stream->SetPosition(0x10C);
    titleSpecific1.emblemForeground = t1Stream->ReadByte();
    titleSpecific1.emblemBackground = t1Stream->ReadByte();
    titleSpecific1.hideEmblemDetails = t1Stream->ReadByte();
    titleSpecific1.emblemPrimaryColor = t1Stream->ReadByte();
    titleSpecific1.emblemSecondaryColor = t1Stream->ReadByte();
    titleSpecific1.emblemTertiaryColor = t1Stream->ReadByte();

    t1Stream->SetPosition(0x114);
    titleSpecific1.armorHelmet = t1Stream->ReadByte();
    titleSpecific1.armorTorso = t1Stream->ReadByte();

    t1Stream->SetPosition(0x117);
    titleSpecific1.armorLeftShoulder = t1Stream->ReadByte();
    titleSpecific1.armorRightShoulder = t1Stream->ReadByte();
    titleSpecific1.armorForearms = t1Stream->ReadByte();
    titleSpecific1.armorLegs = t1Stream->ReadByte();

    t1Stream->SetPosition(0x12A);
    for (DWORD i = 0; i < 5; i++)
        titleSpecific1.serviceTag[i] = t1Stream->ReadWord();

    t1Stream->SetPosition(0x135);
    titleSpecific1.stance = t1Stream->ReadByte();

    t1Stream->SetPosition(0x13B);
    titleSpecific1.playersMuted = t1Stream->ReadByte();

    t1Stream->SetPosition(0x143);
    titleSpecific1.controlVoiceChat = t1Stream->ReadByte();

    t1Stream->SetPosition(0x178);
    titleSpecific1.spartanPoints = t1Stream->ReadDword();

    t1Stream->SetPosition(0x180);
    titleSpecific1.experience = t1Stream->ReadDword();

    this->gpd = gpd;

    ui->dteCampaignTimestamp->setDateTime(QDateTime::fromTime_t(titleSpecific1.lastInCampaign));
    ui->txtServiceTag->setText(QString::fromWCharArray(titleSpecific1.serviceTag));
    ui->spnExp->setValue(titleSpecific1.experience);
    ui->spnSpartanPoints->setValue(titleSpecific1.spartanPoints);

    for (DWORD i = 0; i < 10; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setText(halo4Missions[i].name);
        if (i != 0)
        {
            item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            item->setCheckState((!!(titleSpecific1.missionsUnlockedFlags & (1 << i))) << 1);
        }
        else
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        ui->listWidget->addItem(item);
    }

    ui->listWidget->setCurrentRow(0);

    loaded = true;
    *ok = true;
}

QWidget* Halo4ProfileDialog::GetDialog()
{
    return this;
}

QString Halo4ProfileDialog::Version() const
{
    return "0.0.0.1";
}

QString Halo4ProfileDialog::ToolAuthor() const
{
    return "Expetelek";
}

QString Halo4ProfileDialog::ToolName() const
{
    return "Halo 4";
}

DWORD Halo4ProfileDialog::TitleID() const
{
    return 0x4D530919;
}

Halo4ProfileDialog::~Halo4ProfileDialog()
{
    if (gpd)
        delete gpd;
    if (t1Stream)
        delete t1Stream;
    if (ui)
        delete ui;
}

void Halo4ProfileDialog::on_listWidget_currentRowChanged(int currentRow)
{
    if (currentRow < 0)
        return;

    ui->cmbxRallyPoints->setEnabled(currentRow != 0);
    ui->chkRallyPoints->setEnabled(currentRow != 0);
    ui->chkRallyPoints->setChecked(false);

    ui->cmbxRallyPoints->clear();

    // load the correct number of rally points for the mission
    for (DWORD i = 0; i < halo4Missions[currentRow].rallyPointBitOffsets.size(); i++)
        ui->cmbxRallyPoints->addItem(rallyPoints[i]);

    // check to see if it was beaten on easy, SP
    ui->cmbxDiffSP->setCurrentIndex(0);
    ui->chkSP->setCheckState(((titleSpecific1.missionStatuses >> ((currentRow + ((currentRow < 8) ? 8 : 0)) * 4)) & 1) * 2);

    // check to see if it was beaten on easy, CoOp
    ui->cmbxDiffCoOp->setCurrentIndex(0);
    ui->chkCoOp->setCheckState(((titleSpecific1.coopMissionStatuses >> ((currentRow + ((currentRow < 8) ? 8 : 0)) * 4)) & 1) * 2);

    ui->imgMission->setPixmap(QPixmap(":/images/images/" + halo4Missions[currentRow].name.toLower().trimmed() + ".jpg"));
}

void Halo4ProfileDialog::on_cmbxDiffSP_currentIndexChanged(int index)
{
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0 || index < 0)
        return;

    spChange = false;
    ui->chkSP->setCheckState(((titleSpecific1.missionStatuses >> ((currentRow + ((currentRow < 8) ? 8 : 0)) * 4)) & (1 << index)) * 2);
}

void Halo4ProfileDialog::on_cmbxDiffCoOp_currentIndexChanged(int index)
{
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0 || index < 0)
        return;

    coopChange = false;
    ui->chkCoOp->setCheckState(((titleSpecific1.coopMissionStatuses >> ((currentRow + ((currentRow < 8) ? 8 : 0)) * 4)) & (1 << index)) * 2);
}

void Halo4ProfileDialog::on_cmbxRallyPoints_currentIndexChanged(int index)
{
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0 || index < 0)
        return;

    ui->chkRallyPoints->setCheckState(rallyPointBits->BitAt(halo4Missions[currentRow].rallyPointBitOffsets.at(index)) * 2);
}

void Halo4ProfileDialog::on_pushButton_clicked()
{
    // save the general information
    titleSpecific1.lastInCampaign = ui->dteCampaignTimestamp->dateTime().toTime_t();
    titleSpecific1.experience = ui->spnExp->value();
    titleSpecific1.spartanPoints = ui->spnSpartanPoints->value();
    if (titleSpecific1.missionFlags == 0xFFFFFFFF)
        titleSpecific1.missionFlags = 0;

    t1Stream->SetPosition(0x2C);
    t1Stream->Write(titleSpecific1.missionFlags);
    t1Stream->Write(titleSpecific1.missionStatuses);
    qDebug() << "Save: " << QString::number(titleSpecific1.missionsUnlockedFlags, 16);

    t1Stream->SetPosition(0x50);
    t1Stream->Write(titleSpecific1.coopMissionStatuses);

    t1Stream->SetPosition(0x74);
    t1Stream->Write((DWORD)titleSpecific1.lastInCampaign);

    t1Stream->SetPosition(0x86);
    t1Stream->Write(titleSpecific1.missionsUnlockedFlags);

    t1Stream->SetPosition(0x88);
    t1Stream->WriteBytes(titleSpecific1.rallyPoints, 0x10);

    t1Stream->SetPosition(0x178);
    t1Stream->Write(titleSpecific1.spartanPoints);

    t1Stream->SetPosition(0x180);
    t1Stream->Write(titleSpecific1.spartanPoints);

    ui->txtServiceTag->text().toWCharArray(titleSpecific1.serviceTag);
    titleSpecific1.serviceTag[4] = 0;

    t1Stream->SetPosition(0x12A);
    for (DWORD i = 0; i < 5; i++)
        t1Stream->Write((WORD)titleSpecific1.serviceTag[i]);

    // put all the settings next to one another, to fix the checksum
    BYTE allSettings[0xB10];
    memcpy(allSettings, tp1.binaryData.data, tp1.binaryData.length);
    memcpy(allSettings + 0x3E8, tp2.binaryData.data, tp2.binaryData.length);
    memcpy(allSettings + 0x7D0, tp3.binaryData.data, tp3.binaryData.length);

    // set the hash to all 0x99
    memset(allSettings + 0xA28, 0x99, 0x14);

    // create an sha160 object for hashing
    Botan::LibraryInitializer init;
    Botan::SHA_160 sha1;

    // hash the data
    sha1.clear();
    sha1.update(allSettings, 0xB10);
    sha1.final(tp3.binaryData.data + 0x258);

    // write the settings back to the gpd
    gpd->StartWriting();
    gpd->WriteSettingEntry(tp1);
    gpd->WriteSettingEntry(tp2);
    gpd->WriteSettingEntry(tp3);
    gpd->StopWriting();

    gpd->Close();

    emit PluginFinished();

    close();
}

void Halo4ProfileDialog::on_pushButton_2_clicked()
{
    close();
}

void Halo4ProfileDialog::on_listWidget_itemChanged(QListWidgetItem *item)
{
    if (loaded != true)
        return;

    titleSpecific1.missionsUnlockedFlags &= ~(1 << ui->listWidget->row(item));
    if (ui->listWidget->row(item) != 0)
        titleSpecific1.missionsUnlockedFlags |= (item->checkState() << (ui->listWidget->row(item) - 1));
    else
        titleSpecific1.missionsUnlockedFlags |= (item->checkState() >> 1);

    qDebug() << QString::number(titleSpecific1.missionsUnlockedFlags, 16);
}

void Halo4ProfileDialog::on_chkSP_stateChanged(int arg1)
{
    if (spChange == false)
    {
        spChange = true;
        return;
    }

    UINT64 shiftValue = ((ui->listWidget->currentRow() + ((ui->listWidget->currentRow() < 8) ? 8 : 0)) * 4) + ui->cmbxDiffSP->currentIndex();
    titleSpecific1.missionStatuses &= ~(UINT64)((UINT64)1 << shiftValue);
    titleSpecific1.missionStatuses |= ((UINT64)arg1 << (shiftValue - 1));
}

void Halo4ProfileDialog::on_chkCoOp_stateChanged(int arg1)
{
    if (coopChange == false)
    {
        coopChange = true;
        return;
    }

    UINT64 shiftValue = ((ui->listWidget->currentRow() + ((ui->listWidget->currentRow() < 8) ? 8 : 0)) * 4) + ui->cmbxDiffCoOp->currentIndex();
    titleSpecific1.coopMissionStatuses &= ~(UINT64)((UINT64)1 << shiftValue);
    titleSpecific1.coopMissionStatuses |= ((UINT64)arg1 << (shiftValue - 1));
}

void Halo4ProfileDialog::on_chkRallyPoints_clicked()
{
    if (ui->chkRallyPoints->checkState() == Qt::Checked)
        rallyPointBits->SetBit(halo4Missions[ui->listWidget->currentRow()].rallyPointBitOffsets.at(ui->cmbxRallyPoints->currentIndex()));
    else
        rallyPointBits->ClearBit(halo4Missions[ui->listWidget->currentRow()].rallyPointBitOffsets.at(ui->cmbxRallyPoints->currentIndex()));
}

void Halo4ProfileDialog::on_pushButton_3_clicked()
{
    titleSpecific1.missionStatuses = titleSpecific1.coopMissionStatuses = 0xFFFFFFFF000000FF;
    titleSpecific1.missionsUnlockedFlags = 0x3FF;
    titleSpecific1.experience = 0x7FFFFFFF;
    titleSpecific1.spartanPoints = 0x7FFFFFFF;

    // set all the rally points
    for (DWORD i = 1; i < 10; i++)
        for (DWORD x = 0; x < halo4Missions[i].rallyPointBitOffsets.size(); x++)
            rallyPointBits->SetBit(halo4Missions[i].rallyPointBitOffsets.at(x));

    // update the UI
    ui->spnExp->setValue(0x7FFFFFFF);
    ui->spnSpartanPoints->setValue(0x7FFFFFFF);

    for (DWORD i = 1; i < ui->listWidget->count(); i++)
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    ui->listWidget->setCurrentRow(0);

    ui->chkSP->setChecked(Qt::Checked);
    ui->chkCoOp->setChecked(Qt::Checked);

    ui->cmbxDiffSP->setCurrentIndex(0);
    ui->cmbxDiffCoOp->setCurrentIndex(0);
}

void Halo4ProfileDialog::on_txtServiceTag_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(arg1 != "");
}

void Halo4ProfileDialog::on_pushButton_4_clicked()
{
    QMessageBox::information(this, "Information", "<b>Campaign Progress</b><br />In order for the changes in campaign progress to take effect, there cannot be any campaign saves on the device. If there are right now that's fine, just delete them before going back into Halo 4.<br /><br />" \
                             "<b>Experience Points</b><br />Only 10,000 experience points can be modded for online use each day. Any more than that, and the changes simply won't show online. There is no maximum for offline use though.");
}
