#include "mainwindow.h"
#include <QColor>
#include <QColorDialog>
#include <QErrorMessage>
#include <QFileDialog>
#include <fstream>
#include "stagedata.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->scene = new EditorScene{this->stageSize};
    this->ui->editorView->setScene(this->scene);

    this->ui->colorPreview->setScene(new QGraphicsScene);

    /* toolbar */
    connect(this->ui->actionAdd_Worm, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setWorm()));
    connect(this->ui->actionAdd_Long_Girder, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setLongGirder()));
    connect(this->ui->actionShort_Girder, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setShortGirder()));

    QColor defaultColor{0xba, 0x8d, 0xc6};
    this->scene->setBgColor(defaultColor);
    this->ui->colorPreview->setBackgroundBrush(QBrush(defaultColor));

    this->showMaximized();
}

MainWindow::~MainWindow() {
    delete ui;
    delete scene;
}

void MainWindow::on_actionLejano_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Seleccione una imagen para el fondo lejano"), "/home", tr("Image Files (*.png)"));
    if (!fileName.isEmpty()) {
        this->fartherBgFile = fileName;
        this->scene->setFartherBg(QImage(fileName));
    }
}

void MainWindow::on_actionMedio_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Seleccione una imagen para el fondo medio"), "/home", tr("Image Files (*.png)"));
    if (!fileName.isEmpty()) {
        this->midBgFile = fileName;
        this->scene->setMedianBg(QImage(fileName));
    }
}

void MainWindow::on_actionCercano_triggered() {
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Seleccione una imagen para el fondo cercano"),
                                     "/home", tr("Image Files (*.png)"));
    if (!fileName.isEmpty()) {
        this->closeBgFile = fileName;
        this->scene->setCloserBg(QImage(fileName));
    }
}

void MainWindow::on_bgColorButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        this->scene->setBgColor(color);
        this->ui->colorPreview->setBackgroundBrush(QBrush(color));
    }
}

void MainWindow::on_actionOpen_triggered() {
    /* serializes the stage */
    StageData sd{this->stageSize.width(), stageSize.height()};

    sd.closeBgFile = this->closeBgFile;
    sd.medianBgFile = this->midBgFile;
    sd.fartherBgFile = this->fartherBgFile;
    sd.wormsHealth = this->ui->wormsHP->value();
    sd.numPlayers= this->ui->numPlayers->value();

    /* weapon ammo */
    const QString WEAPON_PREFIX = "wpn_";
    for(auto *child : this->ui->stageParams->children()) {
        if(child->objectName().startsWith(WEAPON_PREFIX)) {
            QString weaponName = child->objectName().remove(0, WEAPON_PREFIX.size());

            QSpinBox *widget = dynamic_cast<QSpinBox *>(child);
            sd.addWeaponAmmo(weaponName, widget->value());
        }
    }

    this->ui->editorView->serialize(sd);

    if (static_cast<int>(sd.numWorms()) < sd.numPlayers) {
        QErrorMessage::qtHandler()->showMessage("Se necesita al menos 1 worm por jugador");
        return;
    }

    /* gets the output file name */
    QString fileName = QFileDialog::getSaveFileName(this, tr("Nombre de archivo de salida"),
                                                    "/home", tr("YAML (*.yml)"));

    /* checks if a file was selected */
    if (fileName.isEmpty()) {
        return;
    }

    std::ofstream file;
    file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
    if (!file) {
        QErrorMessage::qtHandler()->showMessage("Error al abrir el archivo");
        return;
    }
    /* gets the base name of the file */
    QStringList list = fileName.split('/');
    QList<QString>::Iterator it = list.end();
    it--;
    QStringList list2 = it->split('.');
    sd.dump(file,list2[0].toStdString());
}
