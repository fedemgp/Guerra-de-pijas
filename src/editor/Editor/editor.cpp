#include "editor.h"

Editor::Editor::Editor(QWidget *parent) : QGraphicsView(parent) {}

Editor::Editor::~Editor() {}

void Editor::Editor::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
    if (event->isAccepted()) {
        return;
    }

    static qreal factor = 1.1;

    if (event->angleDelta().y() > 0) {
        scale(factor, factor);
    } else {
        scale(1 / factor, 1 / factor);
    }

    event->accept();
}

void Editor::Editor::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);
    if (event->isAccepted()) {
        return;
    }

    switch (event->button()) {
        case Qt::LeftButton:
            break;

        case Qt::RightButton:
            break;

        default:
            break;
    }

    event->accept();
}
