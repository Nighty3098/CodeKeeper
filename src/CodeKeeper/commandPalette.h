#ifndef COMMANDPALETTE_H
#define COMMANDPALETTE_H
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>

#include "accountwindow.h"
#include "settingswindow.h"
#include "syncwindow.h"

class CommandPalette : public QMainWindow
{
    Q_OBJECT
  public:
    explicit CommandPalette(QWidget *parent = nullptr);
    ~CommandPalette();

    void setFontStyle();

    QSettings *globalSettings;

    QFont selectedFont;
    QString font_size;

  private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLineEdit *searchBar;
    QListWidget *listItems;
    QPushButton *closeBtn;

    QListWidgetItem *settingsItem;
    QListWidgetItem *syncItem;
    QListWidgetItem *helpItem;
    QListWidgetItem *aboutItem;
    QListWidgetItem *checkUpdatesItem;
    QListWidgetItem *clearAllDataItem;
    QListWidgetItem *userProfileItem;
    QListWidgetItem *hideMenuItem;

  private slots:
    void getSettingsData();
    void setWindowSize();
    void setWindowPosition();
    void filterList(const QString &text);
    void activateCommand(QListWidgetItem *item);
};

#endif // COMMANDPALETTE_H
