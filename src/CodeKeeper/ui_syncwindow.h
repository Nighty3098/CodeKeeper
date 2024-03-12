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
    QLabel *title;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *repoPath;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *userName;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *saveL;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *saveBtn;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QWidget *SyncWindow)
    {
        if (SyncWindow->objectName().isEmpty())
            SyncWindow->setObjectName(QString::fromUtf8("SyncWindow"));
        SyncWindow->resize(498, 291);
        verticalLayout = new QVBoxLayout(SyncWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QLabel(SyncWindow);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(26);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        repoPath = new QLineEdit(SyncWindow);
        repoPath->setObjectName(QString::fromUtf8("repoPath"));
        repoPath->setMinimumSize(QSize(0, 30));
        repoPath->setFrame(false);

        horizontalLayout_2->addWidget(repoPath);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        userName = new QLineEdit(SyncWindow);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setMinimumSize(QSize(0, 30));
        userName->setFrame(false);

        horizontalLayout->addWidget(userName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        lineEdit = new QLineEdit(SyncWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setFrame(false);

        horizontalLayout_3->addWidget(lineEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

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
        repoPath->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Repository URL", nullptr));
        userName->setInputMask(QString());
        userName->setText(QString());
        userName->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Username from github", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("SyncWindow", "GitHub token", nullptr));
        saveBtn->setText(QCoreApplication::translate("SyncWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SyncWindow: public Ui_SyncWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCWINDOW_H
