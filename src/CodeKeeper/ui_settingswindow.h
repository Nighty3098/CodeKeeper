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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *appSettings;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *title;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QFontComboBox *fontSelector;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_9;
    QComboBox *themeSelector;
    QSpacerItem *horizontalSpacer_12;
    QSpinBox *fontSizeSelector;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *clearDataBtn;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *saveBtn;
    QSpacerItem *horizontalSpacer_6;
    QWidget *syncSettings;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_5;
    QLabel *title_2;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_29;
    QLineEdit *commitText;
    QSpacerItem *horizontalSpacer_30;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_27;
    QLineEdit *repoUrlText;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *hostnameText;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *gitTokenText;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *userNameText;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_34;
    QCheckBox *isAutoUpgrade;
    QSpacerItem *horizontalSpacer_33;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_37;
    QCheckBox *isAutoCommit;
    QSpacerItem *horizontalSpacer_38;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_21;
    QCheckBox *isHostname;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_23;
    QCheckBox *isDate;
    QSpacerItem *horizontalSpacer_24;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_25;
    QCheckBox *isTime;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *saveL;
    QSpacerItem *horizontalSpacer_31;
    QPushButton *saveBtn_2;
    QSpacerItem *horizontalSpacer_32;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_10;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *pathToStorage;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_35;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_36;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *openFolderBtn;
    QSpacerItem *horizontalSpacer_14;

    void setupUi(QMainWindow *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QString::fromUtf8("SettingsWindow"));
        SettingsWindow->resize(412, 701);
        SettingsWindow->setDocumentMode(false);
        centralwidget = new QWidget(SettingsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(400, 0));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::tab-bar { alignment: center; }"));
        appSettings = new QWidget();
        appSettings->setObjectName(QString::fromUtf8("appSettings"));
        verticalLayout_2 = new QVBoxLayout(appSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 138, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        title = new QLabel(appSettings);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(32);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(title);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_1 = new QLabel(appSettings);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        gridLayout->addWidget(label_1, 0, 1, 1, 1);

        label_2 = new QLabel(appSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        label_3 = new QLabel(appSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        fontSelector = new QFontComboBox(appSettings);
        fontSelector->setObjectName(QString::fromUtf8("fontSelector"));

        gridLayout->addWidget(fontSelector, 1, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 1, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 3, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 0, 3, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 2, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        themeSelector = new QComboBox(appSettings);
        themeSelector->addItem(QString());
        themeSelector->addItem(QString());
        themeSelector->setObjectName(QString::fromUtf8("themeSelector"));

        gridLayout->addWidget(themeSelector, 2, 2, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_12, 2, 3, 1, 1);

        fontSizeSelector = new QSpinBox(appSettings);
        fontSizeSelector->setObjectName(QString::fromUtf8("fontSizeSelector"));

        gridLayout->addWidget(fontSizeSelector, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        clearDataBtn = new QPushButton(appSettings);
        clearDataBtn->setObjectName(QString::fromUtf8("clearDataBtn"));
        clearDataBtn->setMinimumSize(QSize(200, 30));
        clearDataBtn->setMaximumSize(QSize(200, 30));

        horizontalLayout_2->addWidget(clearDataBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        saveBtn = new QPushButton(appSettings);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setMinimumSize(QSize(200, 30));
        saveBtn->setMaximumSize(QSize(200, 30));

        horizontalLayout_3->addWidget(saveBtn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tabWidget->addTab(appSettings, QString());
        syncSettings = new QWidget();
        syncSettings->setObjectName(QString::fromUtf8("syncSettings"));
        verticalLayout_4 = new QVBoxLayout(syncSettings);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        title_2 = new QLabel(syncSettings);
        title_2->setObjectName(QString::fromUtf8("title_2"));
        QFont font1;
        font1.setPointSize(26);
        title_2->setFont(font1);
        title_2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(title_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_29);

        commitText = new QLineEdit(syncSettings);
        commitText->setObjectName(QString::fromUtf8("commitText"));
        commitText->setMinimumSize(QSize(0, 30));
        commitText->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(commitText);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_30);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_27);

        repoUrlText = new QLineEdit(syncSettings);
        repoUrlText->setObjectName(QString::fromUtf8("repoUrlText"));
        repoUrlText->setMinimumSize(QSize(0, 30));
        repoUrlText->setFrame(false);
        repoUrlText->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(repoUrlText);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_28);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_17);

        hostnameText = new QLineEdit(syncSettings);
        hostnameText->setObjectName(QString::fromUtf8("hostnameText"));
        hostnameText->setMinimumSize(QSize(0, 30));
        hostnameText->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(hostnameText);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_18);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_15);

        gitTokenText = new QLineEdit(syncSettings);
        gitTokenText->setObjectName(QString::fromUtf8("gitTokenText"));
        gitTokenText->setMinimumSize(QSize(0, 30));
        gitTokenText->setFrame(false);
        gitTokenText->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(gitTokenText);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_16);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        userNameText = new QLineEdit(syncSettings);
        userNameText->setObjectName(QString::fromUtf8("userNameText"));
        userNameText->setMinimumSize(QSize(0, 30));
        userNameText->setFrame(false);
        userNameText->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(userNameText);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_34);

        isAutoUpgrade = new QCheckBox(syncSettings);
        isAutoUpgrade->setObjectName(QString::fromUtf8("isAutoUpgrade"));

        horizontalLayout_13->addWidget(isAutoUpgrade);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_33);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_37 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_37);

        isAutoCommit = new QCheckBox(syncSettings);
        isAutoCommit->setObjectName(QString::fromUtf8("isAutoCommit"));

        horizontalLayout_15->addWidget(isAutoCommit);

        horizontalSpacer_38 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_38);


        verticalLayout_4->addLayout(horizontalLayout_15);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_7);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_19);

        label_4 = new QLabel(syncSettings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_4);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_20);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_9);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_21);

        isHostname = new QCheckBox(syncSettings);
        isHostname->setObjectName(QString::fromUtf8("isHostname"));

        horizontalLayout_9->addWidget(isHostname);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_22);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_23);

        isDate = new QCheckBox(syncSettings);
        isDate->setObjectName(QString::fromUtf8("isDate"));

        horizontalLayout_8->addWidget(isDate);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_24);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_25);

        isTime = new QCheckBox(syncSettings);
        isTime->setObjectName(QString::fromUtf8("isTime"));

        horizontalLayout_10->addWidget(isTime);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_26);


        verticalLayout_3->addLayout(horizontalLayout_10);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_8);

        saveL = new QHBoxLayout();
        saveL->setObjectName(QString::fromUtf8("saveL"));
        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        saveL->addItem(horizontalSpacer_31);

        saveBtn_2 = new QPushButton(syncSettings);
        saveBtn_2->setObjectName(QString::fromUtf8("saveBtn_2"));
        saveBtn_2->setMinimumSize(QSize(200, 30));
        saveBtn_2->setMaximumSize(QSize(200, 16777215));

        saveL->addWidget(saveBtn_2);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        saveL->addItem(horizontalSpacer_32);


        verticalLayout_4->addLayout(saveL);

        tabWidget->addTab(syncSettings, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_10);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pathToStorage = new QLabel(tab);
        pathToStorage->setObjectName(QString::fromUtf8("pathToStorage"));
        QFont font2;
        font2.setPointSize(12);
        pathToStorage->setFont(font2);
        pathToStorage->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(pathToStorage);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalSpacer_35 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_35);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(200, 30));
        pushButton->setMaximumSize(QSize(200, 30));

        horizontalLayout_14->addWidget(pushButton);

        horizontalSpacer_36 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_36);


        verticalLayout_6->addLayout(horizontalLayout_14);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        openFolderBtn = new QPushButton(tab);
        openFolderBtn->setObjectName(QString::fromUtf8("openFolderBtn"));
        openFolderBtn->setMinimumSize(QSize(200, 30));

        horizontalLayout_4->addWidget(openFolderBtn);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);


        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(verticalLayout_6);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        SettingsWindow->setCentralWidget(centralwidget);

        retranslateUi(SettingsWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QCoreApplication::translate("SettingsWindow", "MainWindow", nullptr));
        title->setText(QCoreApplication::translate("SettingsWindow", "Settings", nullptr));
        label_1->setText(QCoreApplication::translate("SettingsWindow", "Font size", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsWindow", "Font style", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsWindow", "Theme", nullptr));
        themeSelector->setItemText(0, QCoreApplication::translate("SettingsWindow", "Dark", nullptr));
        themeSelector->setItemText(1, QCoreApplication::translate("SettingsWindow", "Light", nullptr));

        clearDataBtn->setText(QCoreApplication::translate("SettingsWindow", "Clear data", nullptr));
        saveBtn->setText(QCoreApplication::translate("SettingsWindow", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(appSettings), QCoreApplication::translate("SettingsWindow", "App settings", nullptr));
        title_2->setText(QCoreApplication::translate("SettingsWindow", "Sync Settings", nullptr));
        commitText->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Commit text", nullptr));
        repoUrlText->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Repository URL", nullptr));
        hostnameText->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Hostname", nullptr));
        gitTokenText->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "GitHub token", nullptr));
        userNameText->setInputMask(QString());
        userNameText->setText(QString());
        userNameText->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Username from github", nullptr));
        isAutoUpgrade->setText(QCoreApplication::translate("SettingsWindow", "Get updates from repo after start (Git)", nullptr));
        isAutoCommit->setText(QCoreApplication::translate("SettingsWindow", "Auto commit and push (Git)", nullptr));
        label_4->setText(QCoreApplication::translate("SettingsWindow", "Commit data", nullptr));
        isHostname->setText(QCoreApplication::translate("SettingsWindow", "Hostname", nullptr));
        isDate->setText(QCoreApplication::translate("SettingsWindow", "Date", nullptr));
        isTime->setText(QCoreApplication::translate("SettingsWindow", "Time", nullptr));
        saveBtn_2->setText(QCoreApplication::translate("SettingsWindow", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(syncSettings), QCoreApplication::translate("SettingsWindow", "Sync settings", nullptr));
        label_5->setText(QCoreApplication::translate("SettingsWindow", "Storage settings", nullptr));
        pathToStorage->setText(QString());
        pushButton->setText(QCoreApplication::translate("SettingsWindow", "Open folder", nullptr));
        openFolderBtn->setText(QCoreApplication::translate("SettingsWindow", "Set folder as storage", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SettingsWindow", "Storage settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
