# **`☘️ CodeKeeper`**
### *Менеджер проектов для разработчиков*
![](imgs/1.png)

<br>

<a href="LICENSE.md"><kbd> <br>**Лицензия**<br><br> </kbd></a>
<a href="doc/Shortcuts.md"><kbd> <br>**Горячие клавиши**<br><br> </kbd></a>
<a href="doc/Installation.md"><kbd> <br>**Установка**<br><br> </kbd></a>
<a href="doc/Tweaks.md"><kbd> <br>**Твики**<br><br> </kbd></a>
<a href="doc/Screenshots.md"><kbd> <br>**Скриншоты**<br><br> </kbd></a>

<br>

---

<br>

![](https://img.shields.io/github/forks/Nighty3098/CodeKeeper?style=for-the-badge&color=9dc3ea&logoColor=D9E0EE&labelColor=1c1c29)
![](https://img.shields.io/github/downloads/Nighty3098/CodeKeeper/total?style=for-the-badge&color=e0ea9d&logoColor=D9E0EE&labelColor=171b22)
![](https://img.shields.io/github/stars/Nighty3098/CodeKeeper?style=for-the-badge&color=eed49f&logoColor=D9E0EE&labelColor=1c1c29)
<br><br>
<img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_cpp.png?raw=true" height="45px" />
<img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_c.png?raw=true" height="45px" />
<img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_qt.png?raw=true" height="45px" />
<img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_sqlite.png?raw=true" height="45px" />
<img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_git.png?raw=true" height="45px" />

<br>

---

## Описание

**CodeKeeper** — это современный менеджер проектов для разработчиков, объединяющий:
- Ведение и организацию проектов
- Управление задачами (todo, in progress, done)
- Ведение заметок (Markdown, txt, html)
- Интеграцию с Git и GitHub (просмотр репозиториев, коммитов, релизов, статистики)
- Синхронизацию данных
- Гибкую настройку интерфейса и тем
- Многоязычную поддержку (русский, английский, японский, немецкий, испанский)

Приложение построено на Qt, поддерживает кроссплатформенность и хранит данные локально в SQLite.

## Основные возможности

- **Проекты**: создание, удаление, сортировка, просмотр информации о репозитории, открытие в браузере, отслеживание статуса (не начат, в процессе, завершён и др.)
- **Задачи**: добавление, удаление, редактирование, фильтрация по проекту, drag&drop между статусами, прогресс-бар выполнения
- **Заметки**: древовидная структура, поддержка Markdown, drag&drop файлов, быстрый просмотр и редактирование
- **Git/GitHub**: подключение аккаунта, просмотр статистики, автоматическая синхронизация, поддержка токенов
- **Синхронизация**: ручная и автоматическая, поддержка нескольких аккаунтов
- **Палитра команд**: быстрый доступ к основным действиям через командную палитру
- **Кастомизация**: темы (custom dark, solarized, mac dark), настройка шрифтов, размеров, кастомный titlebar
- **Уведомления**: системный трей, всплывающие сообщения
- **Горячие клавиши**: см. [Shortcuts](doc/Shortcuts.md)

## Архитектура

- **Главное окно** (`MainWindow`): управление вкладками (проекты, задачи, заметки), отображение статистики, кастомизация интерфейса
- **Окна**: настройки (`SettingsWindow`), аккаунт (`AccountWindow`), синхронизация (`SyncWindow`), палитра команд (`CommandPalette`)
- **Модули**:
  - keeperFunc: логика работы с проектами, задачами, заметками
  - sql_db: работа с локальной БД SQLite
  - gitFunc: взаимодействие с git-репозиториями
  - custom: пользовательские виджеты (кликабельные лейблы, прогресс-бары, графики)
- **Данные**: хранятся локально в выбранной пользователем папке (SQLite + файлы заметок)

## Интерфейс

- Современный минималистичный дизайн
- Drag&drop для задач и заметок
- Кастомные виджеты для отображения статистики
- Системный трей и всплывающие уведомления
- Поддержка масштабирования и адаптивного UI

## Настройки

- Выбор темы и кастомизация внешнего вида
- Настройка языка интерфейса
- Подключение GitHub-аккаунта и токена
- Путь к папке хранения данных
- Включение/отключение автосинхронизации и автообновлений
- Гибкая настройка отображаемых метрик проектов

## Синхронизация и Git

- Поддержка ручной и автоматической синхронизации с удалённым репозиторием
- Просмотр информации о репозитории: коммиты, релизы, лицензия, языки, звёзды, форки, размер
- Получение статистики по задачам и проектам

## Быстрый старт

1. Ознакомьтесь с [инструкцией по установке](doc/Installation.md)
2. При первом запуске выберите папку для хранения данных и настройте параметры в окне настроек
3. Создайте первый проект, добавьте задачи и заметки
4. Подключите GitHub-аккаунт для расширенных возможностей

## Документация

- [Горячие клавиши](doc/Shortcuts.md)
- [Установка](doc/Installation.md)
- [Твики и советы](doc/Tweaks.md)
- [Скриншоты](doc/Screenshots.md)

## Обратная связь и поддержка

Если вы нашли баг или у вас есть предложения — пишите:

[![Discord](https://img.shields.io/discord/1238858182403559505.svg?label=Discord&logo=Discord&style=for-the-badge&color=f5a7a0&logoColor=FFFFFF&labelColor=1c1c29)](https://discord.gg/6xEc5WFK)
<br><br>
<a href="https://t.me/Night3098" target="blank"><img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_telegram.png?raw=true" width="45px"/></a>
<a href="https://discord.gg/#9707" target="blank"><img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_discord.png?raw=true" width="45px"/></a>
<a href="https://www.reddit.com/user/DEVELOPER0x31/" target="blank"><img src="https://github.com/Nighty3098/DevIcons/blob/main/badges/badges_reddit.png?raw=true" width="45px"/></a>
<br><br>

---

### **`💵 Поддержать проект`**
<img src="imgs/toncoin.png" width="45px"/>
<br>

***`UQCF-sPDO0QqkNtvy5CKSvYWEsZS6l7vzaytV36oYM0SNhKt`***
