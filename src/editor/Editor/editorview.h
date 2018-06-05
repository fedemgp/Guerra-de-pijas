#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>
#include <QObject>
#include <QEvent>

class EditorView : public QGraphicsView
{
    Q_OBJECT

public:
    EditorView(QWidget *parent);

public slots:
    void setWorm();
    void setShortGirder();
    void setLongGirder();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    bool event(QEvent *event);
    void hoverEvent(QHoverEvent *event);

    bool collides();
    void deleteAt(QPoint pos);
    void createAt(QPoint pos);

    QGraphicsPixmapItem *getResource();

private:
    std::string resource;
    QGraphicsPixmapItem *pix{nullptr};
};

#endif // EDITORVIEW_H
