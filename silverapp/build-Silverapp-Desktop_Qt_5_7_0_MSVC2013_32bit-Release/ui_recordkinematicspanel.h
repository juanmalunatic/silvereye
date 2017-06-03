/********************************************************************************
** Form generated from reading UI file 'recordkinematicspanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDKINEMATICSPANEL_H
#define UI_RECORDKINEMATICSPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordKinematicsPanel
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QLineEdit *FolderLineEdit;
    QLabel *FileLabel;
    QLineEdit *FileLineEdit;
    QLabel *FolderLabel;
    QPushButton *FolderButton;
    QPushButton *FileButton;
    QLabel *FileStatus;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QCheckBox *segmentCheckBox;
    QCheckBox *rawCheckBox;
    QCheckBox *jointCheckBox;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QGroupBox *ControlsBox;
    QGridLayout *gridLayout_2;
    QLabel *RecordingStatus;
    QLabel *ElapsedLabel;
    QLabel *ElapsedTimeLabel;
    QPushButton *RecordButton;

    void setupUi(QWidget *RecordKinematicsPanel)
    {
        if (RecordKinematicsPanel->objectName().isEmpty())
            RecordKinematicsPanel->setObjectName(QStringLiteral("RecordKinematicsPanel"));
        RecordKinematicsPanel->resize(367, 431);
        gridLayout = new QGridLayout(RecordKinematicsPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_2 = new QGroupBox(RecordKinematicsPanel);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        FolderLineEdit = new QLineEdit(groupBox_2);
        FolderLineEdit->setObjectName(QStringLiteral("FolderLineEdit"));

        gridLayout_4->addWidget(FolderLineEdit, 0, 1, 1, 1);

        FileLabel = new QLabel(groupBox_2);
        FileLabel->setObjectName(QStringLiteral("FileLabel"));
        FileLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(FileLabel, 1, 0, 1, 1);

        FileLineEdit = new QLineEdit(groupBox_2);
        FileLineEdit->setObjectName(QStringLiteral("FileLineEdit"));

        gridLayout_4->addWidget(FileLineEdit, 1, 1, 1, 1);

        FolderLabel = new QLabel(groupBox_2);
        FolderLabel->setObjectName(QStringLiteral("FolderLabel"));

        gridLayout_4->addWidget(FolderLabel, 0, 0, 1, 1);

        FolderButton = new QPushButton(groupBox_2);
        FolderButton->setObjectName(QStringLiteral("FolderButton"));

        gridLayout_4->addWidget(FolderButton, 0, 2, 1, 1);

        FileButton = new QPushButton(groupBox_2);
        FileButton->setObjectName(QStringLiteral("FileButton"));

        gridLayout_4->addWidget(FileButton, 1, 2, 1, 1);

        FileStatus = new QLabel(groupBox_2);
        FileStatus->setObjectName(QStringLiteral("FileStatus"));
        sizePolicy.setHeightForWidth(FileStatus->sizePolicy().hasHeightForWidth());
        FileStatus->setSizePolicy(sizePolicy);
        FileStatus->setMinimumSize(QSize(0, 11));

        gridLayout_4->addWidget(FileStatus, 2, 1, 1, 2);


        gridLayout->addWidget(groupBox_2, 7, 0, 1, 3);

        groupBox = new QGroupBox(RecordKinematicsPanel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 150));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        segmentCheckBox = new QCheckBox(groupBox);
        segmentCheckBox->setObjectName(QStringLiteral("segmentCheckBox"));

        gridLayout_3->addWidget(segmentCheckBox, 1, 1, 1, 1);

        rawCheckBox = new QCheckBox(groupBox);
        rawCheckBox->setObjectName(QStringLiteral("rawCheckBox"));

        gridLayout_3->addWidget(rawCheckBox, 0, 1, 1, 1);

        jointCheckBox = new QCheckBox(groupBox);
        jointCheckBox->setObjectName(QStringLiteral("jointCheckBox"));

        gridLayout_3->addWidget(jointCheckBox, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox, 8, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 3);

        label = new QLabel(RecordKinematicsPanel);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 66));
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label->setWordWrap(true);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        ControlsBox = new QGroupBox(RecordKinematicsPanel);
        ControlsBox->setObjectName(QStringLiteral("ControlsBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ControlsBox->sizePolicy().hasHeightForWidth());
        ControlsBox->setSizePolicy(sizePolicy1);
        ControlsBox->setMaximumSize(QSize(16777215, 150));
        gridLayout_2 = new QGridLayout(ControlsBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        RecordingStatus = new QLabel(ControlsBox);
        RecordingStatus->setObjectName(QStringLiteral("RecordingStatus"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(RecordingStatus->sizePolicy().hasHeightForWidth());
        RecordingStatus->setSizePolicy(sizePolicy2);
        RecordingStatus->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(RecordingStatus, 1, 1, 1, 2);

        ElapsedLabel = new QLabel(ControlsBox);
        ElapsedLabel->setObjectName(QStringLiteral("ElapsedLabel"));
        sizePolicy1.setHeightForWidth(ElapsedLabel->sizePolicy().hasHeightForWidth());
        ElapsedLabel->setSizePolicy(sizePolicy1);
        ElapsedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(ElapsedLabel, 2, 1, 1, 1);

        ElapsedTimeLabel = new QLabel(ControlsBox);
        ElapsedTimeLabel->setObjectName(QStringLiteral("ElapsedTimeLabel"));
        sizePolicy1.setHeightForWidth(ElapsedTimeLabel->sizePolicy().hasHeightForWidth());
        ElapsedTimeLabel->setSizePolicy(sizePolicy1);
        ElapsedTimeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(ElapsedTimeLabel, 2, 2, 1, 1);

        RecordButton = new QPushButton(ControlsBox);
        RecordButton->setObjectName(QStringLiteral("RecordButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(RecordButton->sizePolicy().hasHeightForWidth());
        RecordButton->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(RecordButton, 3, 1, 1, 2);


        gridLayout->addWidget(ControlsBox, 8, 1, 1, 2);


        retranslateUi(RecordKinematicsPanel);

        QMetaObject::connectSlotsByName(RecordKinematicsPanel);
    } // setupUi

    void retranslateUi(QWidget *RecordKinematicsPanel)
    {
        RecordKinematicsPanel->setWindowTitle(QApplication::translate("RecordKinematicsPanel", "Record kinematics", 0));
        groupBox_2->setTitle(QApplication::translate("RecordKinematicsPanel", "Settings", 0));
        FolderLineEdit->setText(QApplication::translate("RecordKinematicsPanel", "D:/", 0));
        FileLabel->setText(QApplication::translate("RecordKinematicsPanel", "Filename:", 0));
        FolderLabel->setText(QApplication::translate("RecordKinematicsPanel", "Rec folder:", 0));
        FolderButton->setText(QApplication::translate("RecordKinematicsPanel", "Choose", 0));
        FileButton->setText(QApplication::translate("RecordKinematicsPanel", "Generate new", 0));
        FileStatus->setText(QApplication::translate("RecordKinematicsPanel", "Checking filename...", 0));
        groupBox->setTitle(QApplication::translate("RecordKinematicsPanel", "Additional signals", 0));
        segmentCheckBox->setText(QApplication::translate("RecordKinematicsPanel", "Segment quats", 0));
        rawCheckBox->setText(QApplication::translate("RecordKinematicsPanel", "Raw quats", 0));
        jointCheckBox->setText(QApplication::translate("RecordKinematicsPanel", "Joint quats", 0));
        label->setText(QApplication::translate("RecordKinematicsPanel", "Record the acquired sagittal angles to disk and, optionally, the quaternions used to calculate them. The .cimu file contains the compensation references and the .kimu contains the kinematic data.", 0));
        ControlsBox->setTitle(QApplication::translate("RecordKinematicsPanel", "Controls", 0));
        RecordingStatus->setText(QApplication::translate("RecordKinematicsPanel", "Idle", 0));
        ElapsedLabel->setText(QApplication::translate("RecordKinematicsPanel", "Elapsed secs:", 0));
        ElapsedTimeLabel->setText(QApplication::translate("RecordKinematicsPanel", "0", 0));
        RecordButton->setText(QApplication::translate("RecordKinematicsPanel", "Record", 0));
    } // retranslateUi

};

namespace Ui {
    class RecordKinematicsPanel: public Ui_RecordKinematicsPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDKINEMATICSPANEL_H
