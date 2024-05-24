#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#ifndef STARTPAGE_H
#define STARTPAGE_H
#include <QWidget>
#include <QPainter>
#include"gameSettings.h"

class HelpWidget;
class startpage : public QWidget
{
    Q_OBJECT
public:
    QPainter* mpainter_1;
    void paintEvent(QPaintEvent *event);
    void initSettings();
    explicit startpage(QWidget *parent = nullptr);
    void setWidget(HelpWidget* help);
    void initCardCool();
public slots:
    void goToHelp();//ת�������˵�
    void openSettingsDialog();//�򿪰����˵�
    void updateSettings(int volume, const QString& difficulty, int fps);//��������ѡ��
private:
    HelpWidget* Help;//�����˵�ָ��
};

#endif // STARTPAGE_H
