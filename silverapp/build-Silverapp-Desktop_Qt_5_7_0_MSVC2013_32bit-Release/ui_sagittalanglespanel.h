/********************************************************************************
** Form generated from reading UI file 'sagittalanglespanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAGITTALANGLESPANEL_H
#define UI_SAGITTALANGLESPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_SagittalAnglesPanel
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *rightAnklePlot;
    QCustomPlot *leftHipPlot;
    QCustomPlot *rightHipPlot;
    QCustomPlot *leftAnklePlot;
    QCustomPlot *rightKneePlot;
    QCustomPlot *leftKneePlot;

    void setupUi(QWidget *SagittalAnglesPanel)
    {
        if (SagittalAnglesPanel->objectName().isEmpty())
            SagittalAnglesPanel->setObjectName(QStringLiteral("SagittalAnglesPanel"));
        SagittalAnglesPanel->resize(599, 666);
        SagittalAnglesPanel->setAutoFillBackground(false);
        SagittalAnglesPanel->setStyleSheet(QLatin1String("QWidget#SagittalAnglesPanel{\n"
"	background-color:rgb(255,255,255);\n"
"}"));
        gridLayout = new QGridLayout(SagittalAnglesPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        rightAnklePlot = new QCustomPlot(SagittalAnglesPanel);
        rightAnklePlot->setObjectName(QStringLiteral("rightAnklePlot"));

        gridLayout->addWidget(rightAnklePlot, 2, 1, 1, 1);

        leftHipPlot = new QCustomPlot(SagittalAnglesPanel);
        leftHipPlot->setObjectName(QStringLiteral("leftHipPlot"));

        gridLayout->addWidget(leftHipPlot, 0, 0, 1, 1);

        rightHipPlot = new QCustomPlot(SagittalAnglesPanel);
        rightHipPlot->setObjectName(QStringLiteral("rightHipPlot"));

        gridLayout->addWidget(rightHipPlot, 0, 1, 1, 1);

        leftAnklePlot = new QCustomPlot(SagittalAnglesPanel);
        leftAnklePlot->setObjectName(QStringLiteral("leftAnklePlot"));

        gridLayout->addWidget(leftAnklePlot, 2, 0, 1, 1);

        rightKneePlot = new QCustomPlot(SagittalAnglesPanel);
        rightKneePlot->setObjectName(QStringLiteral("rightKneePlot"));

        gridLayout->addWidget(rightKneePlot, 1, 1, 1, 1);

        leftKneePlot = new QCustomPlot(SagittalAnglesPanel);
        leftKneePlot->setObjectName(QStringLiteral("leftKneePlot"));

        gridLayout->addWidget(leftKneePlot, 1, 0, 1, 1);


        retranslateUi(SagittalAnglesPanel);

        QMetaObject::connectSlotsByName(SagittalAnglesPanel);
    } // setupUi

    void retranslateUi(QWidget *SagittalAnglesPanel)
    {
        SagittalAnglesPanel->setWindowTitle(QApplication::translate("SagittalAnglesPanel", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SagittalAnglesPanel: public Ui_SagittalAnglesPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAGITTALANGLESPANEL_H
