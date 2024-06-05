//utf8
#pragma once
#include<QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include<QScrollArea>
#include<QVBoxLayout>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include "ui_CardSelectionDialog.h"
#include"CustomButton.h"
#include"card.h"
#include"startpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CardSelectionDialogClass; };
QT_END_NAMESPACE

class startpage;
class card;
class CardSelectionDialog : public QWidget
{
	Q_OBJECT

public:
	CardSelectionDialog(QWidget *parent = nullptr);
	~CardSelectionDialog();
	void moveCard(const QString& contactName);//移动卡片
	bool isAdvMode = false;//判断是否在冒险模式选卡片
public slots:
	void onCloseClicked();//取消按钮
	void onApplyClicked();//应用按钮
signals:
	void cardIsSelected();
	void cancelGame();
	void resumeLevel_BGM();
private:
	Ui::CardSelectionDialogClass *ui;
	//BGM
	QMediaPlayer* selectingBGM;
	QMediaPlaylist* selectingBGM_List;
	//总的卡片地图
	QMap<QString, CustomButton*> buttonTotalMap;
	//已选择的卡片地图
	QMap<QString, CustomButton*> buttonSelectedMap;
	//记录卡片的原始坐标
	QMap<QString, QPoint> buttonOrignPos;
	void createCardBtn();
	int cardTotal;
	int offset = 38;//选择植物栏图片大小补偿
	void bgmPlay();
};
