#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include "editorscene.h"
#include <QString>


namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLejano_triggered();

    void on_actionMedio_triggered();

    void on_actionCercano_triggered();

    void on_bgColorButton_clicked();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    EditorScene *scene;
    QString closeBgFile;
    QString midBgFile;
    QString fartherBgFile;
};

#endif  // MAINWINDOW_H
