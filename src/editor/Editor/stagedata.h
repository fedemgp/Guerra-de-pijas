#ifndef STAGEDATA_H
#define STAGEDATA_H

#include <Qt>
#include <QPoint>


class StageData
{
public:
    StageData();

    void addWorm(QPointF position, qreal angle);
    void addShortGirder(QPointF position, qreal angle);
    void addLongGirder(QPointF position, qreal angle);
};

#endif // STAGEDATA_H