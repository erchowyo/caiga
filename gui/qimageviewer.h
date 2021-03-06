#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class QImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit QImageViewer(QWidget *parent = 0);
    inline const QPixmap *pixmap() const { return &m_pixmap; }

public slots:
    inline void setPixmap(const QPixmap &pix) { m_pixmap = pix; update(); }
    inline void setImage(const QImage &qimg) {  m_pixmap = QPixmap::fromImage(qimg); update(); }

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap m_pixmap;
};

#endif // QIMAGEVIEWER_H
