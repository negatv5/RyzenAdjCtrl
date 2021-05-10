#include "CtrlSettings.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QRegularExpression>

#include <QDebug>

CtrlSettings::CtrlSettings()
    : presetsBuffer(new presetStr[4])
{
    QFile configQFile("Config.xml");
    if (!configQFile.exists()) saveSettings();
    else openSettings();

    QFile presetsQFile("Presets.xml");
    if (!presetsQFile.exists()){
        for(int i = 0;i < 4; i++)
            presetsBuffer[i].presetId = i;
        presetsBuffer[0].presetName = "Battery Saver";
        presetsBuffer[1].presetName = "Better Battery";
        presetsBuffer[2].presetName = "Balanced";
        presetsBuffer[3].presetName = "Maximum Perfomance";
        savePresets();
    }
    else
        openPresets();
}

CtrlSettings::~CtrlSettings() {
    saveSettings();
    savePresets();
}

bool CtrlSettings::saveSettings() {
    QFile configQFile("Config.xml");
    configQFile.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&configQFile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Settings");
    //
        xmlWriter.writeStartElement("useAgent");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.useAgent));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("showNotifications");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.showNotifications));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("showReloadStyleSheetButton");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.showReloadStyleSheetButton));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("showNotificationToDisableAutoSwitcher");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.showNotificationToDisableAutoSwitcher));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("autoPresetApplyDurationChecked");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.autoPresetApplyDurationChecked));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("autoPresetApplyDuration");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.autoPresetApplyDuration));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("autoPresetSwitchAC");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.autoPresetSwitchAC));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("dcStatePresetId");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.dcStatePresetId));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("acStatePresetId");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.acStatePresetId));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("epmAutoPresetSwitch");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.epmAutoPresetSwitch));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("epmBatterySaverPresetId");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.epmBatterySaverPresetId));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("epmBetterBatteryPresetId");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.epmBetterBatteryPresetId));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("epmBalancedPresetId");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.epmBalancedPresetId));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("epmMaximumPerfomancePresetId");
            xmlWriter.writeAttribute("value", QString::number(settingsBuffer.epmMaximumPerfomancePresetId));
        xmlWriter.writeEndElement();
    //
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    configQFile.close();
    return true;
}

