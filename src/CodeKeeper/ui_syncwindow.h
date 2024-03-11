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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SyncWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QVBoxLayout *inputL;
    QLineEdit *userName;
    QLineEdit *repoPath;
    QLineEdit *lineEdit;
    QHBoxLayout *saveL;
    QPushButton *saveBtn;

    void setupUi(QWidget *SyncWindow)
    {
        if (SyncWindow->objectName().isEmpty())
            SyncWindow->setObjectName(QString::fromUtf8("SyncWindow"));
        SyncWindow->resize(606, 472);
        verticalLayout = new QVBoxLayout(SyncWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QLabel(SyncWindow);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(26);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        inputL = new QVBoxLayout();
        inputL->setObjectName(QString::fromUtf8("inputL"));
        userName = new QLineEdit(SyncWindow);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setMinimumSize(QSize(0, 30));
        userName->setFrame(false);

        inputL->addWidget(userName);

        repoPath = new QLineEdit(SyncWindow);
        repoPath->setObjectName(QString::fromUtf8("repoPath"));
        repoPath->setMinimumSize(QSize(0, 30));
        repoPath->setFrame(false);

        inputL->addWidget(repoPath);

        lineEdit = new QLineEdit(SyncWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setFrame(false);

        inputL->addWidget(lineEdit);


        verticalLayout->addLayout(inputL);

        saveL = new QHBoxLayout();
        saveL->setObjectName(QString::fromUtf8("saveL"));
        saveBtn = new QPushButton(SyncWindow);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setMinimumSize(QSize(0, 30));
        saveBtn->setMaximumSize(QSize(200, 16777215));

        saveL->addWidget(saveBtn);


        verticalLayout->addLayout(saveL);


        retranslateUi(SyncWindow);

        QMetaObject::connectSlotsByName(SyncWindow);
    } // setupUi

    void retranslateUi(QWidget *SyncWindow)
    {
        SyncWindow->setWindowTitle(QCoreApplication::translate("SyncWindow", "Form", nullptr));
        title->setText(QCoreApplication::translate("SyncWindow", "Sync Settings", nullptr));
        userName->setInputMask(QString());
        userName->setText(QString());
        userName->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Username from github", nullptr));
        repoPath->setPlaceholderText(QCoreApplication::translate("SyncWindow", "Repository URL", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("SyncWindow", "GitHub token", nullptr));
        saveBtn->setText(QCoreApplication::translate("SyncWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SyncWindow: public Ui_SyncWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCWINDOW_H
