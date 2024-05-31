#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
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
	void moveCard(const QString& contactName);//�ƶ���Ƭ
	bool isAdvMode = false;//�ж��Ƿ���ð��ģʽѡ��Ƭ
public slots:
	void onCloseClicked();//ȡ����ť
	void onApplyClicked();//Ӧ�ð�ť
signals:
	void cardIsSelected();
	void cancelGame();
	void resumeLevel_BGM();
private:
	Ui::CardSelectionDialogClass *ui;
	//BGM
	QMediaPlayer* selectingBGM;
	QMediaPlaylist* selectingBGM_List;
	//�ܵĿ�Ƭ��ͼ
	QMap<QString, CustomButton*> buttonTotalMap;
	//��ѡ��Ŀ�Ƭ��ͼ
	QMap<QString, CustomButton*> buttonSelectedMap;
	//��¼��Ƭ��ԭʼ����
	QMap<QString, QPoint> buttonOrignPos;
	void createCardBtn();
	int cardTotal;
	int offset = 38;//ѡ��ֲ����ͼƬ��С����
	void bgmPlay();
};
