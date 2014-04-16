#ifndef QIMAGEDRAWER_H
#define QIMAGEDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

class QImageDrawer : public QWidget
{
    Q_OBJECT
public:
    explicit QImageDrawer(QWidget *parent = 0);
    const QImage *image() const;
    QImage getCroppedImage();
    void setDrawMode(int);//-2: circle; -3: rect; -4: calibre (QButtonGroup id start with -2)
    void setPenColour(const QString &);
    bool isCircle();

public slots:
    void setImage(const QImage &);

signals:
    void calibreFinished(int, double);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    int m_drawMode;
    bool m_isCircle;
    QColor m_penColour;
    QImage m_image;
    QImage m_scaledImage;//this ensures user always crop correct region
    qreal m_scale;//m_scaledImage.size() / m_image.size()

    //all these values are calculated based on original image (m_image)
    QPoint m_mousePressed;
    QPoint m_mouseReleased;
    QPoint m_drawedCircleCentre;
    int m_drawedCircleRadius;
    QRect m_drawedRect;
    QLine m_drawedCalibre;
    qreal m_calibreRealSize;
};

#endif // QIMAGEDRAWER_H
