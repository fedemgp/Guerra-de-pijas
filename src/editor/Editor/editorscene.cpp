#include "editorscene.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMouseEvent>

EditorScene::EditorScene(QWidget *parent) : QGraphicsScene(parent) {
}

void EditorScene::addItem(StageElement *elem) {
    QGraphicsScene::addItem(elem);
    this->elements.insert(elem);
}

void EditorScene::removeItem(StageElement *elem) {
    if(this->contains(elem)) {
        this->elements.erase(this->elements.find(elem));
        QGraphicsScene::removeItem(elem);
    }
}

void EditorScene::serialize(StageData &sd) {
    for(auto *elem : this->elements) {
        elem->serialize(sd);
    }
}

QList<StageElement *> EditorScene::collidingItems(StageElement *elem) {
    QList<StageElement *> rv;
    for (QGraphicsItem *other : QGraphicsScene::collidingItems(elem)) {
        if (other == elem) {
            continue;
        }

        if(this->contains(dynamic_cast<StageElement *>(other))) {
            rv.append(dynamic_cast<StageElement *>(other));
        }
    }
    return rv;
}

bool EditorScene::contains(StageElement *elem) {
    auto it = this->elements.find(elem);
    return (it != this->elements.end());
}
