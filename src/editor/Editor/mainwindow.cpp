#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->scene = new EditorScene{QRect{0, 0, 13 * 250, 13 * 250}};
    this->ui->editorView->setScene(this->scene);

    /* toolbar */
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

void MainWindow::on_actionLejano_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                                      this,
                                      tr("Seleccione una imagen para el fondo lejano"),
                                      "/home",
                                      tr("Image Files (*.png)")
                                    );
    if(!fileName.isEmpty()) {
        this->sd.fartherBgFile = fileName;
        this->scene->setFartherBg(QImage(fileName));
    }
}

void MainWindow::on_actionMedio_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                                      this,
                                      tr("Seleccione una imagen para el fondo medio"),
                                      "/home",
                                      tr("Image Files (*.png)")
                                    );
    if(!fileName.isEmpty()) {
        this->sd.medianBgFile = fileName;
        this->scene->setMedianBg(QImage(fileName));
    }
}

void MainWindow::on_actionCercano_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                                      this,
                                      tr("Seleccione una imagen para el fondo cercano"),
                                      "/home",
                                      tr("Image Files (*.png)")
                                    );
    if(!fileName.isEmpty()) {
        this->sd.closeBgFile = fileName;
        this->scene->setCloserBg(QImage(fileName));
    }
}

void MainWindow::on_bgColorButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid()) {
        this->scene->setBgColor(color);
    }
}

void MainWindow::on_actionOpen_triggered() {
    /* serializes the stage */
    this->ui->editorView->serialize(this->sd);
    qDebug() << this->sd;
}
