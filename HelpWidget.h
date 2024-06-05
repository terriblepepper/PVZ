#pragma once

#include <QWidget>
#include "ui_HelpWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HelpWidgetClass; };
QT_END_NAMESPACE

class startpage;
class HelpWidget : public QWidget
{
	Q_OBJECT

public:
	HelpWidget(QWidget *parent = nullptr);
	~HelpWidget();
	void setWidget(startpage* start);
public slots:
	void goToMainMenu();

private:
	Ui::HelpWidgetClass *ui;
	startpage* mainMenu;//主菜单指针
};
