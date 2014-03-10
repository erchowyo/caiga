#ifndef IMAGE_H
#define IMAGE_H

#include <QStringList>
#include <QImage>
#include <QPixmap>
#include "caigaglobal.h"

/*
 * define inside CAIGA namespace
 * in case of global conflict
 */
namespace CAIGA {
// store QImage instead of Mat or QPixmap
class Image
{
public:
    Image();
    Image(QImage img);
    Image(Mat &matImg);
    Image(const QString &imgfile);
    Image(const QByteArray &orig, QByteArray *pre, QByteArray *pro, QStringList *info);
    ~Image();
    QImage getOrigImage();
    void setOrigImage(QImage img);
    QImage getProcessedImage();
    void setPreProcessedImage(QImage img);
    void setProcessedImage(QImage img);
    bool isPreProcessed();
    bool isProcessed();
    bool isAnalysed();
    QStringList getInfoList();

    static QImage convertMat2QImage(const cv::Mat &src);
    static QPixmap convertMat2QPixmap(const cv::Mat &src);
    static Mat preProcess(Mat &src);
    static Mat process(Mat &src);

private:
    QImage origImage;//original image
    QImage preprocessedImage;//pre-processed image
    QImage processedImage;//image ready to be analysed
    bool m_isPreProcessed;//with prefix "m_" to indicate an object instead of a function
    bool m_isProcessed;
    bool m_isAnalysed;

    /*
     * analysis data are defined below
     */

    QStringList infoList;//information displayed on the info text browser

};

}

#endif // IMAGE_H