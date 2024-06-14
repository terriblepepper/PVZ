#include <QApplication>
#include<qtextcodec.h>
#include <QSettings>
#include<QObject>
#include "Mainwindow.h"
#include"gameIndex.h"
#include"highprecesionQtimer.h"
//读配置文件
void readSettingsFromFile(const QString& filePath) {
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("FPS");
    fpsIndex = settings.value("fpsIndex", 2).toInt();
    settings.endGroup();

    settings.beginGroup("Audio");
    musicVolume = settings.value("musicVolume", 80).toInt();
    itemVolume = settings.value("itemVolume", 80).toInt();
    settings.endGroup();

    settings.beginGroup("Game");
    QString difficultyStr = settings.value("Difficulty", "Medium").toString();
    if (difficultyStr == "Easy")
        Difficulty = "简单";
    else if (difficultyStr == "Medium")
        Difficulty = "中等";
    else if (difficultyStr == "Hard")
        Difficulty = "困难";
    else if (difficultyStr == "Insane")
        Difficulty = "变态";
    settings.endGroup();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  
    //读配置文件
    readSettingsFromFile("./configs/settings.ini");
    MainWindow w;
    w.show();
    return a.exec();
}
