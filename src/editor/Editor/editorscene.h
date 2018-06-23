#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <set>
#include <string>
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <QImage>
#include <QColor>
#include "stageelement.h"
#include "qgraphicsitemlayer.h"


class EditorScene : public QGraphicsScene {
    Q_OBJECT

   public:
    EditorScene(QRect rect);

    void setCursor(StageElement *newCursor);
    void hideCursor();
    void showCursor();

    void addItem(QGraphicsItem *elem);
    void addItem(StageElement *elem);
    void removeItem(QGraphicsItem *elem);
    void removeItem(StageElement *elem);

    virtual QList<StageElement *> collidingItems(StageElement *elem);
    bool contains(StageElement *elem);

    void serialize(StageData &sd);

    /* background */
    void setBgColor(QColor color);
    void setFartherBg(QImage image);
    void setMedianBg(QImage image);
    void setCloserBg(QImage image);

   private:
    void setBackground(QImage image, QGraphicsItemLayer **layerPtr, qreal zValue);

    QRect rect;
    QColor bgColor;
    QGraphicsItemLayer *closeBg{nullptr};
    QGraphicsItemLayer *medianBg{nullptr};
    QGraphicsItemLayer *fartherBg{nullptr};
    QGraphicsItemLayer *bgColorLayer{nullptr};
    StageElement *cursor{nullptr};
    std::string resource;
    std::set<StageElement *> elements;
};

#endif  // EDITORSCENE_H
