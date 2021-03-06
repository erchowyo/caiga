#ifndef ANALYSER_H
#define ANALYSER_H

#include <QObject>
#include <QPoint>
#include <QStandardItemModel>
#include <QStringList>
#include <QStringListModel>
#include <QList>
#include <opencv2/core/core.hpp>
#include "classobject.h"
#include "core_lib.h"

namespace CAIGA
{
class CORE_LIB Analyser : public QObject
{
    Q_OBJECT
public:
    explicit Analyser(qreal scale, cv::Mat *markers, std::vector<std::vector <cv::Point> > contours, QObject *parent = 0);
    ~Analyser() {}
    void reset();
    QStandardItemModel *getDataModel();
    QStringList* getClassesList() { return &m_classes; }
    void addClass(const QString &);
    void deleteClass(int classIndex);
    QString getClassValues(int classIdx);
    int count();
    inline int classCount() const { return m_classes.size(); }
    qreal getMaximumDiameter();

    inline QString getScale() { return QString::number(scaleValue); }
    inline QString getImageArea() { return QString::number(m_markerMatrix->cols * m_markerMatrix->rows / scaleValue / scaleValue); }
    //below are functions that get the value at a specified index in type of QString
    inline QString getClassNameAt(int idx) { return m_classes.at(classIndexOfObject(idx)); }
    inline QString getAreaAt(int idx) { return QString::number(getObjectAt(idx).area()); }
    inline QString getPerimeterAt(int idx) { return QString::number(getObjectAt(idx).perimeter()); }
    inline QString getDiameterAt(int idx) { return QString::number(getObjectAt(idx).diameter()); }
    inline QString getFlatteningAt(int idx) { return QString::number(getObjectAt(idx).flattening()); }
    //below are based on class index
    inline QString getCountOfClass(int i) { return QString::number(classObjMap[i].count()); }
    inline QString getTotalAreaOfClass(int i) { return QString::number(classObjMap[i].totalArea()); }
    inline QString getAvgPercentOfClass(int i) { return QString::number(classObjMap[i].percentage() * 100); }
    inline QString getAvgAreaOfClass(int i) { return QString::number(classObjMap[i].averageArea()); }
    inline QString getAvgPerimeterOfClass(int i) { return QString::number(classObjMap[i].averagePerimeter()); }
    inline QString getAvgDiameterOfClass(int i) { return QString::number(classObjMap[i].averageDiameter()); }
    inline QString getAvgInterceptOfClass(int i) { return QString::number(classObjMap[i].averageIntercept()); }
    inline QString getAvgFlatteningOfClass(int i) { return QString::number(classObjMap[i].averageFlattening()); }
    inline QString getSizeNumberByPlanimetricOfClass(int i) { return QString::number(classObjMap[i].sizeNumberByPlanimetric()); }
    inline QString getSizeNumberByInterceptOfClass(int i) { return QString::number(classObjMap[i].sizeNumberByIntercept()); }

    QMap<int, ClassObject> classObjMap;

    //this static member function "find" the locations whose value equals to the given key
    //the Mat must have value which is of integer type
    static std::vector<cv::Point> findValuePoints(int key, const cv::Mat &m);
    static qreal distanceBetweenPoints(const cv::Point_<qreal> &pt1, const cv::Point_<qreal> &pt2);

signals:
    void foundContourIndex(const QModelIndex &);
    void currentClassChanged(int classIdx);
    void finished();

public slots:
    void findContourHasPoint(const QPointF &pt);
    void onModelIndexChanged(const QModelIndex &mIdx);
    void onClassChanged(const QModelIndex &mIndex, const QString classText);

private:
    QFutureWatcher<void> m_watcher;

    qreal scaleValue;//pixel / um
    int currentSelectedIdx;
    int previousClassIdx;
    cv::Mat *m_markerMatrix;
    std::vector<std::vector <cv::Point> > m_contours;
    QSet<int> boundarySet;//store all boundary objects' indice
    QSet<int> cornerSet;//store all corner objects' indice

    int classIndexOfObject(int idx);//get the class index of the idx-th object
    Object getObjectAt(int idx);
    QStringList m_classes;
    qreal averageIntercept;

    QStandardItemModel *contoursModel;
    QStringList headerLabels;

    void calculateByContours();

    qreal calculatePerimeter(int idx);
    qreal calculateContourAreaByPixels(int idx);
    qreal calculateFlattening(int idx);
    Object::POSITION determineIsBoundary(int idx);
    void updateBoundarySet();
    int getBoundaryJointNeighbours(const cv::Point_<qreal> &pos);//leave at least 1 position from Mat edge
    inline int getBoundaryJointNeighbours(const cv::Point &pos) { return getBoundaryJointNeighbours(cv::Point_<qreal> (pos.x, pos.y)); }//overload function of float-point one

    /*
     * calculate all sorts of information class by class
     * these functions would clear the previous values
     */
    void calculatePercentage();
    void calculateInterceptsByLine();
    void calculateIntercepts();//by triple circles
};
}

#endif // ANALYSER_H
