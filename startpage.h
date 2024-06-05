//utf8
#ifndef STARTPAGE_H
#define STARTPAGE_H
#include <QWidget>
#include <QPainter>
#include <QIcon>
#include<qmessagebox.h>
#include <QPushButton>
#include <QKeyEvent>
#include"gameSettings.h"
#include"gamingMenu.h"
#include"adventureMode.h"
#include "survivalMode.h"
#include"smallgameMode.h"
#include"puzzleMode.h"
#include"gameIndex.h"
#include"Mainwindow.h"//bgm
#include "HelpWidget.h"
#include"card.h"
#include"CardSelectionDialog.h"
#include"highprecesionQtimer.h"


struct Cards {
    QString name;
    int cool;
    int cost;
};

class HelpWidget;
class adventureGameMode;
class survivalGameMode;
class smallGameMode;
class puzzleMode;
class gamingMenuDialog;
class CardSelectionDialog;
class startpage : public QWidget
{
    Q_OBJECT
public:
    QPainter* mpainter_1;
    void paintEvent(QPaintEvent *event);
    explicit startpage(QWidget *parent = nullptr);
    void setWidget(HelpWidget* help);
    void initCardInformation();
    static bool isSurvivalSelect;
public slots:
    void goToHelp();//转到帮助菜单
    void openSettingsDialog();//打开设置菜单
    void updateSettings(int volumeBGM,int volumeItem, const QString& difficulty, int fps);//更新设置选项
    void updateVolume();
    void handleGameToMainMenu();
    void handleRestartGame(survivalGameMode* g1);
    void handleRestartGame(adventureGameMode* g2);
    void handleRestartGame(smallGameMode* g3);
    void handleRestartGame(puzzleMode* g4);
signals:
    void startSurvivalGame();
private:
    HelpWidget* Help;//帮助菜单指针
    QWidget* currentGameMode = nullptr; // 保存当前游戏模式的指针
    survivalGameMode* survivalGaming = nullptr;
    adventureGameMode* adventureGaming = nullptr;
    smallGameMode* smallGaming = nullptr;
    puzzleMode* puzzleGaming = nullptr;
    gamingMenuDialog* gamingMenu = nullptr;
    CardSelectionDialog* selectingCardsWidget = nullptr;
    QVector<Cards> cards;//读取出的卡片json文件信息
    bool isLoadCards = false;
    void loadCards(const QString& filename);
    void writeSettingsToFile(const QString& filePath);//写回配置文件(修改被应用时）
};

#endif // STARTPAGE_H
