void CommandPalette::getSettingsData()
{
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
}

void CommandPalette::setWindowSize()
{
    MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());
    int width = mainWindow->width();
    if (width < 1920)
    {
        width = width - 200;
    }
    if (width > 1920)
    {
        width = 1500;
    }

    int height = 400;

    setFixedSize(width, height);
    qDebug() << "Set commands window size";
}

void CommandPalette::setWindowPosition()
{
    QThread *commandsWindowThread = new QThread;
    QObject::connect(commandsWindowThread, &QThread::started, this, [this]() {
        MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());
        QRect geo = mainWindow->geometry();
        int x = geo.x();
        int y = geo.y();
        int width = geo.width();
        int height = geo.height();

        QRect geo2 = this->geometry();

        int width2 = geo2.width();
        int height2 = geo2.height();

        int new_x = x + (width - width2) / 2;
        int new_y = y + (height - height2) / 4;

        this->move(new_x, new_y);

        qDebug() << "Set commands window position";
    });
    commandsWindowThread->start();
}

void CommandPalette::filterList(const QString &text)
{
    for (int i = 0; i < listItems->count(); ++i)
    {
        QListWidgetItem *item = listItems->item(i);
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}

void CommandPalette::activateCommand(QListWidgetItem *item)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(parent());
    SettingsWindow *settingsWindow = static_cast<SettingsWindow *>(parent());

    if (item == settingsItem)
    {
        qDebug() << "Run settings action";
        mainWindow->openSettingsWindow();
    }
    else if (item == syncItem)
    {
        qDebug() << "Run sync action";
        mainWindow->openSyncWindow();
    }
    else if (item == helpItem)
    {
        qDebug() << "Run help action";
        QDesktopServices::openUrl(QUrl("https://github.com/Nighty3098/CodeKeeper/wiki"));
    }
    else if (item == aboutItem)
    {
        qDebug() << "Run about action";
        QDesktopServices::openUrl(QUrl("https://github.com/Nighty3098/CodeKeeper"));
    }
    else if (item == clearAllDataItem)
    {
        qDebug() << "Run rm_data action";
        mainWindow->deleteAllData();
    }
    else if (item == userProfileItem)
    {
        qDebug() << "Run account action";
        mainWindow->fOpenAccountWindow();
    }

    this->close();
}
