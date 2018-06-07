#ifndef EDITOR_H
#define EDITOR_H

#include <QGraphicsView>
#include <QWheelEvent>

namespace Editor {
class Editor : public QGraphicsView {
   public:
    Editor(QWidget *parent);
    ~Editor();

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
};
}

// Q_DECLARE_METATYPE(Editor::Editor);

#endif  // EDITOR_H
