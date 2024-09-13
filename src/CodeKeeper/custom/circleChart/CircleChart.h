#include <QProgressBar>
#include <QPainter>
#include <QColor>
#include <QVector>

#ifndef CIRCLECHART_H
#define CIRCLECHART_H

class CircleChart : public QProgressBar {
    Q_OBJECT

public:
    CircleChart(QWidget *parent = nullptr) : QProgressBar(parent) {
        // Установка фона прогресс-бара
        setStyleSheet("QProgressBar { background-color: transparent; border: none; }");
    }

    void setMaximumValue(int value) {
        QProgressBar::setMaximum(value);
    }

    void addValue(double value, QColor color) {
        values_.append(value);
        colors_.append(color);
        update();
    }

    void setHeight(int height) {
        height_ = height;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int width = this->width();
        int height = this->height();
        int diameter = qMin(width, height);
        int radius = diameter / 2;

        // Установка цвета фона
        painter.setBrush(Qt::NoBrush); // Заливка фона
        painter.setPen(Qt::NoPen); // Убираем границу
        painter.drawEllipse(QRectF(0, 0, diameter, diameter)); // Рисуем фон

        // Рисуем круги прогресса
        qreal progress = 0;
        for (int i = 0; i < values_.size(); i++) {
            qreal value = values_.at(i) / (qreal)maximum();
            painter.setBrush(colors_.at(i));
            painter.setPen(Qt::NoPen);
            painter.drawPie(QRectF(radius - height_ / 2, radius - height_ / 2, height_, height_),
                             (progress * 360) * 16, (value * 360) * 16);
            progress += value;
        }

        // Заполнение оставшегося пространства
        if (progress < 1.0) {
            painter.setBrush(Qt::NoBrush); // Цвет для оставшегося пространства
            painter.setPen(Qt::NoPen);
            painter.drawPie(QRectF(radius - height_ / 2, radius - height_ / 2, height_, height_),
                             (progress * 360) * 16, (1.0 - progress) * 360 * 16);
        }
    }

private:
    QVector<double> values_; // Изменен на double для большей точности
    QVector<QColor> colors_;
    int height_ = 20;
};

#endif // CIRCLECHART_H
