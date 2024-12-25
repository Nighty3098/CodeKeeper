#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

class ClickableLabel : public QLabel
{
    Q_OBJECT
  public:
    explicit ClickableLabel(const QString &text, QWidget *parent = nullptr) : QLabel(parent), m_text(text)
    {
        setFixedHeight(25);
        setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QPixmap originalPixmap(":/expand.png");
        QPixmap coloredPixmap = changeIconColor(originalPixmap);
        m_pixmap = coloredPixmap;

        m_pixmapSize = QSize(20, 20);
        m_textColor = Qt::white;
    }

    void setCustomStyleSheet(const QString &styleSheet)
    {
        QLabel::setObjectName("subtitle");
        QLabel::setStyleSheet(styleSheet);
        updateFontSize();
        updateTextColor();
    }

    void setPixmapSize(int size)
    {
        m_pixmapSize = QSize(size, size);
        m_pixmap = m_pixmap.scaled(m_pixmapSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        update();
    }

    QPixmap changeIconColor(QPixmap pixmap)
    {
        QColor color = QColor("#fff");
        QPixmap coloredPixmap = pixmap;
        QPainter painter(&coloredPixmap);

        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(coloredPixmap.rect(), color);
        painter.end();

        return coloredPixmap;
    }

  signals:
    void clicked();

  protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        emit clicked();
        QLabel::mousePressEvent(event);
    }

    void paintEvent(QPaintEvent *event) override
    {
        QLabel::paintEvent(event);

        QPainter painter(this);
        int pixmapWidth = m_pixmap.width();
        int pixmapHeight = m_pixmap.height();
        painter.drawPixmap(5, (height() - pixmapHeight) / 2, m_pixmap);

        painter.setPen(m_textColor);

        int textX = pixmapWidth + 10;
        painter.drawText(textX, height() / 2 + painter.fontMetrics().height() / 4, m_text);
    }

  private:
    QString m_text;
    QPixmap m_pixmap;
    QSize m_pixmapSize;
    QColor m_textColor;

    void updateFontSize()
    {
        QStringList styleList = styleSheet().split(';');
        for (const QString &style : styleList)
        {
            if (style.contains("font-size:"))
            {
                QString fontSizeStr = style.split(':').last().trimmed();
                bool ok;
                int fontSize = fontSizeStr.split(' ').first().toInt(&ok);
                if (ok)
                {
                    QFont font = this->font();
                    font.setPointSize(fontSize);
                    setFont(font);
                }
                break;
            }
        }
    }

    void updateTextColor()
    {
        QStringList styleList = styleSheet().split(';');
        for (const QString &style : styleList)
        {
            if (style.contains("color:"))
            {
                QString colorStr = style.split(':').last().trimmed();
                QColor color(colorStr);
                if (color.isValid())
                {
                    m_textColor = color;
                }
                break;
            }
        }
    }
};
