/********************************************************************************
** Form generated from reading UI file 'serialsettingspanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALSETTINGSPANEL_H
#define UI_SERIALSETTINGSPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialSettingsPanel
{
public:
    QGridLayout *gridLayout;
    QLabel *portStatusLabel;
    QLabel *label;
    QComboBox *portSelectComboBox;
    QPushButton *portReloadPushButton;
    QTextEdit *portStatusTextEdit;

    void setupUi(QWidget *SerialSettingsPanel)
    {
        if (SerialSettingsPanel->objectName().isEmpty())
            SerialSettingsPanel->setObjectName(QStringLiteral("SerialSettingsPanel"));
        SerialSettingsPanel->resize(498, 107);
        gridLayout = new QGridLayout(SerialSettingsPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        portStatusLabel = new QLabel(SerialSettingsPanel);
        portStatusLabel->setObjectName(QStringLiteral("portStatusLabel"));
        portStatusLabel->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        portStatusLabel->setMargin(5);

        gridLayout->addWidget(portStatusLabel, 0, 1, 1, 1);

        label = new QLabel(SerialSettingsPanel);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        portSelectComboBox = new QComboBox(SerialSettingsPanel);
        portSelectComboBox->setObjectName(QStringLiteral("portSelectComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(portSelectComboBox->sizePolicy().hasHeightForWidth());
        portSelectComboBox->setSizePolicy(sizePolicy);

        gridLayout->addWidget(portSelectComboBox, 1, 2, 1, 1);

        portReloadPushButton = new QPushButton(SerialSettingsPanel);
        portReloadPushButton->setObjectName(QStringLiteral("portReloadPushButton"));

        gridLayout->addWidget(portReloadPushButton, 1, 3, 1, 1);

        portStatusTextEdit = new QTextEdit(SerialSettingsPanel);
        portStatusTextEdit->setObjectName(QStringLiteral("portStatusTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(portStatusTextEdit->sizePolicy().hasHeightForWidth());
        portStatusTextEdit->setSizePolicy(sizePolicy1);
        portStatusTextEdit->setMinimumSize(QSize(0, 60));
        portStatusTextEdit->setMaximumSize(QSize(16777215, 60));
        portStatusTextEdit->setReadOnly(true);

        gridLayout->addWidget(portStatusTextEdit, 0, 2, 1, 2);


        retranslateUi(SerialSettingsPanel);

        QMetaObject::connectSlotsByName(SerialSettingsPanel);
    } // setupUi

    void retranslateUi(QWidget *SerialSettingsPanel)
    {
        SerialSettingsPanel->setWindowTitle(QApplication::translate("SerialSettingsPanel", "Serial settings", 0));
        portStatusLabel->setText(QApplication::translate("SerialSettingsPanel", "Serial port status:", 0));
        label->setText(QApplication::translate("SerialSettingsPanel", "Choose a serial port:", 0));
        portReloadPushButton->setText(QApplication::translate("SerialSettingsPanel", "Update list", 0));
        portStatusTextEdit->setHtml(QApplication::translate("SerialSettingsPanel", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class SerialSettingsPanel: public Ui_SerialSettingsPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALSETTINGSPANEL_H
