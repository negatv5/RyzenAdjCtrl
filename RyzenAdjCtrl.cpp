#include "RyzenAdjCtrl.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDateTime>
#include <iostream>
#include <Windows.h>

#define buffer_size 512
#define bufferToService_refresh_time 100
#define currentAc_refresh_time 300

void messageHandler(QtMsgType, const QMessageLogContext &, const QString &msg){
    QFile log("Service.log");
    QDateTime dt = QDateTime::currentDateTime();
    log.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&log);
    ts << dt.toString("dd.MM.yyyy hh:mm:ss ") << msg << '\n';
    log.close();
    std::cout << msg.toStdString() << std::endl;
}

RyzenAdjCtrl::RyzenAdjCtrl(QSharedMemory *bufferToService, RyzenAdjCfg *conf)
    : QObject(nullptr),
      bufferToService(bufferToService),
      conf(conf)
{
    qInstallMessageHandler(messageHandler);

    bufferToService->create(buffer_size);
    bufferToService_refresh_timer = new QTimer;
    bufferToService_refresh_timer->connect(bufferToService_refresh_timer,
                                           &QTimer::timeout, this, &RyzenAdjCtrl::recieveArgs);
    bufferToService_refresh_timer->start(bufferToService_refresh_time);

    currentAc_refresh_timer = new QTimer;
    currentAc_refresh_timer->connect(currentAc_refresh_timer,
                                     &QTimer::timeout, this, &RyzenAdjCtrl::checkCurrentACState);
    if(conf->getSettings()->autoPresetSwitchAC)
        currentAc_refresh_timer->start(currentAc_refresh_time);

    autoPresetApplyTimer = new QTimer;
    autoPresetApplyTimer->connect(autoPresetApplyTimer,
                                     &QTimer::timeout, this, &RyzenAdjCtrl::currentACStateChanged);
    if(conf->getSettings()->autoPresetApplyDurationChecked)
        autoPresetApplyTimer->start(conf->getSettings()->autoPresetApplyDuration * 1000);


    qDebug() << "RyzenAdj Service started";
    checkCurrentACState();
}

RyzenAdjCtrl::~RyzenAdjCtrl() {
    exit(0);
}

void RyzenAdjCtrl::recieveArgs(){
    char *iodata = (char*)bufferToService->data();
    QByteArray arguments;
    if (bufferToService->lock())
    {
      for (int i=0;iodata[i];i++) {
        arguments.append(iodata[i]);
        iodata[i] = '\0';
      }
      bufferToService->unlock();
    }
    if(arguments.size() > 0)
        decodeArgs(arguments);
}

void RyzenAdjCtrl::decodeArgs(QByteArray args){
    qDebug()<<"Recieved args from GUI";
    int id = -1;
    QString ryzenAdjCmdLine;
    int fanPresetId = 0;
    settingsStr* settings = conf->getSettings();

    QXmlStreamReader argsReader(args);
    argsReader.readNext();
    while(!argsReader.atEnd())
    {
        //
        if (argsReader.name() == QString("id"))
            foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                if (attr.name().toString() == "value")
                    id = attr.value().toString().toInt();
        if (argsReader.name() == QString("ryzenAdjCmdLine"))
            foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                if (attr.name().toString() == "value"){
                    ryzenAdjCmdLine = attr.value().toString();
                }
        if (argsReader.name() == QString("fanPresetId"))
            foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                if (attr.name().toString() == "value")
                    fanPresetId = attr.value().toString().toInt();
        if (argsReader.name() == QString("exit")){
            qDebug() << "Ricieved exit command";
            qDebug() << "RyzenAdj Service stoped";
            exit(0);
        }

        if (argsReader.name() == QString("autoPresetApplyDurationChecked"))
            foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                if (attr.name().toString() == "value"){
                        settings->autoPresetApplyDurationChecked = attr.value().toString().toInt();
                        qDebug() << "autoPresetApplyDurationChecked set to " << settings->autoPresetApplyDurationChecked;
                        autoPresetApplyTimer->stop();
                        if(conf->getSettings()->autoPresetApplyDurationChecked)
                            autoPresetApplyTimer->start(conf->getSettings()->autoPresetApplyDuration * 1000);
                    }
        if (argsReader.name() == QString("autoPresetApplyDuration"))
            foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                if (attr.name().toString() == "value"){
                        settings->autoPresetApplyDuration = attr.value().toString().toInt();
                        qDebug() << "autoPresetApplyDuration set to " << settings->autoPresetApplyDuration;
                        autoPresetApplyTimer->stop();
                        if(conf->getSettings()->autoPresetApplyDurationChecked)
                            autoPresetApplyTimer->start(conf->getSettings()->autoPresetApplyDuration * 1000);
                    }

            if (argsReader.name() == QString("settingsReloadDurationChecked"))
                foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                    if (attr.name().toString() == "value"){
                            settings->settingsReloadDurationChecked = attr.value().toString().toInt();
                            qDebug() << "settingsReloadDurationChecked set to " << settings->settingsReloadDurationChecked;
                        }
            if (argsReader.name() == QString("settingsReloadDuration"))
                foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                    if (attr.name().toString() == "value"){
                            settings->settingsReloadDuration = attr.value().toString().toInt();
                            qDebug() << "settingsReloadDuration set to " << settings->settingsReloadDuration;
                        }

            if (argsReader.name() == QString("autoPresetSwitchAC"))
                foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                    if (attr.name().toString() == "value"){
                            settings->autoPresetApplyDurationChecked = attr.value().toString().toInt();
                            qDebug() << "autoPresetApplyDurationChecked set to " << settings->autoPresetApplyDurationChecked;
                            currentAc_refresh_timer->stop();
                            if(conf->getSettings()->autoPresetSwitchAC)
                                currentAc_refresh_timer->start(currentAc_refresh_time);
                        }
            if (argsReader.name() == QString("dcStatePresetId"))
                foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                    if (attr.name().toString() == "value"){
                            settings->dcStatePresetId = attr.value().toString().toInt();
                            qDebug() << "dcStatePresetId set to " << settings->dcStatePresetId;
                            checkCurrentACState();
                        }
            if (argsReader.name() == QString("acStatePresetId"))
                foreach(const QXmlStreamAttribute &attr, argsReader.attributes())
                    if (attr.name().toString() == "value"){
                            settings->acStatePresetId = attr.value().toString().toInt();
                            qDebug() << "acStatePresetId set to " << settings->acStatePresetId;
                            checkCurrentACState();
                        }
        //

        argsReader.readNext();
    }

    if(id != -1)
        qDebug()<<"Preset ID: "<<id;
    if(ryzenAdjCmdLine.size() > 0)
        RyzenAdjSendCommand(ryzenAdjCmdLine);
    if(fanPresetId > 0) {
        QString fanArguments;
        switch(fanPresetId){
        case 1:
            fanArguments = "plan windows";
            break;
        case 2:
            fanArguments = "plan silent";
            break;
        case 3:
            fanArguments = "plan performance";
            break;
        case 4:
            fanArguments = "plan turbo";
            break;
        case 5:
            fanArguments = "fan --plan windows --cpu 30c:0%,40c:5%,50c:10%,60c:20%,70c:35%,80c:55%,90c:65%,100c:65% --gpu 30c:0%,40c:5%,50c:10%,60c:20%,70c:35%,80c:55%,90c:65%,100c:65%";
            break;
        }
        atrofacSendCommand(fanArguments);
    }
}

