#include <QtWidgets>

#ifndef PROGRESSCIRCLE_H
#define PROGRESSCIRCLE_H

class CircleProgressBar : public QWidget {
    Q_OBJECT

public:
    enum DisplayMode {
        Percent, // Display percentages
        CustomText, // Display custom text
        NoPercent, // Display value without percent sign
        Hidden // Hide text
    };

    explicit CircleProgressBar(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_StyledBackground, true);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setMinimumWidth(100);
        setMinimumHeight(100);

        m_backgroundColor = Qt::lightGray;
        m_progressColor = Qt::blue;
        m_lineWidth = 10; // default line width
        m_displayMode = Percent; // Default display mode
    }

    void setValue(int value) {
        m_value = value;
        update();
    }

    void setMaxValue(int maxValue) {
        m_maxValue = maxValue;
        update();
    }

    void setBackgroundColor(QColor color) {
        m_backgroundColor = color;
        update();
    }

    void setProgressColor(QColor color) {
        m_progressColor = color;
        update();
    }

    void setLineWidth(int width) {
        m_lineWidth = width;
        update();
    }

    void setDisplayMode(DisplayMode mode) {
        m_displayMode = mode;
        update();
    }

    void setCustomText(const QString &text) {
        m_customText = text; // Set the custom text
        update(); // Update the widget to reflect the change
    }

    int value() const { return m_value; }
    int maxValue() const { return m_maxValue; }
    int lineWidth() const { return m_lineWidth; }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int centerX = width() / 2;
        int centerY = height() / 2;
        int radius = qMin(centerX, centerY) - 5;

        // Draw the background circle
        QPen backgroundPen(m_backgroundColor);
        backgroundPen.setWidth(m_lineWidth);
        painter.setPen(backgroundPen);
        painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);

        // Calculate the angle based on the value
        qreal angle = (qreal)m_value / m_maxValue * 360;

        // Draw the progress arc
        QPainterPath progressPath;
        progressPath.moveTo(centerX, centerY - radius);
        progressPath.arcTo(centerX - radius, centerY - radius, 2 * radius, 2 * radius, 90, -angle);
        QPen progressPen(m_progressColor);
        progressPen.setWidth(m_lineWidth);
        progressPen.setCapStyle(Qt::RoundCap);
        painter.setPen(progressPen);
        painter.drawPath(progressPath);

        // Draw the text based on the display mode
        QString text;
        switch (m_displayMode) {
            case Percent:
                text = QString("%1%").arg(m_value * 100 / m_maxValue);
                break;
            case CustomText:
                text = m_customText;
                break;
            case NoPercent:
                text = QString::number(m_value);
                break;
            case Hidden:
                text = ""; // No text to display
                break;
        }

        if (!text.isEmpty()) {
            painter.drawText(QRect(centerX - radius, centerY - radius, 2 * radius, 2 * radius), Qt::AlignCenter, text);
        }
    }

private:
    int m_value = 0;
    int m_maxValue = 100;
    QColor m_backgroundColor;
    QColor m_progressColor;
    int m_lineWidth;
    DisplayMode m_displayMode; // Current display mode
    QString m_customText; // Custom text to display
};

#endif // PROGRESSCIRCLE_H