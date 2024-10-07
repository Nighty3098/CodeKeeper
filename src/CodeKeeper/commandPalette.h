#ifndef COMMANDPALETTE_H
#define COMMANDPALETTE_H
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>

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

  private slots:
    void getSettingsData();
    void setWindowSize();
    void setWindowPosition();
    void filterList(const QString &text);
};

#endif // COMMANDPALETTE_H
