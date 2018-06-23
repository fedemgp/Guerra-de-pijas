#ifndef STAGEDATA_H
#define STAGEDATA_H

#include <Qt>
#include <QPoint>
#include <QString>
#include <QColor>
#include <QDebug>
#include <iostream>


class StageData
{
public:
    QString fartherBgFile;
    QString medianBgFile;
    QString closeBgFile;
    QColor bgColor;

    StageData();

    friend QDebug operator<<(QDebug d, StageData &sd) {
        d << "BG color: " << sd.bgColor << endl;
        d << "BG close: " << sd.closeBgFile << endl;
        d << "BG median: " << sd.medianBgFile << endl;
        d << "BG farther: " << sd.fartherBgFile << endl;
        return d;
    }

    void addWorm(QPointF position, qreal angle);
    void addShortGirder(QPointF position, qreal angle);
    void addLongGirder(QPointF position, qreal angle);
};

#endif // STAGEDATA_H
