/********************************************************************************
** Form generated from reading UI file 'modelcalibrationpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELCALIBRATIONPANEL_H
#define UI_MODELCALIBRATIONPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelCalibrationPanel
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *saveFrontalButton;
    QPushButton *saveMountingButton;
    QPushButton *saveAllButton;
    QPushButton *saveCompensationButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *resetViewportButton;
    QPushButton *sagittalViewportButton;

    void setupUi(QWidget *ModelCalibrationPanel)
    {
        if (ModelCalibrationPanel->objectName().isEmpty())
            ModelCalibrationPanel->setObjectName(QStringLiteral("ModelCalibrationPanel"));
        ModelCalibrationPanel->resize(252, 256);
        gridLayout = new QGridLayout(ModelCalibrationPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(ModelCalibrationPanel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        saveFrontalButton = new QPushButton(groupBox);
        saveFrontalButton->setObjectName(QStringLiteral("saveFrontalButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(saveFrontalButton->sizePolicy().hasHeightForWidth());
        saveFrontalButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(saveFrontalButton, 1, 0, 1, 1);

        saveMountingButton = new QPushButton(groupBox);
        saveMountingButton->setObjectName(QStringLiteral("saveMountingButton"));
        sizePolicy.setHeightForWidth(saveMountingButton->sizePolicy().hasHeightForWidth());
        saveMountingButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(saveMountingButton, 2, 0, 1, 1);

        saveAllButton = new QPushButton(groupBox);
        saveAllButton->setObjectName(QStringLiteral("saveAllButton"));
        sizePolicy.setHeightForWidth(saveAllButton->sizePolicy().hasHeightForWidth());
        saveAllButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        saveAllButton->setFont(font);

        gridLayout_2->addWidget(saveAllButton, 0, 0, 1, 1);

        saveCompensationButton = new QPushButton(groupBox);
        saveCompensationButton->setObjectName(QStringLiteral("saveCompensationButton"));
        sizePolicy.setHeightForWidth(saveCompensationButton->sizePolicy().hasHeightForWidth());
        saveCompensationButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(saveCompensationButton, 3, 0, 1, 1);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(ModelCalibrationPanel);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        resetViewportButton = new QPushButton(groupBox_2);
        resetViewportButton->setObjectName(QStringLiteral("resetViewportButton"));
        sizePolicy.setHeightForWidth(resetViewportButton->sizePolicy().hasHeightForWidth());
        resetViewportButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(resetViewportButton, 0, 0, 1, 1);

        sagittalViewportButton = new QPushButton(groupBox_2);
        sagittalViewportButton->setObjectName(QStringLiteral("sagittalViewportButton"));

        gridLayout_3->addWidget(sagittalViewportButton, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 3, 0, 1, 1);


        retranslateUi(ModelCalibrationPanel);

        QMetaObject::connectSlotsByName(ModelCalibrationPanel);
    } // setupUi

    void retranslateUi(QWidget *ModelCalibrationPanel)
    {
        ModelCalibrationPanel->setWindowTitle(QApplication::translate("ModelCalibrationPanel", "Form", 0));
        groupBox->setTitle(QApplication::translate("ModelCalibrationPanel", "Calibration", 0));
        saveFrontalButton->setText(QApplication::translate("ModelCalibrationPanel", "Save frontal reference", 0));
        saveMountingButton->setText(QApplication::translate("ModelCalibrationPanel", "Save sensor mounting", 0));
        saveAllButton->setText(QApplication::translate("ModelCalibrationPanel", "Save all mounting references", 0));
        saveCompensationButton->setText(QApplication::translate("ModelCalibrationPanel", "Save compensation", 0));
        groupBox_2->setTitle(QApplication::translate("ModelCalibrationPanel", "Camera control", 0));
        resetViewportButton->setText(QApplication::translate("ModelCalibrationPanel", "Reset viewport", 0));
        sagittalViewportButton->setText(QApplication::translate("ModelCalibrationPanel", "Sagittal view", 0));
    } // retranslateUi

};

namespace Ui {
    class ModelCalibrationPanel: public Ui_ModelCalibrationPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELCALIBRATIONPANEL_H
