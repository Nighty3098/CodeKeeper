/********************************************************************************
** Form generated from reading UI file 'syncwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCWINDOW_H
#define UI_SYNCWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SyncWindow
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *title;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *userNameText;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *repoUrlText;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *gitTokenText;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_12;
    QLineEdit *hostnameText;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *commitText;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_19;
    QCheckBox *isHostname;
    QSpacerItem *horizontalSpacer_20;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *isDate;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_15;
    QCheckBox *isTime;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *saveL;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *saveBtn;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QWidget *SyncWindow)
    {
        if (SyncWindow->objectName().isEmpty())
            SyncWindow->setObjectName(QString::fromUtf8("SyncWindow"));
        SyncWindow->resize(467, 623);
        verticalLayout = new QVBoxLayout(SyncWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        title = new QLabel(SyncWindow);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(26);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        userNameText = new QLineEdit(SyncWindow);
        userNameText->setObjectName(QString::fromUtf8("userNameText"));
        userNameText->setMinimumSize(QSize(0, 30));
        userNameText->setFrame(false);
        userNameText->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(userNameText);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        repoUrlText = new QLineEdit(SyncWindow);
        repoUrlText->setObjectName(QString::fromUtf8("repoUrlText"));
        repoUrlText->setMinimumSize(QSize(0, 30));
        repoUrlText->setFrame(false);
        repoUrlText->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(repoUrlText);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        gitTokenText = new QLineEdit(SyncWindow);
        gitTokenText->setObjectName(QString::fromUtf8("gitTokenText"));
        gitTokenText->setMinimumSize(QSize(0, 30));
        gitTokenText->setFrame(false);
        gitTokenText->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(gitTokenText);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);

        hostnameText = new QLineEdit(SyncWindow);
        hostnameText->setObjectName(QString::fromUtf8("hostnameText"));
        hostnameText->setMinimumSize(QSize(0, 30));
        hostnameText->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(hostnameText);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        commitText = new QLineEdit(SyncWindow);
        commitText->setObjectName(QString::fromUtf8("commitText"));
        commitText->setMinimumSize(QSize(0, 30));
        commitText->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(commitText);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_13);

        label = new QLabel(SyncWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_19);

        isHostname = new QCheckBox(SyncWindow);
        isHostname->setObjectName(QString::fromUtf8("isHostname"));

        horizontalLayout_9->addWidget(isHostname);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_20);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        isDate = new QCheckBox(SyncWindow);
        isDate->setObjectName(QString::fromUtf8("isDate"));

        horizontalLayout_8->addWidget(isDate);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_15);

        isTime = new QCheckBox(SyncWindow);
        isTime->setObjectName(QString::fromUtf8("isTime"));

        horizontalLayout_7->addWidget(isTime);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_16);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        saveL = new QHBoxLayout();
        saveL->setObjectName(QString::fromUtf8("saveL"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        saveL->addItem(horizontalSpacer_7);

        saveBtn = new QPushButton(SyncWindow);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setMinimumSize(QSize(200, 30));
        saveBtn->setMaximumSize(QSize(200, 16777215));

        saveL->addWidget(saveBtn);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        saveL->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(saveL);


        retranslateUi(SyncWindow);

        QMetaObject::connectSlotsByName(SyncWindow);
    } // setupUi

    void retranslateUi(QWidget *SyncWindow)
    {
        SyncWindow->setWindowTitle(QCoreApplication::translate("SyncWindow", "Form", nullptr));
        title->setText(QCoreApplication::translate("SyncWindow", "Sync Settings", nullptr));
        userNameText->setInputMask(QString());
        userNameText->setText(QString());
        userNameText->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Username from github", nullptr));
        repoUrlText->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Repository URL", nullptr));
        gitTokenText->setPlaceholderText(QCoreApplication::translate("SyncWindow", "GitHub token", nullptr));
        hostnameText->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Hostname", nullptr));
        commitText->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Commit text", nullptr));
        label->setText(QCoreApplication::translate("SyncWindow", "Commit data", nullptr));
        isHostname->setText(QCoreApplication::translate("SyncWindow", "Hostname", nullptr));
        isDate->setText(QCoreApplication::translate("SyncWindow", "Date", nullptr));
        isTime->setText(QCoreApplication::translate("SyncWindow", "Time", nullptr));
        saveBtn->setText(QCoreApplication::translate("SyncWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SyncWindow: public Ui_SyncWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCWINDOW_H
