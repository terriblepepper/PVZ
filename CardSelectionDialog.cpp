#include "CardSelectionDialog.h"
#include<qdebug.h>
#include "adventureMode.h"
CardSelectionDialog::CardSelectionDialog(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CardSelectionDialogClass())
{
	ui->setupUi(this);
	this->setStyleSheet("font-size: 18px;font-family: MiSans");
	// ��ȡ��ǰ���ڱ�־
	Qt::WindowFlags flags = windowFlags();
	// �Ƴ��رհ�ť��־
	setWindowFlags(flags & ~Qt::WindowCloseButtonHint);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	setWindowTitle("��ѡ�����ֲ��");
	setWindowIcon(QIcon(":/new/prefix1/WallNut.png"));
	bgmPlay();
	card::cardSelectedMap.clear();//�����ѡ��Ŀ�Ƭ�Է��ظ�ѡ��
	createCardBtn();//���ƿ�Ƭ��ť
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
	levelSelectArea->setWidgetResizable(true); // ����Ϊ�ɵ�����С
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
//�ƶ���Ƭ
void CardSelectionDialog::moveCard(const QString& contactObjName)
{
	QString contactN = contactObjName;
	contactN.remove("btn_");
	
	if (buttonSelectedMap.contains(contactN))//���tab���Ͽ�Ƭʱ�Ƴ��ÿ�Ƭ
	{
		CustomButton* rm = this->findChild<CustomButton*>(contactObjName);
		rm->setParent(ui->widget);
		//map���Ƴ���Ƭ
		buttonSelectedMap.remove(contactN);	
		rm->setFixedSize(60, 81);
		int counts = 0;
		for (auto& key : buttonSelectedMap.keys())//tab���Ƴ���ƬҪ��������
		{
			buttonSelectedMap[key]->move(60 * counts++, 30);
		}
		rm->move(buttonOrignPos[contactN]);
		rm->show();
		ui->cardTab->update();
		ui->widget->update();
		return;
	}
	if (buttonTotalMap.contains(contactN) && buttonSelectedMap.size()<7 && !buttonSelectedMap.contains(contactN))//ѡ�п�Ƭʱ�Ƴ���Ƭ������totalMap���Ƴ�
	{
		CustomButton* rm2 = ui->widget->findChild<CustomButton*>(contactObjName);
		rm2->setParent(ui->cardTab);
		rm2->setFixedSize(60, 81);
		//��ѡ�еĿ�Ƭ����ѡ��map
		buttonSelectedMap.insert(contactN, rm2);
		rm2->show();
		int counts = 0;
		for (auto& key : buttonSelectedMap.keys())//tab�����������
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
	cardTotal = 0;//��¼�ܹ��еĿ�Ƭ��
	for (auto& key : card::baseCardMap.keys())
	{
		if (!(adventureGameMode::level > 5 && adventureGameMode::level < 11 && (key == "SunFlower"|| key == "TwinSunflower")))
		{
			//������Ƭ����
			CustomButton* seedButton = new CustomButton(ui->widget);//������Ƭ��ť(����ΪStackedWidget��
			//���ð�ť����
			seedButton->setObjectName("btn_" + key);
			//���ÿ�Ƭͼ��
			seedButton->setBackgroundImage(":/new/prefix1/Card.png", QPoint(0, 0), 0.6, 0.58);
			seedButton->setOverlayImage(QString("./images/") + key + ".png", QPoint(12, 20), 0.48, 0.483);
			seedButton->setFixedSize(60, 81);
			seedButton->move(10 + (seedButton->width() + 3) * (cardTotal % 7), 26 + (seedButton->height() + 3) * (cardTotal / 7));
			buttonOrignPos.insert(key, seedButton->pos());
			//�Ѱ�ť��ӵ�map���Ա��������
			buttonTotalMap.insert(key, seedButton);
			seedButton->setButtonName(key);
			//���ƿ�Ƭ��Ҫ��������
			QString displayText = QString("%1").arg(card::baseCardMap[key].cost, 3, 10, QChar(' '));
			qInfo() << "key" << key<<"level:"<<adventureGameMode::level;
			qInfo() << "Text" << displayText;
			seedButton->setDisplayText(displayText);

			//�����ƶ���Ƭ���źŲ�
			connect(seedButton, &QPushButton::clicked, [this, seedButton]() {
				moveCard(seedButton->objectName());
				});
			//��Ƭ����һ
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
