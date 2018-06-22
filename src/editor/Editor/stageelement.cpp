#include "stageelement.h"

const double PI = 3.141592653589793;

StageElement::StageElement(const std::string &resource, ItemType type) :
    QGraphicsPixmapItem(nullptr), type(type), resource(resource) {
    this->setPixmap(this->getResource());
    this->setTransformOriginPoint(this->pixmap().width() / 2, this->pixmap().height() / 2);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

ItemType StageElement::getType() {
    return this->type;
}

qreal StageElement::getAngle() const {
    return this->angle / 180.0f * PI;
}

QPointF StageElement::getPosition() const {
    return this->pos();
}

void StageElement::increaseAngle() {
    this->angle += 90.0f / 10.0f;

    if(this->angle > 90.0f) {
        this->angle = 90.0f;
    }

    this->setRotation(this->angle);
}

void StageElement::decreaseAngle() {
    this->angle -= 90.0f / 10.0f;

    if(this->angle < -90.0f) {
        this->angle = -90.0f;
    }

    this->setRotation(this->angle);
}

QPixmap StageElement::getResource() {
    QImage *img = new QImage;
    img->load(this->resource.c_str());

    QPixmap pix = pix.fromImage(*img, Qt::AutoColor);
    return pix;
}

bool StageElement::canOverlap(StageElement *) {
    return false;
}
