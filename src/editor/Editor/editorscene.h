#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <set>
#include <string>
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include "stageelement.h"

class EditorScene : public QGraphicsScene {
    Q_OBJECT

   public:
    EditorScene(QWidget *parent = nullptr);

    void addItem(StageElement *elem);
    void removeItem(StageElement *elem);

    virtual QList<StageElement *> collidingItems(StageElement *elem);
    bool contains(StageElement *elem);

    void serialize(StageData &sd);

   private:
    std::string resource;
    std::set<StageElement *> elements;
};

#endif  // EDITORSCENE_H
