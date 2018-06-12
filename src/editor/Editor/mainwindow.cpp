#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->scene = new EditorScene;
    QRect r = QRect(0, 0, ui->editorView->width(), ui->editorView->height());
    this->scene->setSceneRect(r);
    this->ui->editorView->setScene(this->scene);

    connect(this->ui->actionAdd_Worm, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setWorm()));
    connect(this->ui->actionAdd_Long_Girder, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setLongGirder()));
    connect(this->ui->actionShort_Girder, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setShortGirder()));

    this->showMaximized();
}

MainWindow::~MainWindow() {
    delete ui;
    delete scene;
}