void RyzenAdjCtrl::checkCurrentACState(){
    SYSTEM_POWER_STATUS sps;
    if (GetSystemPowerStatus(&sps))
        if(currentACState != ACState(sps.ACLineStatus)) {
            currentACState = ACState(sps.ACLineStatus);
            currentACStateChanged();
        }
}

void RyzenAdjCtrl::currentACStateChanged(){
    qDebug() << "Current state changed to" <<
                ((currentACState == Battery) ? "DC State" : "AC State");

    if(conf->getSettings()->autoPresetSwitchAC)
        loadPreset((currentACState == Battery)
                   ? (conf->getSettings()->dcStatePresetId)
                   : (conf->getSettings()->acStatePresetId));
}

void RyzenAdjCtrl::loadPreset(int currentPresetId){
    qDebug()<<"Load preset ID:" << currentPresetId << "...";
    if(conf->getPresets()[currentPresetId].cmdOutputValue.size() > 0)
        RyzenAdjSendCommand(conf->getPresets()[currentPresetId].cmdOutputValue);

    if(conf->getPresets()[currentPresetId].fanPresetId > 0) {
        QString fanArguments;
        switch(conf->getPresets()[currentPresetId].fanPresetId){
        case 1:
            fanArguments = "plan windows";
            break;
        case 2:
            fanArguments = "plan silent";
            break;
        case 3:
            fanArguments = "plan performance";
            break;
        case 4:
            fanArguments = "plan turbo";
            break;
        case 5:
            fanArguments = "fan --plan windows --cpu 30c:0%,40c:5%,50c:10%,60c:20%,70c:35%,80c:55%,90c:65%,100c:65% --gpu 30c:0%,40c:5%,50c:10%,60c:20%,70c:35%,80c:55%,90c:65%,100c:65%";
            break;
        }
        atrofacSendCommand(fanArguments);
    }
}

void RyzenAdjCtrl::RyzenAdjSendCommand(QString arguments) {
    qDebug()<<"RyzenAdj Commandline: "<<arguments;
    QStringList argumentsList = arguments.split(" ",Qt::SkipEmptyParts);
    QProcess process;
    QString output;
    for(int i = 0; i < 3; i++){
        process.start("Binaries/ryzenadj.exe", argumentsList);
        if( !process.waitForStarted() || !process.waitForFinished())
            return;
        output = process.readAllStandardOutput();
        qDebug() << "RyzenAdj output:" << output;
        if (!output.contains("Err"))
            break;
    }
}

void RyzenAdjCtrl::atrofacSendCommand(QString arguments) {
    qDebug()<<"atrofac Commandline: "<<arguments;
    QStringList argumentsList = arguments.split(" ",Qt::SkipEmptyParts);
    QProcess process;
    QString output;
    for(int i = 0; i < 3; i++){
        process.start("Binaries/atrofac-cli.exe", argumentsList);
        if( !process.waitForStarted() || !process.waitForFinished())
            return;
        output = process.readAllStandardError();
        qDebug() << "atrofac output:" << output;
        if (!output.contains("Err"))
            break;
    }
}