#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColor>
#include <QList>


#ifndef COLORVALUEDISPLAY_H
#define COLORVALUEDISPLAY_H

class ColorValueDisplay : public QWidget {
    Q_OBJECT

public:
    ColorValueDisplay(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setSpacing(5);
        layout->setContentsMargins(5, 5, 5, 5);

        items_ = new QVector<ColorValueItem*>();
    }

    void addValue(const QString &text, int value, QColor color, QFont &font) {
        ColorValueItem *item = new ColorValueItem(text, value, color, font);
        items_->append(item);
        layout()->addWidget(item);
        update();
    }

private:
    class ColorValueItem : public QWidget {
    public:
        ColorValueItem(const QString &text, int value, QColor color, QFont &font, QWidget *parent = nullptr) : QWidget(parent) {
            QHBoxLayout *layout = new QHBoxLayout(this);
            layout->setSpacing(5);
            layout->setContentsMargins(0, 0, 0, 0);

            QLabel *colorLabel = new QLabel(this);
            colorLabel->setStyleSheet(QString("background-color: %1; border: 0px solid black; border-radius: 7px;").arg(color.name()));
            colorLabel->setFixedSize(15, 15);
            layout->addWidget(colorLabel);

            QLabel *dashLabel = new QLabel("-", this);
            dashLabel->setFont(font);
            layout->addWidget(dashLabel);

            QLabel *textLabel = new QLabel(text, this);
            textLabel->setFont(font);
            layout->addWidget(textLabel);

            QLabel *valueLabel = new QLabel(QString::number(value) + "%", this);
            valueLabel->setFont(font);
            layout->addWidget(valueLabel);
        }
    };

    QVector<ColorValueItem*> *items_;
};


#endif // COLORVALUEDISPLAY_H