/********************************************************************************
** Form generated from reading UI file 'systemstatuspanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSTATUSPANEL_H
#define UI_SYSTEMSTATUSPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemStatusPanel
{
public:
    QGridLayout *gridLayout;
    QLabel *FrameRateValue;
    QFrame *line;
    QLabel *FrameRateLabel;
    QLabel *TitleLabelID;
    QLabel *CalibLabelG;
    QLabel *S3calibG;
    QLabel *S4calibM;
    QLabel *S5calibM;
    QLabel *S4calibA;
    QLabel *S7id;
    QLabel *S5status;
    QLabel *S5calibA;
    QLabel *S4status;
    QLabel *S4bat;
    QLabel *S5id;
    QLabel *S6calibG;
    QLabel *S5calibS;
    QLabel *S6calibS;
    QLabel *S6bat;
    QLabel *S4id;
    QLabel *S3bat;
    QLabel *S4calibS;
    QLabel *S2calibA;
    QLabel *S3id;
    QLabel *S6calibA;
    QLabel *S6calibM;
    QLabel *S2calibS;
    QLabel *S2calibM;
    QLabel *S6id;
    QLabel *S2calibG;
    QLabel *S7calibS;
    QLabel *S7bat;
    QLabel *S3calibM;
    QLabel *TitleLabelCalibration;
    QLabel *S2status;
    QLabel *TitleLabelBattery;
    QLabel *S5bat;
    QLabel *CalibLabelS;
    QLabel *S1calibA;
    QLabel *S5calibG;
    QLabel *S3calibS;
    QLabel *S1calibM;
    QLabel *TitleLabelStatus;
    QLabel *S6status;
    QLabel *S7calibA;
    QLabel *S2bat;
    QLabel *S1id;
    QLabel *S1calibS;
    QLabel *S1calibG;
    QLabel *S3status;
    QLabel *S2id;
    QLabel *S4calibG;
    QLabel *CalibLabelA;
    QLabel *S1status;
    QLabel *S1bat;
    QLabel *S7calibM;
    QLabel *S7calibG;
    QLabel *S3calibA;
    QLabel *CalibLabelM;
    QLabel *S7status;

    void setupUi(QWidget *SystemStatusPanel)
    {
        if (SystemStatusPanel->objectName().isEmpty())
            SystemStatusPanel->setObjectName(QStringLiteral("SystemStatusPanel"));
        SystemStatusPanel->resize(250, 260);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SystemStatusPanel->sizePolicy().hasHeightForWidth());
        SystemStatusPanel->setSizePolicy(sizePolicy);
        SystemStatusPanel->setMinimumSize(QSize(250, 260));
        SystemStatusPanel->setMaximumSize(QSize(500, 500));
        SystemStatusPanel->setStyleSheet(QLatin1String("QLabel[margin=\"1\"]{\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"/*QLabel[margin=\"2\"]{\n"
"	color:#096;\n"
"}*/"));
        gridLayout = new QGridLayout(SystemStatusPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        FrameRateValue = new QLabel(SystemStatusPanel);
        FrameRateValue->setObjectName(QStringLiteral("FrameRateValue"));
        FrameRateValue->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(FrameRateValue, 13, 3, 1, 4);

        line = new QFrame(SystemStatusPanel);
        line->setObjectName(QStringLiteral("line"));
        line->setMinimumSize(QSize(0, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 12, 0, 1, 7);

        FrameRateLabel = new QLabel(SystemStatusPanel);
        FrameRateLabel->setObjectName(QStringLiteral("FrameRateLabel"));
        FrameRateLabel->setMargin(1);

        gridLayout->addWidget(FrameRateLabel, 13, 0, 1, 2);

        TitleLabelID = new QLabel(SystemStatusPanel);
        TitleLabelID->setObjectName(QStringLiteral("TitleLabelID"));
        TitleLabelID->setMinimumSize(QSize(0, 20));
        TitleLabelID->setAlignment(Qt::AlignCenter);
        TitleLabelID->setMargin(1);

        gridLayout->addWidget(TitleLabelID, 3, 0, 1, 1);

        CalibLabelG = new QLabel(SystemStatusPanel);
        CalibLabelG->setObjectName(QStringLiteral("CalibLabelG"));
        CalibLabelG->setAlignment(Qt::AlignCenter);
        CalibLabelG->setMargin(1);

        gridLayout->addWidget(CalibLabelG, 4, 6, 1, 1);

        S3calibG = new QLabel(SystemStatusPanel);
        S3calibG->setObjectName(QStringLiteral("S3calibG"));
        S3calibG->setMaximumSize(QSize(30, 16777215));
        S3calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S3calibG, 7, 6, 1, 1);

        S4calibM = new QLabel(SystemStatusPanel);
        S4calibM->setObjectName(QStringLiteral("S4calibM"));
        S4calibM->setMaximumSize(QSize(30, 16777215));
        S4calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S4calibM, 8, 5, 1, 1);

        S5calibM = new QLabel(SystemStatusPanel);
        S5calibM->setObjectName(QStringLiteral("S5calibM"));
        S5calibM->setMaximumSize(QSize(30, 16777215));
        S5calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S5calibM, 9, 5, 1, 1);

        S4calibA = new QLabel(SystemStatusPanel);
        S4calibA->setObjectName(QStringLiteral("S4calibA"));
        S4calibA->setMaximumSize(QSize(30, 16777215));
        S4calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S4calibA, 8, 4, 1, 1);

        S7id = new QLabel(SystemStatusPanel);
        S7id->setObjectName(QStringLiteral("S7id"));
        S7id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S7id, 11, 0, 1, 1);

        S5status = new QLabel(SystemStatusPanel);
        S5status->setObjectName(QStringLiteral("S5status"));
        S5status->setAlignment(Qt::AlignCenter);
        S5status->setMargin(2);

        gridLayout->addWidget(S5status, 9, 1, 1, 1);

        S5calibA = new QLabel(SystemStatusPanel);
        S5calibA->setObjectName(QStringLiteral("S5calibA"));
        S5calibA->setMaximumSize(QSize(30, 16777215));
        S5calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S5calibA, 9, 4, 1, 1);

        S4status = new QLabel(SystemStatusPanel);
        S4status->setObjectName(QStringLiteral("S4status"));
        S4status->setAlignment(Qt::AlignCenter);
        S4status->setMargin(2);

        gridLayout->addWidget(S4status, 8, 1, 1, 1);

        S4bat = new QLabel(SystemStatusPanel);
        S4bat->setObjectName(QStringLiteral("S4bat"));
        S4bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S4bat, 8, 2, 1, 1);

        S5id = new QLabel(SystemStatusPanel);
        S5id->setObjectName(QStringLiteral("S5id"));
        S5id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S5id, 9, 0, 1, 1);

        S6calibG = new QLabel(SystemStatusPanel);
        S6calibG->setObjectName(QStringLiteral("S6calibG"));
        S6calibG->setMaximumSize(QSize(30, 16777215));
        S6calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S6calibG, 10, 6, 1, 1);

        S5calibS = new QLabel(SystemStatusPanel);
        S5calibS->setObjectName(QStringLiteral("S5calibS"));
        S5calibS->setMaximumSize(QSize(30, 16777215));
        S5calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S5calibS, 9, 3, 1, 1);

        S6calibS = new QLabel(SystemStatusPanel);
        S6calibS->setObjectName(QStringLiteral("S6calibS"));
        S6calibS->setMaximumSize(QSize(30, 16777215));
        S6calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S6calibS, 10, 3, 1, 1);

        S6bat = new QLabel(SystemStatusPanel);
        S6bat->setObjectName(QStringLiteral("S6bat"));
        S6bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S6bat, 10, 2, 1, 1);

        S4id = new QLabel(SystemStatusPanel);
        S4id->setObjectName(QStringLiteral("S4id"));
        S4id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S4id, 8, 0, 1, 1);

        S3bat = new QLabel(SystemStatusPanel);
        S3bat->setObjectName(QStringLiteral("S3bat"));
        S3bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S3bat, 7, 2, 1, 1);

        S4calibS = new QLabel(SystemStatusPanel);
        S4calibS->setObjectName(QStringLiteral("S4calibS"));
        S4calibS->setMaximumSize(QSize(30, 16777215));
        S4calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S4calibS, 8, 3, 1, 1);

        S2calibA = new QLabel(SystemStatusPanel);
        S2calibA->setObjectName(QStringLiteral("S2calibA"));
        S2calibA->setMaximumSize(QSize(30, 16777215));
        S2calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S2calibA, 6, 4, 1, 1);

        S3id = new QLabel(SystemStatusPanel);
        S3id->setObjectName(QStringLiteral("S3id"));
        S3id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S3id, 7, 0, 1, 1);

        S6calibA = new QLabel(SystemStatusPanel);
        S6calibA->setObjectName(QStringLiteral("S6calibA"));
        S6calibA->setMaximumSize(QSize(30, 16777215));
        S6calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S6calibA, 10, 4, 1, 1);

        S6calibM = new QLabel(SystemStatusPanel);
        S6calibM->setObjectName(QStringLiteral("S6calibM"));
        S6calibM->setMaximumSize(QSize(30, 16777215));
        S6calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S6calibM, 10, 5, 1, 1);

        S2calibS = new QLabel(SystemStatusPanel);
        S2calibS->setObjectName(QStringLiteral("S2calibS"));
        S2calibS->setMaximumSize(QSize(30, 16777215));
        S2calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S2calibS, 6, 3, 1, 1);

        S2calibM = new QLabel(SystemStatusPanel);
        S2calibM->setObjectName(QStringLiteral("S2calibM"));
        S2calibM->setMaximumSize(QSize(30, 16777215));
        S2calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S2calibM, 6, 5, 1, 1);

        S6id = new QLabel(SystemStatusPanel);
        S6id->setObjectName(QStringLiteral("S6id"));
        S6id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S6id, 10, 0, 1, 1);

        S2calibG = new QLabel(SystemStatusPanel);
        S2calibG->setObjectName(QStringLiteral("S2calibG"));
        S2calibG->setMaximumSize(QSize(30, 16777215));
        S2calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S2calibG, 6, 6, 1, 1);

        S7calibS = new QLabel(SystemStatusPanel);
        S7calibS->setObjectName(QStringLiteral("S7calibS"));
        S7calibS->setMaximumSize(QSize(30, 16777215));
        S7calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S7calibS, 11, 3, 1, 1);

        S7bat = new QLabel(SystemStatusPanel);
        S7bat->setObjectName(QStringLiteral("S7bat"));
        S7bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S7bat, 11, 2, 1, 1);

        S3calibM = new QLabel(SystemStatusPanel);
        S3calibM->setObjectName(QStringLiteral("S3calibM"));
        S3calibM->setMaximumSize(QSize(30, 16777215));
        S3calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S3calibM, 7, 5, 1, 1);

        TitleLabelCalibration = new QLabel(SystemStatusPanel);
        TitleLabelCalibration->setObjectName(QStringLiteral("TitleLabelCalibration"));
        TitleLabelCalibration->setMinimumSize(QSize(0, 20));
        TitleLabelCalibration->setAlignment(Qt::AlignCenter);
        TitleLabelCalibration->setMargin(1);

        gridLayout->addWidget(TitleLabelCalibration, 3, 3, 1, 4);

        S2status = new QLabel(SystemStatusPanel);
        S2status->setObjectName(QStringLiteral("S2status"));
        S2status->setAlignment(Qt::AlignCenter);
        S2status->setMargin(2);

        gridLayout->addWidget(S2status, 6, 1, 1, 1);

        TitleLabelBattery = new QLabel(SystemStatusPanel);
        TitleLabelBattery->setObjectName(QStringLiteral("TitleLabelBattery"));
        TitleLabelBattery->setMinimumSize(QSize(56, 20));
        TitleLabelBattery->setAlignment(Qt::AlignCenter);
        TitleLabelBattery->setMargin(1);

        gridLayout->addWidget(TitleLabelBattery, 3, 2, 1, 1);

        S5bat = new QLabel(SystemStatusPanel);
        S5bat->setObjectName(QStringLiteral("S5bat"));
        S5bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S5bat, 9, 2, 1, 1);

        CalibLabelS = new QLabel(SystemStatusPanel);
        CalibLabelS->setObjectName(QStringLiteral("CalibLabelS"));
        CalibLabelS->setAlignment(Qt::AlignCenter);
        CalibLabelS->setMargin(1);

        gridLayout->addWidget(CalibLabelS, 4, 3, 1, 1);

        S1calibA = new QLabel(SystemStatusPanel);
        S1calibA->setObjectName(QStringLiteral("S1calibA"));
        S1calibA->setMaximumSize(QSize(30, 16777215));
        S1calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S1calibA, 5, 4, 1, 1);

        S5calibG = new QLabel(SystemStatusPanel);
        S5calibG->setObjectName(QStringLiteral("S5calibG"));
        S5calibG->setMaximumSize(QSize(30, 16777215));
        S5calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S5calibG, 9, 6, 1, 1);

        S3calibS = new QLabel(SystemStatusPanel);
        S3calibS->setObjectName(QStringLiteral("S3calibS"));
        S3calibS->setMaximumSize(QSize(30, 16777215));
        S3calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S3calibS, 7, 3, 1, 1);

        S1calibM = new QLabel(SystemStatusPanel);
        S1calibM->setObjectName(QStringLiteral("S1calibM"));
        S1calibM->setMaximumSize(QSize(30, 16777215));
        S1calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S1calibM, 5, 5, 1, 1);

        TitleLabelStatus = new QLabel(SystemStatusPanel);
        TitleLabelStatus->setObjectName(QStringLiteral("TitleLabelStatus"));
        TitleLabelStatus->setMinimumSize(QSize(50, 20));
        TitleLabelStatus->setAlignment(Qt::AlignCenter);
        TitleLabelStatus->setMargin(1);

        gridLayout->addWidget(TitleLabelStatus, 3, 1, 1, 1);

        S6status = new QLabel(SystemStatusPanel);
        S6status->setObjectName(QStringLiteral("S6status"));
        S6status->setAlignment(Qt::AlignCenter);
        S6status->setMargin(2);

        gridLayout->addWidget(S6status, 10, 1, 1, 1);

        S7calibA = new QLabel(SystemStatusPanel);
        S7calibA->setObjectName(QStringLiteral("S7calibA"));
        S7calibA->setMaximumSize(QSize(30, 16777215));
        S7calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S7calibA, 11, 4, 1, 1);

        S2bat = new QLabel(SystemStatusPanel);
        S2bat->setObjectName(QStringLiteral("S2bat"));
        S2bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S2bat, 6, 2, 1, 1);

        S1id = new QLabel(SystemStatusPanel);
        S1id->setObjectName(QStringLiteral("S1id"));
        S1id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S1id, 5, 0, 1, 1);

        S1calibS = new QLabel(SystemStatusPanel);
        S1calibS->setObjectName(QStringLiteral("S1calibS"));
        S1calibS->setMaximumSize(QSize(30, 16777215));
        S1calibS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S1calibS, 5, 3, 1, 1);

        S1calibG = new QLabel(SystemStatusPanel);
        S1calibG->setObjectName(QStringLiteral("S1calibG"));
        S1calibG->setMaximumSize(QSize(30, 16777215));
        S1calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S1calibG, 5, 6, 1, 1);

        S3status = new QLabel(SystemStatusPanel);
        S3status->setObjectName(QStringLiteral("S3status"));
        S3status->setAlignment(Qt::AlignCenter);
        S3status->setMargin(2);

        gridLayout->addWidget(S3status, 7, 1, 1, 1);

        S2id = new QLabel(SystemStatusPanel);
        S2id->setObjectName(QStringLiteral("S2id"));
        S2id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S2id, 6, 0, 1, 1);

        S4calibG = new QLabel(SystemStatusPanel);
        S4calibG->setObjectName(QStringLiteral("S4calibG"));
        S4calibG->setMaximumSize(QSize(30, 16777215));
        S4calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S4calibG, 8, 6, 1, 1);

        CalibLabelA = new QLabel(SystemStatusPanel);
        CalibLabelA->setObjectName(QStringLiteral("CalibLabelA"));
        CalibLabelA->setAlignment(Qt::AlignCenter);
        CalibLabelA->setMargin(1);

        gridLayout->addWidget(CalibLabelA, 4, 4, 1, 1);

        S1status = new QLabel(SystemStatusPanel);
        S1status->setObjectName(QStringLiteral("S1status"));
        S1status->setAlignment(Qt::AlignCenter);
        S1status->setMargin(2);

        gridLayout->addWidget(S1status, 5, 1, 1, 1);

        S1bat = new QLabel(SystemStatusPanel);
        S1bat->setObjectName(QStringLiteral("S1bat"));
        S1bat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S1bat, 5, 2, 1, 1);

        S7calibM = new QLabel(SystemStatusPanel);
        S7calibM->setObjectName(QStringLiteral("S7calibM"));
        S7calibM->setMaximumSize(QSize(30, 16777215));
        S7calibM->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S7calibM, 11, 5, 1, 1);

        S7calibG = new QLabel(SystemStatusPanel);
        S7calibG->setObjectName(QStringLiteral("S7calibG"));
        S7calibG->setMaximumSize(QSize(30, 16777215));
        S7calibG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S7calibG, 11, 6, 1, 1);

        S3calibA = new QLabel(SystemStatusPanel);
        S3calibA->setObjectName(QStringLiteral("S3calibA"));
        S3calibA->setMaximumSize(QSize(30, 16777215));
        S3calibA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(S3calibA, 7, 4, 1, 1);

        CalibLabelM = new QLabel(SystemStatusPanel);
        CalibLabelM->setObjectName(QStringLiteral("CalibLabelM"));
        CalibLabelM->setAlignment(Qt::AlignCenter);
        CalibLabelM->setMargin(1);

        gridLayout->addWidget(CalibLabelM, 4, 5, 1, 1);

        S7status = new QLabel(SystemStatusPanel);
        S7status->setObjectName(QStringLiteral("S7status"));
        S7status->setAlignment(Qt::AlignCenter);
        S7status->setMargin(2);

        gridLayout->addWidget(S7status, 11, 1, 1, 1);


        retranslateUi(SystemStatusPanel);

        QMetaObject::connectSlotsByName(SystemStatusPanel);
    } // setupUi

    void retranslateUi(QWidget *SystemStatusPanel)
    {
        SystemStatusPanel->setWindowTitle(QApplication::translate("SystemStatusPanel", "System status", 0));
        FrameRateValue->setText(QApplication::translate("SystemStatusPanel", "- Hz", 0));
        FrameRateLabel->setText(QApplication::translate("SystemStatusPanel", "Frame rate:", 0));
        TitleLabelID->setText(QApplication::translate("SystemStatusPanel", "ID", 0));
#ifndef QT_NO_TOOLTIP
        CalibLabelG->setToolTip(QApplication::translate("SystemStatusPanel", "Gyroscope", 0));
#endif // QT_NO_TOOLTIP
        CalibLabelG->setText(QApplication::translate("SystemStatusPanel", "G", 0));
        S3calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S4calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S5calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S4calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S7id->setText(QApplication::translate("SystemStatusPanel", "7", 0));
        S5status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
        S5calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S4status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
        S4bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S5id->setText(QApplication::translate("SystemStatusPanel", "5", 0));
        S6calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S5calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S6calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S6bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S4id->setText(QApplication::translate("SystemStatusPanel", "4", 0));
        S3bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S4calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S2calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S3id->setText(QApplication::translate("SystemStatusPanel", "3", 0));
        S6calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S6calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S2calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S2calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S6id->setText(QApplication::translate("SystemStatusPanel", "6", 0));
        S2calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S7calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S7bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S3calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        TitleLabelCalibration->setText(QApplication::translate("SystemStatusPanel", "Calibration", 0));
        S2status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
        TitleLabelBattery->setText(QApplication::translate("SystemStatusPanel", "Battery", 0));
        S5bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
#ifndef QT_NO_TOOLTIP
        CalibLabelS->setToolTip(QApplication::translate("SystemStatusPanel", "System", 0));
#endif // QT_NO_TOOLTIP
        CalibLabelS->setText(QApplication::translate("SystemStatusPanel", "S", 0));
        S1calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S5calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S3calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S1calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        TitleLabelStatus->setText(QApplication::translate("SystemStatusPanel", "Status", 0));
        S6status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
        S7calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S2bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S1id->setText(QApplication::translate("SystemStatusPanel", "1", 0));
        S1calibS->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S1calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S3status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
        S2id->setText(QApplication::translate("SystemStatusPanel", "2", 0));
        S4calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
#ifndef QT_NO_TOOLTIP
        CalibLabelA->setToolTip(QApplication::translate("SystemStatusPanel", "Accelerometer", 0));
#endif // QT_NO_TOOLTIP
        CalibLabelA->setText(QApplication::translate("SystemStatusPanel", "A", 0));
        S1status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
        S1bat->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S7calibM->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S7calibG->setText(QApplication::translate("SystemStatusPanel", "-", 0));
        S3calibA->setText(QApplication::translate("SystemStatusPanel", "-", 0));
#ifndef QT_NO_TOOLTIP
        CalibLabelM->setToolTip(QApplication::translate("SystemStatusPanel", "Magnetometer", 0));
#endif // QT_NO_TOOLTIP
        CalibLabelM->setText(QApplication::translate("SystemStatusPanel", "M", 0));
        S7status->setText(QApplication::translate("SystemStatusPanel", "Off", 0));
    } // retranslateUi

};

namespace Ui {
    class SystemStatusPanel: public Ui_SystemStatusPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSTATUSPANEL_H
