#include "editorview.h"
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QtDebug>
#include <cmath>
#include "stageelementworm.h"
#include "stageelemlonggirder.h"
#include "stageelemshortgirder.h"

const qreal cursorOpacity = 0.7;

EditorView::EditorView(QWidget *parent) : QGraphicsView(parent) {
    this->setAttribute(Qt::WA_Hover, true);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setLongGirder();
}

void EditorView::drawCloseBg(QString &) {
}

void EditorView::setScene(EditorScene *scene) {
    QGraphicsView::setScene(scene);
    this->escene = scene;
}

void EditorView::setWorm() {
    if (this->stageElem) {
        delete this->stageElem;
    }

    this->stageElem = new StageElementWorm{cursorOpacity};
}

void EditorView::setShortGirder() {
    if (this->stageElem) {
        delete this->stageElem;
    }

    this->stageElem = new StageElemShortGirder{cursorOpacity};
}

void EditorView::setLongGirder() {
    if (this->stageElem) {
        delete this->stageElem;
    }

    this->stageElem = new StageElemLongGirder{cursorOpacity};
}

void EditorView::mousePressEvent(QMouseEvent *) {}

void EditorView::deleteAt(QPoint pos) {
    this->scene()->removeItem(this->stageElem);
    QGraphicsItem *item = this->itemAt(pos);
    if (item) {
        this->escene->removeItem(dynamic_cast<StageElement *>(item));
    }
    this->escene->addItem(this->stageElem);
}

void EditorView::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Plus) {
        this->stageElem->increaseAngle();
    } else if(event->key() == Qt::Key_Minus) {
        this->stageElem->decreaseAngle();
    }
}

void EditorView::createAt(QPoint pos) {
    if (!this->stageElem) {
        return;
    }

    if (this->collides()) {
        return;
    }

    StageElement *newElem = this->stageElem->clone();

    QPointF lpos = this->mapToScene(pos);
    lpos.rx() -= newElem->pixmap().width() / 2;
    lpos.ry() -= newElem->pixmap().height() / 2;

    newElem->setPos(lpos);
    this->escene->addItem(newElem);
}

void EditorView::mouseReleaseEvent(QMouseEvent *event) {
    event->accept();

    if (event->button() & Qt::RightButton) {
        this->deleteAt(event->pos());
    } else {
        this->createAt(event->pos());
        this->stageElem->setZValue(1);
    }
}

void EditorView::mouseMoveEvent(QMouseEvent *event) {
    if (!this->stageElem) {
        return;
    }

    /* set the position of the hint image under the mouse */
    QPointF pos = this->mapToScene(event->pos());
    pos.rx() -= this->stageElem->pixmap().width() / 2;
    pos.ry() -= this->stageElem->pixmap().height() / 2;

    this->stageElem->setPos(pos);
    event->accept();
}

bool EditorView::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::HoverEnter:
            if (this->stageElem) {
                this->escene->addItem(this->stageElem);
            }
            return true;
        case QEvent::HoverLeave:
            if (this->stageElem) {
                this->scene()->removeItem(this->stageElem);
            }
            return true;
        default:
            break;
    }

    return QGraphicsView::event(event);
}

void EditorView::wheelEvent(QWheelEvent *event) {
    static qreal factor = 1.1;

    if (event->delta() > 0) {
        this->scale(factor, factor);
    } else {
        this->scale(1.0 / factor, 1.0 / factor);
    }

    /* set the position of the hint image under the mouse */
    QPointF pos = this->mapToScene(event->pos());
    pos.rx() -= this->stageElem->pixmap().width() / 2;
    pos.ry() -= this->stageElem->pixmap().height() / 2;

    this->stageElem->setPos(pos);
    event->accept();
}

bool EditorView::collides() {
    for(StageElement *other : this->escene->collidingItems(this->stageElem)) {
        if(!this->stageElem->canOverlap(other)) {
            return true;
        }
    }

    return false;
}

void EditorView::serialize(StageData &sd) const {
    this->escene->serialize(sd);
}
