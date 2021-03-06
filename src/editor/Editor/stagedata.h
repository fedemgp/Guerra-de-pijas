#ifndef STAGEDATA_H
#define STAGEDATA_H

#include <QColor>
#include <QDebug>
#include <QPoint>
#include <QString>
#include <Qt>
#include <iostream>
#include <vector>
#include <map>
#include "yaml-cpp/yaml.h"

struct GirderData {
    QPointF position;
    qreal angle;
    qreal length;
};

struct WormData {
    QPointF position;
};

class StageData {
   public:
    QString fartherBgFile;
    QString medianBgFile;
    QString closeBgFile;
    QColor bgColor;
    int wormsHealth;
    int numPlayers;

    StageData(qreal width, qreal height);

    void dump(std::ostream &output, std::string fileName);

    std::size_t numWorms() const;

    void addWorm(QPointF position);
    void addShortGirder(QPointF position, qreal angle);
    void addLongGirder(QPointF position, qreal angle);
    void addWeaponAmmo(QString weaponName, int ammo);

   private:
    QPointF toGameCoords(const QPointF &point) const;

    qreal width;
    qreal height;
    std::vector<GirderData> girders;
    std::vector<WormData> worms;
    std::map<std::string, int> weapons;
};

#endif  // STAGEDATA_H
