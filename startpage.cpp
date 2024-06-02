#include "startpage.h"

bool startpage::closeWinTellItem = true;//提醒场景能否删除物品对象
bool startpage::isSurvivalSelect = false;
startpage::startpage(QWidget *parent)
    : QWidget{parent}
{
    initCardInformation();//初始时从json文件读入card数据
    this->setFixedSize(900,600);
    this->setWindowTitle("PlantsVsZombies");
    this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png"));
    this->setStyleSheet("font-size: 18px;font-family: MiSans");
    mpainter_1=new QPainter(this);
    QPushButton* btn_adventure=new QPushButton(this);
    QPushButton* btn_smallgame=new QPushButton(this);
    QPushButton* btn_yizhigame=new QPushButton(this);
    QPushButton* btn_survivegame=new QPushButton(this);
    QPushButton* btn_options=new QPushButton(this);
    QPushButton* btn_help = new QPushButton(this);
    QPushButton* btn_exit = new QPushButton(this);
    btn_options->setGeometry(644, 490, 72, 30);
    btn_options->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-options.png);" // 鼠标悬停样式 
                         "}");
    btn_help->setGeometry(728, 521, 59, 29);
    btn_help->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-help.png);" // 鼠标悬停样式 
                         "}");
    btn_exit->setGeometry(811, 510, 60, 30);
    btn_exit->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-exit.png);" // 鼠标悬停样式 
                         "}");
    btn_adventure->setGeometry(450,60,340,120);
    btn_adventure->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明
                         "border-image:url(:/new/prefix1/adventure.png);" // 设置按钮样式，包括背景图片
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/adventure1.png);" // 鼠标悬停样式
                         "}"
                         );
    btn_smallgame->setGeometry(450,150,320,130);
    btn_smallgame->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/play.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/play1.png);"
                         "}"
                         );
    btn_yizhigame->setGeometry(460,230,290,130);
    btn_yizhigame->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/yizi.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/yizi1.png);"
                         "}"
                         );
    btn_survivegame->setGeometry(460,320,280,120);
    btn_survivegame->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/survive.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/survive1.png);"
                         "}"
                         );
    //进入冒险模式
    connect(btn_adventure, &QPushButton::clicked, [this]() {
        gamingMenu = new(gamingMenuDialog);//创建游戏菜单
        adventureGaming = new (adventureGameMode);//创建游戏窗口
        currentGameMode = adventureGaming;
        gamingMenu->getCurrentGameMode(currentGameMode);
        gamingMenu->getMainMenuPoints(this);
        gamingMenu->getGameWindow(adventureGaming);
        adventureGaming->getGamingMenu(gamingMenu);
        //initCardInformation();
        this->close();
        adventureGaming->show();
        //接收回到菜单信号进行连接
        connect(gamingMenu, &gamingMenuDialog::gameToMainMenu, this, &startpage::handleGameToMainMenu);
        connect(adventureGaming,&adventureGameMode::onBackClicked,this,&startpage::handleGameToMainMenu);
        //接收重新开始信号
        connect(gamingMenu, static_cast<void(gamingMenuDialog::*)(adventureGameMode*)>(&gamingMenuDialog::restartGame),
            this, static_cast<void(startpage::*)(adventureGameMode*)>(&startpage::handleRestartGame));
        //接收更新音量信号
        connect(gamingMenu, &gamingMenuDialog::changeVolume, this, &startpage::updateVolume);
        //接收停止主菜单BGM信号
        connect(adventureGaming, &adventureGameMode::stopLoadingBGM, loadingBGM, &QMediaPlayer::stop);
        //接收游戏失败确认信号
        connect(adventureGaming, &adventureGameMode::gameFinish, this, &startpage::handleGameToMainMenu);
        //接收恢复关卡界面BGM信号
        connect(adventureGaming, &adventureGameMode::resumeLoadingBGM, loadingBGM, &QMediaPlayer::play);
        });
        // 进入生存模式
        connect(btn_survivegame,&QPushButton::clicked,[this](){
        loadingBGM->stop();
        selectingCardsWidget = new(CardSelectionDialog);//创建卡片选择窗口
        this->close();
        selectingCardsWidget->show();
        connect(selectingCardsWidget, &CardSelectionDialog::cancelGame, this, &startpage::handleGameToMainMenu);
        connect(selectingCardsWidget, &CardSelectionDialog::cardIsSelected, [this]() {
            /*设置卡片冷却时间（在card.cpp设置会出现赋值失效）*/
            isSurvivalSelect = true;
            initCardInformation();
            gamingMenu = new(gamingMenuDialog);//创建游戏菜单
            survivalGaming = new (survivalGameMode);//创建游戏窗口
            gamingMenu->getCurrentGameMode(currentGameMode);
            gamingMenu->getMainMenuPoints(this);
            gamingMenu->getGameWindow(survivalGaming);
            survivalGaming->getGamingMenu(gamingMenu);
            currentGameMode = survivalGaming;
            survivalGaming->show();
            //接收回到菜单信号进行连接
            connect(gamingMenu, &gamingMenuDialog::gameToMainMenu, this, &startpage::handleGameToMainMenu);
            //接收重新开始信号
            connect(gamingMenu, static_cast<void(gamingMenuDialog::*)(survivalGameMode*)>(&gamingMenuDialog::restartGame),
                this, static_cast<void(startpage::*)(survivalGameMode*)>(&startpage::handleRestartGame));
            //接收更新音量信号
            connect(gamingMenu, &gamingMenuDialog::changeVolume, this, &startpage::updateVolume);
            //接收游戏失败确认信号
            connect(survivalGaming, &survivalGameMode::gameOver, this, &startpage::handleGameToMainMenu);
            });
    });
    //退出
    connect(btn_exit, &QPushButton::clicked, [this]() {
        QMessageBox exitBox;
        exitBox.setWindowTitle("退出");
        exitBox.setText("是否要退出游戏?");
        exitBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        exitBox.setDefaultButton(QMessageBox::No);
        int ret = exitBox.exec();

        switch (ret) {
        case QMessageBox::Yes:
            writeSettingsToFile("./configs/settings.ini");
            exit(1);
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
        });
    //帮助
    connect(btn_help, &QPushButton::clicked,this,&startpage::goToHelp);
    //设置
    connect(btn_options, &QPushButton::clicked, this, &startpage::openSettingsDialog); 
}