bool CtrlSettings::openSettings(){
    QFile configQFile("Config.xml");
    configQFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&configQFile);
    xmlReader.readNext();
    while(!xmlReader.atEnd())
    {
        //
        if (xmlReader.name() == QString("useAgent"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.useAgent =
                            attr.value().toString().toInt();
        if (xmlReader.name() == QString("showNotifications"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.showNotifications =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("showNotificationToDisableAutoSwitcher"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.showNotificationToDisableAutoSwitcher =
                            attr.value().toString().toInt();
        if (xmlReader.name() == QString("showReloadStyleSheetButton"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.showReloadStyleSheetButton =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("autoPresetApplyDurationChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.autoPresetApplyDurationChecked =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("autoPresetApplyDuration"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.autoPresetApplyDuration =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("autoPresetSwitchAC"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.autoPresetSwitchAC =
                            attr.value().toString().toInt();
        if (xmlReader.name() == QString("dcStatePresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.dcStatePresetId =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("acStatePresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.acStatePresetId =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("epmAutoPresetSwitch"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.epmAutoPresetSwitch =
                            attr.value().toString().toInt();
        if (xmlReader.name() == QString("epmBatterySaverPresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.epmBatterySaverPresetId =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("epmBetterBatteryPresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.epmBetterBatteryPresetId =
                            attr.value().toString().toInt();
        if (xmlReader.name() == QString("epmBalancedPresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.epmBalancedPresetId =
                            attr.value().toString().toInt();

        if (xmlReader.name() == QString("epmMaximumPerfomancePresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    settingsBuffer.epmMaximumPerfomancePresetId =
                            attr.value().toString().toInt();
        //
        xmlReader.readNext();
    }
    configQFile.close();
    return true;
}

bool CtrlSettings::savePresets() {
    QFile presetsQFile("Presets.xml");
    presetsQFile.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&presetsQFile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Presets");
    //
    for(int i = 0;i < 4;i++){
        xmlWriter.writeStartElement("Preset");

            xmlWriter.writeStartElement("presetId");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].presetId));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("presetName");
                xmlWriter.writeAttribute("value", presetsBuffer[i].presetName);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("fanPresetId");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].fanPresetId));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("tempLimitValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].tempLimitValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("tempLimitChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].tempLimitChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("apuSkinValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].apuSkinValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("apuSkinChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].apuSkinChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("stampLimitValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].stampLimitValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("stampLimitChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].stampLimitChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("fastLimitValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].fastLimitValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("fastLimitChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].fastLimitChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("fastTimeValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].fastTimeValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("fastTimeChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].fastTimeChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("slowLimitValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].slowLimitValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("slowLimitChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].slowLimitChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("slowTimeValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].slowTimeValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("slowTimeChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].slowTimeChecked));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("vrmCurrentValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].vrmCurrentValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("vrmCurrentChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].vrmCurrentChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("vrmMaxValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].vrmMaxValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("vrmMaxChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].vrmMaxChecked));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("minFclkValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minFclkValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("minFclkChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minFclkChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxFclkValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxFclkValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxFclkChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxFclkChecked));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("minGfxclkValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minGfxclkValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("minGfxclkChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minGfxclkChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxGfxclkValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxGfxclkValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxGfxclkChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxGfxclkChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("minSocclkValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minSocclkValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("minSocclkChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minSocclkChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxSocclkValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxSocclkValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxSocclkChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxSocclkChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("minVcnValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minVcnValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("minVcnChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].minVcnChecked));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxVcnValue");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxVcnValue));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("maxVcnChecked");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].maxVcnChecked));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("smuMaxPerfomance");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].smuMaxPerfomance));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("smuPowerSaving");
                xmlWriter.writeAttribute("value", QString::number(presetsBuffer[i].smuPowerSaving));
            xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
    }
    //
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    presetsQFile.close();
    return true;
}

bool CtrlSettings::openPresets(){
    QFile presetsQFile("Presets.xml");
    presetsQFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&presetsQFile);
    xmlReader.readNext();
    int i = 0;
    while(!xmlReader.atEnd())
    {
        //
        if (xmlReader.name() == QString("presetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value") {
                    i = attr.value().toString().toInt();
                    presetsBuffer[i].presetId = i;
                }
        if (xmlReader.name() == QString("presetName"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    presetsBuffer[i].presetName =
                            attr.value().toString();

        if (xmlReader.name() == QString("fanPresetId"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
                    presetsBuffer[i].fanPresetId = attr.value().toString().toInt();

        if (xmlReader.name() == QString("tempLimitValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].tempLimitValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("tempLimitChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].tempLimitChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("apuSkinValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].apuSkinValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("apuSkinChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].apuSkinChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("stampLimitValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].stampLimitValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("stampLimitChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].stampLimitChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("fastLimitValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].fastLimitValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("fastLimitChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].fastLimitChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("fastTimeValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].fastTimeValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("fastTimeChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].fastTimeChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("slowLimitValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].slowLimitValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("slowLimitChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].slowLimitChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("slowTimeValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].slowTimeValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("slowTimeChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].slowTimeChecked = attr.value().toString().toInt();

        if (xmlReader.name() == QString("vrmCurrentValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].vrmCurrentValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("vrmCurrentChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].vrmCurrentChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("vrmMaxValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].vrmMaxValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("vrmMaxChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].vrmMaxChecked = attr.value().toString().toInt();

        if (xmlReader.name() == QString("minFclkValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minFclkValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("minFclkChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minFclkChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxFclkValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxFclkValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxFclkChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxFclkChecked = attr.value().toString().toInt();

        if (xmlReader.name() == QString("minGfxclkValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minGfxclkValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("minGfxclkChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minGfxclkChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxGfxclkValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxGfxclkValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxGfxclkChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxGfxclkChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("minSocclkValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minSocclkValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("minSocclkChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minSocclkChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxSocclkValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxSocclkValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxSocclkChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxSocclkChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("minVcnValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minVcnValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("minVcnChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].minVcnChecked = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxVcnValue"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxVcnValue = attr.value().toString().toInt();
        if (xmlReader.name() == QString("maxVcnChecked"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].maxVcnChecked = attr.value().toString().toInt();


        if (xmlReader.name() == QString("smuMaxPerfomance"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].smuMaxPerfomance = attr.value().toString().toInt();
        if (xmlReader.name() == QString("smuPowerSaving"))
            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                if (attr.name().toString() == "value")
            presetsBuffer[i].smuPowerSaving = attr.value().toString().toInt();
        //
        xmlReader.readNext();
    }
    presetsQFile.close();
    return true;
}
