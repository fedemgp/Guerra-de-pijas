#ifndef STAGEDATA_H
#define STAGEDATA_H

#include <vector>
#include <Qt>
#include <QPoint>
#include <QString>
#include <QColor>
#include <QDebug>
#include <iostream>
#include "yaml-cpp/yaml.h"

struct GirderData {
    QPointF position;
    qreal angle;
};

struct WormData {
    QPointF position;
};

class StageData
{
public:
    QString fartherBgFile;
    QString medianBgFile;
    QString closeBgFile;
    QColor bgColor;

    StageData();

    void dump(std::ostream &output);

    void addWorm(QPointF position);
    void addShortGirder(QPointF position, qreal angle);
    void addLongGirder(QPointF position, qreal angle);

private:
    std::vector<GirderData> longGirders;
    std::vector<GirderData> shortGirders;
    std::vector<WormData> worms;
};

#endif // STAGEDATA_H
