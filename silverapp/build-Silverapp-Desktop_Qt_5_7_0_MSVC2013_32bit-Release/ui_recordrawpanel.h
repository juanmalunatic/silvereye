/********************************************************************************
** Form generated from reading UI file 'recordrawpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDRAWPANEL_H
#define UI_RECORDRAWPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordRawPanel
{
public:
    QGridLayout *gridLayout;
    QGroupBox *ControlsBox;
    QGridLayout *gridLayout_2;
    QLabel *ElapsedLabel;
    QLabel *ElapsedTimeLabel;
    QLabel *RecordingStatus;
    QPushButton *RecordButton;
    QLabel *FileStatus;
    QLabel *FolderLabel;
    QLineEdit *FolderLineEdit;
    QPushButton *FolderButton;
    QLabel *FileLabel;
    QLineEdit *FileLineEdit;
    QPushButton *FileButton;

    void setupUi(QWidget *RecordRawPanel)
    {
        if (RecordRawPanel->objectName().isEmpty())
            RecordRawPanel->setObjectName(QStringLiteral("RecordRawPanel"));
        RecordRawPanel->resize(406, 196);
        gridLayout = new QGridLayout(RecordRawPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ControlsBox = new QGroupBox(RecordRawPanel);
        ControlsBox->setObjectName(QStringLiteral("ControlsBox"));
        gridLayout_2 = new QGridLayout(ControlsBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        ElapsedLabel = new QLabel(ControlsBox);
        ElapsedLabel->setObjectName(QStringLiteral("ElapsedLabel"));
        ElapsedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(ElapsedLabel, 1, 1, 1, 1);

        ElapsedTimeLabel = new QLabel(ControlsBox);
        ElapsedTimeLabel->setObjectName(QStringLiteral("ElapsedTimeLabel"));

        gridLayout_2->addWidget(ElapsedTimeLabel, 1, 2, 1, 1);

        RecordingStatus = new QLabel(ControlsBox);
        RecordingStatus->setObjectName(QStringLiteral("RecordingStatus"));
        RecordingStatus->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(RecordingStatus, 0, 1, 1, 2);

        RecordButton = new QPushButton(ControlsBox);
        RecordButton->setObjectName(QStringLiteral("RecordButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RecordButton->sizePolicy().hasHeightForWidth());
        RecordButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(RecordButton, 0, 0, 2, 1);


        gridLayout->addWidget(ControlsBox, 3, 0, 1, 3);

        FileStatus = new QLabel(RecordRawPanel);
        FileStatus->setObjectName(QStringLiteral("FileStatus"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(FileStatus->sizePolicy().hasHeightForWidth());
        FileStatus->setSizePolicy(sizePolicy1);
        FileStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(FileStatus, 2, 1, 1, 2);

        FolderLabel = new QLabel(RecordRawPanel);
        FolderLabel->setObjectName(QStringLiteral("FolderLabel"));
        FolderLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(FolderLabel, 0, 0, 1, 1);

        FolderLineEdit = new QLineEdit(RecordRawPanel);
        FolderLineEdit->setObjectName(QStringLiteral("FolderLineEdit"));

        gridLayout->addWidget(FolderLineEdit, 0, 1, 1, 1);

        FolderButton = new QPushButton(RecordRawPanel);
        FolderButton->setObjectName(QStringLiteral("FolderButton"));

        gridLayout->addWidget(FolderButton, 0, 2, 1, 1);

        FileLabel = new QLabel(RecordRawPanel);
        FileLabel->setObjectName(QStringLiteral("FileLabel"));
        FileLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(FileLabel, 1, 0, 1, 1);

        FileLineEdit = new QLineEdit(RecordRawPanel);
        FileLineEdit->setObjectName(QStringLiteral("FileLineEdit"));

        gridLayout->addWidget(FileLineEdit, 1, 1, 1, 1);

        FileButton = new QPushButton(RecordRawPanel);
        FileButton->setObjectName(QStringLiteral("FileButton"));

        gridLayout->addWidget(FileButton, 1, 2, 1, 1);


        retranslateUi(RecordRawPanel);

        QMetaObject::connectSlotsByName(RecordRawPanel);
    } // setupUi

    void retranslateUi(QWidget *RecordRawPanel)
    {
        RecordRawPanel->setWindowTitle(QApplication::translate("RecordRawPanel", "Form", 0));
        ControlsBox->setTitle(QApplication::translate("RecordRawPanel", "Controls", 0));
        ElapsedLabel->setText(QApplication::translate("RecordRawPanel", "Elapsed: ", 0));
        ElapsedTimeLabel->setText(QApplication::translate("RecordRawPanel", "00:00", 0));
        RecordingStatus->setText(QApplication::translate("RecordRawPanel", "Idle", 0));
        RecordButton->setText(QApplication::translate("RecordRawPanel", "Record", 0));
        FileStatus->setText(QApplication::translate("RecordRawPanel", "Checking filename...", 0));
        FolderLabel->setText(QApplication::translate("RecordRawPanel", "Recordings folder:", 0));
        FolderLineEdit->setText(QApplication::translate("RecordRawPanel", "D:/", 0));
        FolderButton->setText(QApplication::translate("RecordRawPanel", "Choose", 0));
        FileLabel->setText(QApplication::translate("RecordRawPanel", "Filename:", 0));
        FileButton->setText(QApplication::translate("RecordRawPanel", "Generate new", 0));
    } // retranslateUi

};

namespace Ui {
    class RecordRawPanel: public Ui_RecordRawPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDRAWPANEL_H
