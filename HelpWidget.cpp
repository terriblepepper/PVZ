#include "HelpWidget.h"
#include"startpage.h"

HelpWidget::HelpWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HelpWidgetClass())
{
	ui->setupUi(this);
	setWindowTitle("PlantsVsZombies");
	this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // 设置窗口图标
	connect(ui->mainMenu, &QPushButton::clicked, this, &HelpWidget::goToMainMenu);
}

HelpWidget::~HelpWidget()
{
	delete ui;
}

void HelpWidget::setWidget(startpage* start)
{
	mainMenu = start;
}

void HelpWidget::goToMainMenu()
{
	this->setEnabled(false);
	this->hide();
	mainMenu->setEnabled(true);
	mainMenu->show();
}
