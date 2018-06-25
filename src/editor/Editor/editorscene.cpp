#include "editorscene.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>

EditorScene::EditorScene(QRect rect) : QGraphicsScene(nullptr), rect(rect) {
    this->setSceneRect(rect);
}

void EditorScene::setCursor(StageElement *newCursor) {
    if (this->cursor) {
        delete this->cursor;
    }
    this->cursor = newCursor;
    QGraphicsScene::addItem(this->cursor);
}

void EditorScene::hideCursor() {
    if (this->cursor) {
        QGraphicsScene::removeItem(this->cursor);
    }
}

void EditorScene::showCursor() {
    if (this->cursor) {
        QGraphicsScene::addItem(this->cursor);
    }
}

void EditorScene::addItem(QGraphicsItem *elem) {
    if (elem->scene() != this) {
        QGraphicsScene::addItem(elem);
    }
}

void EditorScene::addItem(StageElement *elem) {
    if (elem->scene() != this) {
        QGraphicsScene::addItem(elem);
        this->elements.insert(elem);
    }
}

void EditorScene::removeItem(StageElement *elem) {
    if (this->contains(elem)) {
        this->elements.erase(this->elements.find(elem));
    }

    if (elem->scene()) {
        QGraphicsScene::removeItem(elem);
    }
}

void EditorScene::removeItem(QGraphicsItem *elem) {
    if (elem->scene()) {
        QGraphicsScene::removeItem(elem);
    }
}

void EditorScene::serialize(StageData &sd) {
    sd.bgColor = this->bgColor;
    for (auto *elem : this->elements) {
        elem->serialize(sd);
    }
}

QList<StageElement *> EditorScene::collidingItems(StageElement *elem) {
    QList<StageElement *> rv;
    for (QGraphicsItem *other : QGraphicsScene::collidingItems(elem)) {
        if (other == elem) {
            continue;
        }

        if (this->contains(dynamic_cast<StageElement *>(other))) {
            rv.append(dynamic_cast<StageElement *>(other));
        }
    }
    return rv;
}

bool EditorScene::contains(StageElement *elem) {
    auto it = this->elements.find(elem);
    return (it != this->elements.end());
}

void EditorScene::setBgColor(QColor color) {
    this->bgColor = color;
    if (this->bgColorLayer) {
        this->removeItem(this->bgColorLayer);
        delete this->bgColorLayer;
    }

    this->bgColorLayer = new QGraphicsItemLayer;
    this->bgColorLayer->setZValue(-4);
    this->addItem(this->bgColorLayer);
    QGraphicsRectItem *bg = new QGraphicsRectItem(this->rect, this->bgColorLayer);
    bg->setBrush(QBrush{color});
}

void EditorScene::setFartherBg(QImage image) {
    this->setBackground(image, &this->fartherBg, -3);
}

void EditorScene::setMedianBg(QImage image) {
    this->setBackground(image, &this->medianBg, -2);
}

void EditorScene::setCloserBg(QImage image) {
    this->setBackground(image, &this->closeBg, -1);
}

void EditorScene::setBackground(QImage image, QGraphicsItemLayer **layerPtr, qreal zValue) {
    if (*layerPtr) {
        this->removeItem(*layerPtr);
        delete *layerPtr;
    }

    *layerPtr = new QGraphicsItemLayer;
    QGraphicsItemLayer *layer = *layerPtr;

    layer->setZValue(zValue);
    this->addItem(layer);

    for (int i = 0; i < this->rect.width() / image.width() + 1; i++) {
        QGraphicsPixmapItem *pix = new QGraphicsPixmapItem{layer};
        pix->setPixmap(QPixmap::fromImage(image));
        pix->setPos(image.width() * i, this->rect.height() - image.height());
    }
}
