#include "editorview.h"
#include <QtDebug>
#include <QImage>
#include <QGraphicsPixmapItem>


EditorView::EditorView(QWidget *parent) : QGraphicsView(parent) {
    this->setAttribute(Qt::WA_Hover, true);
}

void EditorView::setWorm() {
    this->resource = ":/assets/stage/worm.png";
    if(this->pix) {
        delete this->pix;
    }

    this->pix = this->getResource();
}

void EditorView::setShortGirder() {
    this->resource = ":/assets/stage/short_girder.png";
    if(this->pix) {
        delete this->pix;
    }

    this->pix = this->getResource();
}

void EditorView::setLongGirder() {
    this->resource = ":/assets/stage/long_girder.png";
    if(this->pix) {
        delete this->pix;
    }

    this->pix = this->getResource();
}

void EditorView::mousePressEvent(QMouseEvent *) {
}

void EditorView::deleteAt(QPoint pos) {
    this->scene()->removeItem(this->pix);
    QGraphicsItem *item = this->itemAt(pos);
    if(item) {
        this->scene()->removeItem(item);
    }
    this->scene()->addItem(this->pix);
}

QGraphicsPixmapItem *EditorView::getResource() {
    QImage *img = new QImage;
    img->load(this->resource.c_str());

    QPixmap pix = pix.fromImage( *img, Qt::AutoColor );

    QGraphicsPixmapItem *pmap = new QGraphicsPixmapItem(0);
    pmap->setPixmap(pix);
    return pmap;
}

void EditorView::createAt(QPoint pos) {
    if(this->resource.length() == 0) {
        return;
    }

    QGraphicsPixmapItem *pmap = this->getResource();

    QPointF lpos = this->mapToScene(pos);
    lpos.rx() -= pmap->pixmap().width() / 2;
    lpos.ry() -= pmap->pixmap().height() / 2;

    if(this->collides()) {
        return;
    }

    pmap->setPos(lpos);
    this->scene()->addItem(pmap);
}

void EditorView::mouseReleaseEvent(QMouseEvent *event) {
    event->accept();

    if(event->button() & Qt::RightButton) {
        this->deleteAt(event->pos());
    } else {
        this->createAt(event->pos());
    }
}

void EditorView::mouseMoveEvent(QMouseEvent *event) {
    event->accept();
}

bool EditorView::event(QEvent *event) {
    switch(event->type()) {
        case QEvent::HoverMove:
            this->hoverEvent(static_cast<QHoverEvent*>(event));
            return true;
        case QEvent::HoverEnter:
            if(this->pix) {
                this->scene()->addItem(this->pix);
            }
            break;
        case QEvent::HoverLeave:
            if(this->pix) {
                this->scene()->removeItem(this->pix);
            }
            break;
        default:
            break;
    }

    return QGraphicsView::event(event);
}

void EditorView::hoverEvent(QHoverEvent *event) {
    if(!this->pix) {
        return;
    }

    QPointF pos = this->mapToScene(event->pos());
    pos.rx() -= this->pix->pixmap().width() / 2;
    pos.ry() -= this->pix->pixmap().height() / 2;

    this->pix->setPos(pos);
}

void EditorView::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
    if(event->isAccepted()) {
        return;
    }

    static qreal factor = 1.1;

    if(event->angleDelta().y() > 0) {
        scale(factor, factor);
    } else {
        scale(1 / factor, 1 / factor);
    }

    event->accept();
}

bool EditorView::collides() {
    for (QGraphicsItem* other : this->items(this->viewport()->rect()) ) {
        if(other == this->pix) {
            continue;
        }

        if(other->collidesWithItem(this->pix)) {
            return true;
        }
    }

    return false;
}
