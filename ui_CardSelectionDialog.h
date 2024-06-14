/********************************************************************************
** Form generated from reading UI file 'CardSelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDSELECTIONDIALOG_H
#define UI_CARDSELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CardSelectionDialogClass
{
public:
    QWidget *cardTab;
    QPushButton *cancel;
    QPushButton *apply;
    QWidget *widget;

    void setupUi(QWidget *CardSelectionDialogClass)
    {
        if (CardSelectionDialogClass->objectName().isEmpty())
            CardSelectionDialogClass->setObjectName(QString::fromUtf8("CardSelectionDialogClass"));
        CardSelectionDialogClass->resize(517, 511);
        CardSelectionDialogClass->setMinimumSize(QSize(517, 511));
        CardSelectionDialogClass->setMaximumSize(QSize(517, 511));
        CardSelectionDialogClass->setStyleSheet(QString::fromUtf8(""));
        cardTab = new QWidget(CardSelectionDialogClass);
        cardTab->setObjectName(QString::fromUtf8("cardTab"));
        cardTab->setGeometry(QRect(0, 0, 491, 110));
        cardTab->setMinimumSize(QSize(0, 110));
        cardTab->setMaximumSize(QSize(16777215, 110));
        cardTab->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border-image:url(:/new/prefix1/SeedChooser_Background.png);\n"
"}"));
        cancel = new QPushButton(cardTab);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(12, 5, 75, 23));
        cancel->setMinimumSize(QSize(75, 23));
        cancel->setMaximumSize(QSize(75, 23));
        cancel->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image:url(:/new/prefix1/levelbutton.png);\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"border-image:url(:/new/prefix1/levelbutton1.png);\n"
"}"));
        apply = new QPushButton(cardTab);
        apply->setObjectName(QString::fromUtf8("apply"));
        apply->setGeometry(QRect(404, 5, 75, 23));
        apply->setMinimumSize(QSize(75, 23));
        apply->setMaximumSize(QSize(75, 23));
        apply->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image:url(:/new/prefix1/levelbutton.png);\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"border-image:url(:/new/prefix1/levelbutton1.png);\n"
"}"));
        widget = new QWidget(CardSelectionDialogClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(200, 210, 120, 80));
        widget->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border-image:url(:/new/prefix1/SeedChooser_BackgroundStack.png) center no-repeat;\n"
"	\n"
"}\n"
""));

        retranslateUi(CardSelectionDialogClass);

        QMetaObject::connectSlotsByName(CardSelectionDialogClass);
    } // setupUi

    void retranslateUi(QWidget *CardSelectionDialogClass)
    {
        CardSelectionDialogClass->setWindowTitle(QCoreApplication::translate("CardSelectionDialogClass", "CardSelectionDialog", nullptr));
        cancel->setText(QCoreApplication::translate("CardSelectionDialogClass", "\345\217\226\346\266\210", nullptr));
        apply->setText(QCoreApplication::translate("CardSelectionDialogClass", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CardSelectionDialogClass: public Ui_CardSelectionDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDSELECTIONDIALOG_H
