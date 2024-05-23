/********************************************************************************
** Form generated from reading UI file 'HelpWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWIDGET_H
#define UI_HELPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpWidgetClass
{
public:
    QLabel *label;
    QPushButton *mainMenu;

    void setupUi(QWidget *HelpWidgetClass)
    {
        if (HelpWidgetClass->objectName().isEmpty())
            HelpWidgetClass->setObjectName("HelpWidgetClass");
        HelpWidgetClass->resize(900, 600);
        HelpWidgetClass->setMinimumSize(QSize(900, 600));
        HelpWidgetClass->setMaximumSize(QSize(900, 600));
        label = new QLabel(HelpWidgetClass);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 900, 600));
        label->setMinimumSize(QSize(900, 600));
        label->setMaximumSize(QSize(900, 600));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/help.png")));
        label->setScaledContents(true);
        mainMenu = new QPushButton(HelpWidgetClass);
        mainMenu->setObjectName("mainMenu");
        mainMenu->setGeometry(QRect(368, 520, 170, 37));
        mainMenu->setMinimumSize(QSize(170, 37));
        mainMenu->setMaximumSize(QSize(170, 37));
        mainMenu->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"	border:none;\n"
"    padding:0px;\n"
"    background:transparent;   \n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border-image:url(:/new/prefix1/help-hover.png);\n"
"}"));

        retranslateUi(HelpWidgetClass);

        QMetaObject::connectSlotsByName(HelpWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *HelpWidgetClass)
    {
        HelpWidgetClass->setWindowTitle(QCoreApplication::translate("HelpWidgetClass", "HelpWidget", nullptr));
        label->setText(QString());
        mainMenu->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HelpWidgetClass: public Ui_HelpWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWIDGET_H
