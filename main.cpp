#include "Mainwindow.h"
#include <QApplication>
#include <loading.h>
#include "game.h"
#include"startpage.h"
#include"HelpWidget.h"
#include<qtextcodec.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ÉèÖÃÖĞÎÄ±àÂë
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

    MainWindow w;
    w.show();
//    game w;
//    w.show();
    return a.exec();
}
