#include "stagedata.h"
#include <QDebug>

StageData::StageData() {
}

void StageData::addWorm(QPointF position, qreal angle) {
    qDebug() << "Worm at " << position << " angle=" << angle;
}

void StageData::addShortGirder(QPointF position, qreal angle) {
    qDebug() << "Short girder at " << position << " angle=" << angle;
}

void StageData::addLongGirder(QPointF position, qreal angle) {
    qDebug() << "Long girder at " << position << " angle=" << angle;
}
