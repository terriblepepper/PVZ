#include <QApplication>
#include<qtextcodec.h>
#include <QSettings>
#include<QObject>
#include "Mainwindow.h"
#include"gameIndex.h"

//�������ļ�
void readSettingsFromFile(const QString& filePath) {
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("FPS");
    fpsIndex = settings.value("fpsIndex", 2).toInt();
    settings.endGroup();

    settings.beginGroup("Audio");
    musicVolume = settings.value("musicVolume", 80).toInt();
    settings.endGroup();

    settings.beginGroup("Game");
    QString difficultyStr = settings.value("Difficulty", "Medium").toString();
    if (difficultyStr == "Easy")
        Difficulty = "��";
    else if (difficultyStr == "Medium")
        Difficulty = "�е�";
    else if (difficultyStr == "Hard")
        Difficulty = "����";
    else if (difficultyStr == "Insane")
        Difficulty = "��̬";
    settings.endGroup();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //�������ı���
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec* codec = QTextCodec::codecForName("GBK");
#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif
    //�������ļ�
    readSettingsFromFile("./configs/settings.ini");
    MainWindow w;
    w.show();
    return a.exec();
}
