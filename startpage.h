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
    void goToHelp();//转到帮助菜单
    void openSettingsDialog();//打开帮助菜单
    void updateSettings(int volume, const QString& difficulty, int fps);//更新设置选项
private:
    HelpWidget* Help;//帮助菜单指针
};

#endif // STARTPAGE_H
