/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QLabel *label_2;
    QFontComboBox *fontComboBox;
    QSpinBox *spinBox;
    QComboBox *comboBox;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *setupSyncBtn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *clearDataBtn;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveBtn;

    void setupUi(QWidget *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QString::fromUtf8("SettingsWindow"));
        SettingsWindow->resize(671, 680);
        verticalLayout = new QVBoxLayout(SettingsWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QLabel(SettingsWindow);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(26);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        label_1 = new QLabel(SettingsWindow);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_2 = new QLabel(SettingsWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        fontComboBox = new QFontComboBox(SettingsWindow);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SF Pro"));
        fontComboBox->setFont(font1);

        gridLayout->addWidget(fontComboBox, 1, 1, 1, 1);

        spinBox = new QSpinBox(SettingsWindow);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        comboBox = new QComboBox(SettingsWindow);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        label_3 = new QLabel(SettingsWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 100, -1, -1);
        setupSyncBtn = new QPushButton(SettingsWindow);
        setupSyncBtn->setObjectName(QString::fromUtf8("setupSyncBtn"));
        setupSyncBtn->setMinimumSize(QSize(0, 30));
        setupSyncBtn->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(setupSyncBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 100);
        clearDataBtn = new QPushButton(SettingsWindow);
        clearDataBtn->setObjectName(QString::fromUtf8("clearDataBtn"));
        clearDataBtn->setMinimumSize(QSize(0, 30));
        clearDataBtn->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_2->addWidget(clearDataBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        saveBtn = new QPushButton(SettingsWindow);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setMinimumSize(QSize(0, 30));
        saveBtn->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(saveBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SettingsWindow);

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QCoreApplication::translate("SettingsWindow", "Form", nullptr));
        title->setText(QCoreApplication::translate("SettingsWindow", "Settings", nullptr));
        label_1->setText(QCoreApplication::translate("SettingsWindow", "Font size", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsWindow", "Font style", nullptr));
        fontComboBox->setCurrentText(QCoreApplication::translate("SettingsWindow", "SF Pro", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SettingsWindow", "Dark", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SettingsWindow", "Light", nullptr));

        label_3->setText(QCoreApplication::translate("SettingsWindow", "Theme style", nullptr));
        setupSyncBtn->setText(QCoreApplication::translate("SettingsWindow", "Setup sync via GitHub", nullptr));
        clearDataBtn->setText(QCoreApplication::translate("SettingsWindow", "Clear data", nullptr));
        saveBtn->setText(QCoreApplication::translate("SettingsWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
