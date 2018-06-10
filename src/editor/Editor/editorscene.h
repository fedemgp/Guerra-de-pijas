#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

class EditorScene : public QGraphicsScene {
    Q_OBJECT

   public:
    EditorScene(QWidget *parent = nullptr);

   private:
    std::string resource;
};

#endif  // EDITORSCENE_H
