#ifndef WORKHISTEQUALISE_H
#define WORKHISTEQUALISE_H
#include "workbase.h"
namespace CAIGA {
class WorkHistEqualise : public WorkBase
{
public:
    WorkHistEqualise(const cv::Mat *s) : WorkBase(s) { workType = HistEqualise; }
    void Func();
};
}
#endif // WORKHISTEQUALISE_H
