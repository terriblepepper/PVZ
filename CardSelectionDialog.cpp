#include "CardSelectionDialog.h"
#include<qdebug.h>
#include "adventureMode.h"
CardSelectionDialog::CardSelectionDialog(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CardSelectionDialogClass())
{
	ui->setupUi(this);
	this->setStyleSheet("font-size: 18px;font-family: MiSans");
	// 获取当前窗口标志
	Qt::WindowFlags flags = windowFlags();
	// 移除关闭按钮标志
	setWindowFlags(flags & ~Qt::WindowCloseButtonHint);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	setWindowTitle("请选择你的植物");
	setWindowIcon(QIcon(":/new/prefix1/WallNut.png"));
	bgmPlay();
	card::cardSelectedMap.clear();//清空已选择的卡片以防重复选择
	createCardBtn();//绘制卡片按钮
	if (cardTotal > 28) 
	{
		if(cardTotal%7)
		{
			ui->widget->setFixedHeight(ui->widget->height() + (cardTotal / 7 - 4) * 84+offset);
		}
		else
		{
			ui->widget->setFixedHeight(ui->widget->height() + (cardTotal / 7 - 5) * 84+offset);
		}
	}
	QScrollArea* levelSelectArea = new QScrollArea(this);
	levelSelectArea->setWidgetResizable(true); // 设置为可调整大小
	levelSelectArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	levelSelectArea->setWidget(ui->widget);
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(ui->cardTab);
	layout->addWidget(levelSelectArea);
	layout->setSpacing(0);
	setLayout(layout);
	connect(ui->cancel, &QPushButton::clicked, this, &CardSelectionDialog::onCloseClicked);
	connect(ui->apply, &QPushButton::clicked, this, &CardSelectionDialog::onApplyClicked);
}

CardSelectionDialog::~CardSelectionDialog()
{
	delete ui;
	delete selectingBGM;
	delete selectingBGM_List;
}
//移动卡片
void CardSelectionDialog::moveCard(const QString& contactObjName)
{
	QString contactN = contactObjName;
	contactN.remove("btn_");
	
	if (buttonSelectedMap.contains(contactN))//点击tab栏上卡片时移除该卡片
	{
		CustomButton* rm = this->findChild<CustomButton*>(contactObjName);
		rm->setParent(ui->widget);
		//map中移除卡片
		buttonSelectedMap.remove(contactN);	
		rm->setFixedSize(60, 81);
		int counts = 0;
		for (auto& key : buttonSelectedMap.keys())//tab中移除卡片要重新排序
		{
			buttonSelectedMap[key]->move(60 * counts++, 30);
		}
		rm->move(buttonOrignPos[contactN]);
		rm->show();
		ui->cardTab->update();
		ui->widget->update();
		return;
	}
	if (buttonTotalMap.contains(contactN) && buttonSelectedMap.size()<7 && !buttonSelectedMap.contains(contactN))//选中卡片时移除卡片但不从totalMap中移除
	{
		CustomButton* rm2 = ui->widget->findChild<CustomButton*>(contactObjName);
		rm2->setParent(ui->cardTab);
		rm2->setFixedSize(60, 81);
		//将选中的卡片加入选中map
		buttonSelectedMap.insert(contactN, rm2);
		rm2->show();
		int counts = 0;
		for (auto& key : buttonSelectedMap.keys())//tab添加重新排序
		{
			buttonSelectedMap[key]->move(10+60 * counts++, 30);
		}
		ui->cardTab->update();
		ui->widget->update();
		return;
	}
}

void CardSelectionDialog::onCloseClicked()
{
	startpage::isSurvivalSelect = false;
	emit cancelGame();
	if (isAdvMode)
	{
		emit resumeLevel_BGM();
	}
	selectingBGM->stop();
	this->close();
	this->deleteLater();
}

void CardSelectionDialog::onApplyClicked()
{	
	for (auto& key : buttonSelectedMap.keys())
	{
		card::cardSelectedMap.insert(key, card::baseCardMap[key]);
	}
	selectingBGM->stop();
	this->close();
	this->deleteLater();
	emit cardIsSelected();
}

void CardSelectionDialog::createCardBtn()
{
	cardTotal = 0;//记录总共有的卡片数
	for (auto& key : card::baseCardMap.keys())
	{
		if (!(adventureGameMode::level > 5 && adventureGameMode::level < 11 && (key == "SunFlower"|| key == "TwinSunflower")))
		{
			//创建卡片矩阵
			CustomButton* seedButton = new CustomButton(ui->widget);//创建卡片按钮(父类为StackedWidget）
			//设置按钮名称
			seedButton->setObjectName("btn_" + key);
			//设置卡片图标
			seedButton->setBackgroundImage(":/new/prefix1/Card.png", QPoint(0, 0), 0.6, 0.58);
			seedButton->setOverlayImage(QString("./images/") + key + ".png", QPoint(12, 20), 0.48, 0.483);
			seedButton->setFixedSize(60, 81);
			seedButton->move(10 + (seedButton->width() + 3) * (cardTotal % 7), 26 + (seedButton->height() + 3) * (cardTotal / 7));
			buttonOrignPos.insert(key, seedButton->pos());
			//把按钮添加到map中以便后续操作
			buttonTotalMap.insert(key, seedButton);
			seedButton->setButtonName(key);
			//绘制卡片需要的阳光数
			QString displayText = QString("%1").arg(card::baseCardMap[key].cost, 3, 10, QChar(' '));
			qInfo() << "key" << key<<"level:"<<adventureGameMode::level;
			qInfo() << "Text" << displayText;
			seedButton->setDisplayText(displayText);

			//连接移动卡片的信号槽
			connect(seedButton, &QPushButton::clicked, [this, seedButton]() {
				moveCard(seedButton->objectName());
				});
			//卡片数加一
			cardTotal++;
		}
	}
}

void CardSelectionDialog::bgmPlay()
{
	selectingBGM = new(QMediaPlayer);
	selectingBGM_List = new(QMediaPlaylist);
	selectingBGM_List->addMedia(QUrl::fromLocalFile("./sound/03chooseYourSeeds.mp3"));
	selectingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
	selectingBGM->setMedia(selectingBGM_List);
	selectingBGM->setVolume(musicVolume);
	selectingBGM->play();
}
