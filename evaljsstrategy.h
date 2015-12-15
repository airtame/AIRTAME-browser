#ifndef EVALJSSTRATEGY_H
#define EVALJSSTRATEGY_H
#include <QString>

class EvalJsStrategy
{
public:
    EvalJsStrategy();
    virtual ~EvalJsStrategy();
    virtual void evalJS(const QString jscmd) = 0;

};

#endif // EVALJSSTRATEGY_H
