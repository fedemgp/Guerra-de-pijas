#include "stageelement.h"
#include <QPainter>

const double PI = 3.141592653589793;

StageElement::StageElement(const std::string &resource, ItemType type, qreal opacity)
    : QGraphicsPixmapItem(nullptr), type(type), resource(resource) {
    this->setPixmap(this->getResource(opacity));
    this->setTransformOriginPoint(this->pixmap().width() / 2, this->pixmap().height() / 2);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

ItemType StageElement::getType() {
    return this->type;
}

qreal StageElement::getAngle() const {
    return this->angle;
}

QPointF StageElement::getPosition() const {
    qreal hw = this->pixmap().width() / 2.0;
    qreal hh = this->pixmap().height() / 2.0;
    return QPointF{this->pos().x() + hw, this->pos().y() + hh};
}

void StageElement::increaseAngle() {
    this->angle += 90.0f / 10.0f;

    if (this->angle > 90.0f) {
        this->angle = 90.0f;
    }

    this->setRotation(this->angle);
}

void StageElement::decreaseAngle() {
    this->angle -= 90.0f / 10.0f;

    if (this->angle < -90.0f) {
        this->angle = -90.0f;
    }

    this->setRotation(this->angle);
}

QPixmap StageElement::getResource(qreal opacity) {
    QImage image;
    image.load(this->resource.c_str());
    image = image.convertToFormat(QImage::Format_ARGB32);

    QImage image2(image.size(), QImage::Format_ARGB32);
    image2.fill(Qt::transparent);

    QPainter painter(&image2);
    painter.setOpacity(opacity);
    painter.drawImage(image.rect(), image);

    return QPixmap::fromImage(image2);
}

bool StageElement::canOverlap(StageElement *) {
    return false;
}
