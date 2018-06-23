#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QEvent>
#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>
#include <QWidget>
#include "stageelement.h"
#include "editorscene.h"


class EditorView : public QGraphicsView {
    Q_OBJECT

   public:
    EditorView(QWidget *parent);
    virtual void setScene(EditorScene *scene);

    void drawCloseBg(QString &fileName);

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
    void keyPressEvent(QKeyEvent *event);

    bool collides();
    void deleteAt(QPoint pos);
    void createAt(QPoint pos);

   private:
    StageElement *stageElem{nullptr};
    EditorScene *escene{nullptr};
};

#endif  // EDITORVIEW_H