void startpage::setWidget(HelpWidget* help)
{
    Help = help;
}

void startpage::initCardInformation()
{
    if (!isLoadCards) 
    {
        loadCards(":/cards/configs/cards.json"); // 假设文件路径在资源目录中
    // 更新 card 类中的静态成员
        for (const auto& cardData : cards) {
                CardsData Cards;
                Cards.name = cardData.name;
                Cards.cool = cardData.cool;
                Cards.cost = cardData.cost;
                card::baseCardMap.insert(cardData.name, Cards);
                //qInfo() << "load json" << cardData.name<<cardData.cool;
        }
        isLoadCards = true;
        return;
    }
    else
    {
        for (const auto& key : card::cardSelectedMap.keys()) {
            card::cardSelectedMap[key].cool = card::baseCardMap[key].cool * fpsIndex;
            //qInfo() << fpsIndex << card::cardSelectedMap[key].cool;
        }
        
    } 
    
}

void startpage::goToHelp()
{    
        this->hide();
        Help->setEnabled(true);
        Help->show();
}

void startpage::openSettingsDialog()
{
    SettingsDialog settingsDialog(this);
    connect(&settingsDialog, &SettingsDialog::settingsChanged, this, &startpage::updateSettings);
    settingsDialog.exec();
}

void startpage::updateSettings(int volume, const QString& difficulty, int fps)
{
    musicVolume = volume;
    loadingBGM->setVolume(musicVolume);
    Difficulty = difficulty;
    fpsIndex = fps / 30;//设置刷新帧数
    writeSettingsToFile("./configs/settings.ini");
}

void startpage::updateVolume()//接收游戏中变化音量信号的处理
{
    loadingBGM->setVolume(musicVolume);
}

void startpage::handleGameToMainMenu()
{
    startpage::closeWinTellItem = false;
    bool change = true;
    QTimer::singleShot(1100, [change]() { startpage::closeWinTellItem = change; });
    loadingBGM->play();
        if (isSurvivalSelect && survivalGaming != nullptr)
        {
            survivalGaming->close();
            survivalGaming->deleteLater();
            survivalGaming = nullptr;
            gamingMenu->close();
            gamingMenu->deleteLater();
        }
        else if (adventureGaming != nullptr && currentGameMode == adventureGaming)
        {
            adventureGaming->close();
            adventureGaming->deleteLater();
            adventureGaming = nullptr;
            gamingMenu->close();
            gamingMenu->deleteLater();
        }
        
    this->show();
}

void startpage::handleRestartGame(survivalGameMode* g)
{
    initCardInformation();
    survivalGaming = g;
    startpage::closeWinTellItem = false;
    bool change = true;
    QTimer::singleShot(1100, [change]() { startpage::closeWinTellItem = change; });
    currentGameMode = survivalGaming;
}

void startpage::handleRestartGame(adventureGameMode* g2)
{
    adventureGaming = g2;
    currentGameMode = adventureGaming;
    startpage::closeWinTellItem = false;
    bool change = true;
    QTimer::singleShot(1100, [change]() { startpage::closeWinTellItem = change; });
    connect(adventureGaming, &adventureGameMode::onBackClicked, this, &startpage::handleGameToMainMenu);
}

void startpage::loadCards(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file" << filename;
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);

    if (document.isNull() || !document.isArray()) {
        qWarning() << "Invalid JSON format";
        return;
    }

    QJsonArray jsonArray = document.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        Cards card;
        card.name = obj["name"].toString();
        card.cool = obj["cool"].toInt();
        card.cost = obj["cost"].toInt();
        cards.append(card);
    }
}

void startpage::writeSettingsToFile(const QString& filePath)
{
    QSettings settings(filePath, QSettings::IniFormat);

    settings.beginGroup("FPS");
    settings.setValue("fpsIndex", fpsIndex);
    settings.endGroup();

    settings.beginGroup("Audio");
    settings.setValue("musicVolume", musicVolume);
    settings.endGroup();

    settings.beginGroup("Game");
    if(Difficulty == "简单")
        settings.setValue("Difficulty", "Easy");
    if(Difficulty == "中等")
        settings.setValue("Difficulty", "Medium");
    if(Difficulty == "困难")
        settings.setValue("Difficulty", "Hard");
    if(Difficulty == "变态")
        settings.setValue("Difficulty", "Insane");
    settings.endGroup();
}

void startpage::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // 开始绘制
    QImage img(":/new/prefix1/Surface.png"); // 加载图片资源
    mpainter_1->drawImage(QRect(0, 0, 900, 600), img); // 在主窗口绘制图片
    mpainter_1->end(); // 结束绘制
}


