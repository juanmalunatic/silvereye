/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *logoImgLabel;
    QSpacerItem *verticalSpacer_3;
    QPushButton *systemStatusButton;
    QSpacerItem *verticalSpacer;
    QPushButton *sagittalAnglesButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *humanModelButton;
    QPushButton *recordRawButton;
    QPushButton *modelCalibrationButton;
    QPushButton *serialSettingsButton;
    QPushButton *recordKinematicsButton;
    QLabel *brandingLabel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(158, 471);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        logoImgLabel = new QLabel(centralWidget);
        logoImgLabel->setObjectName(QStringLiteral("logoImgLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logoImgLabel->sizePolicy().hasHeightForWidth());
        logoImgLabel->setSizePolicy(sizePolicy);
        logoImgLabel->setMinimumSize(QSize(140, 121));
        logoImgLabel->setLayoutDirection(Qt::LeftToRight);
        logoImgLabel->setPixmap(QPixmap(QString::fromUtf8(":/logo/silver_96_qt.png")));
        logoImgLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(logoImgLabel, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 3, 0, 1, 1);

        systemStatusButton = new QPushButton(centralWidget);
        systemStatusButton->setObjectName(QStringLiteral("systemStatusButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(systemStatusButton->sizePolicy().hasHeightForWidth());
        systemStatusButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(systemStatusButton, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(0, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        sagittalAnglesButton = new QPushButton(centralWidget);
        sagittalAnglesButton->setObjectName(QStringLiteral("sagittalAnglesButton"));
        sizePolicy1.setHeightForWidth(sagittalAnglesButton->sizePolicy().hasHeightForWidth());
        sagittalAnglesButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(sagittalAnglesButton, 9, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(0, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 11, 0, 1, 1);

        humanModelButton = new QPushButton(centralWidget);
        humanModelButton->setObjectName(QStringLiteral("humanModelButton"));
        sizePolicy1.setHeightForWidth(humanModelButton->sizePolicy().hasHeightForWidth());
        humanModelButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(humanModelButton, 8, 0, 1, 1);

        recordRawButton = new QPushButton(centralWidget);
        recordRawButton->setObjectName(QStringLiteral("recordRawButton"));
        sizePolicy1.setHeightForWidth(recordRawButton->sizePolicy().hasHeightForWidth());
        recordRawButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(recordRawButton, 12, 0, 1, 1);

        modelCalibrationButton = new QPushButton(centralWidget);
        modelCalibrationButton->setObjectName(QStringLiteral("modelCalibrationButton"));
        sizePolicy1.setHeightForWidth(modelCalibrationButton->sizePolicy().hasHeightForWidth());
        modelCalibrationButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(modelCalibrationButton, 7, 0, 1, 1);

        serialSettingsButton = new QPushButton(centralWidget);
        serialSettingsButton->setObjectName(QStringLiteral("serialSettingsButton"));
        sizePolicy1.setHeightForWidth(serialSettingsButton->sizePolicy().hasHeightForWidth());
        serialSettingsButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(serialSettingsButton, 4, 0, 1, 1);

        recordKinematicsButton = new QPushButton(centralWidget);
        recordKinematicsButton->setObjectName(QStringLiteral("recordKinematicsButton"));
        sizePolicy1.setHeightForWidth(recordKinematicsButton->sizePolicy().hasHeightForWidth());
        recordKinematicsButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(recordKinematicsButton, 10, 0, 1, 1);

        brandingLabel = new QLabel(centralWidget);
        brandingLabel->setObjectName(QStringLiteral("brandingLabel"));
        brandingLabel->setStyleSheet(QLatin1String("font: 11pt \"MS Shell Dlg 2\";\n"
"font-weight:bold;"));
        brandingLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(brandingLabel, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        logoImgLabel->setText(QString());
        systemStatusButton->setText(QApplication::translate("MainWindow", "System status", 0));
        sagittalAnglesButton->setText(QApplication::translate("MainWindow", "Sagittal angles", 0));
        humanModelButton->setText(QApplication::translate("MainWindow", "Human model", 0));
        recordRawButton->setText(QApplication::translate("MainWindow", "Record raw signals", 0));
        modelCalibrationButton->setText(QApplication::translate("MainWindow", "Model control", 0));
        serialSettingsButton->setText(QApplication::translate("MainWindow", "Serial settings", 0));
        recordKinematicsButton->setText(QApplication::translate("MainWindow", "Record kinematics", 0));
        brandingLabel->setText(QApplication::translate("MainWindow", "Silvereye", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
