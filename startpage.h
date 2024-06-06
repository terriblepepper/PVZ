#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
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
    bool static closeWinTellItem;
public slots:
    void goToHelp();//ת�������˵�
    void openSettingsDialog();//�����ò˵�
    void updateSettings(int volume, const QString& difficulty, int fps);//��������ѡ��
    void updateVolume();
    void handleGameToMainMenu();
    void handleRestartGame(survivalGameMode* g);
    void handleRestartGame(adventureGameMode* g);
    void handleRestartGame(smallGameMode* g);
signals:
    void startSurvivalGame();
private:
    HelpWidget* Help;//�����˵�ָ��
    QWidget* currentGameMode = nullptr; // ���浱ǰ��Ϸģʽ��ָ��
    survivalGameMode* survivalGaming = nullptr;
    adventureGameMode* adventureGaming = nullptr;
    smallGameMode* smallGaming = nullptr;
    gamingMenuDialog* gamingMenu = nullptr;
    CardSelectionDialog* selectingCardsWidget = nullptr;
    QVector<Cards> cards;//��ȡ���Ŀ�Ƭjson�ļ���Ϣ
    bool isLoadCards = false;
    void loadCards(const QString& filename);
    void writeSettingsToFile(const QString& filePath);//д�������ļ�(�޸ı�Ӧ��ʱ��
};

#endif // STARTPAGE_H
