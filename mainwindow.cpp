#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,    &QPushButton::clicked, this, &MainWindow::onLoadImageClicked); 
    connect(ui->pushButton_20, &QPushButton::clicked, this, &MainWindow::onSaveImageClicked); 
    connect(ui->UndoButton, &QPushButton::clicked, this, &MainWindow::onUndoClicked); 
    connect(ui->pushButton_2,  &QPushButton::clicked, this, &MainWindow::onGreyscaleClicked); 
    connect(ui->pushButton_3,  &QPushButton::clicked, this, &MainWindow::onBlackAndWhiteClicked);
    connect(ui->pushButton_4,  &QPushButton::clicked, this, &MainWindow::onInvertClicked); 
}
MainWindow::~MainWindow() {
    delete ui;
}
bool MainWindow::hasImage() {
    if (currentImage.isNull()) {
        QMessageBox::warning(this, "Warning", "Please load an image first!");
        return false;
    }
    return true;
}
void MainWindow::onLoadImageClicked() {
    QString appDir = QCoreApplication::applicationDirPath();
    QString startDir = appDir + "/../images";
    if (!QDir(startDir).exists()){
        startDir = appDir + "/..";
    }
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", startDir,"Images (*.png *.jpg *.jpeg *.bmp)");
    if (fileName.isEmpty()) return;

    QImage img;
    if (!img.load(fileName)) {
        QMessageBox::warning(this, "Error", "Could not open this image.");
        return;
    }
    currentImage = img.convertToFormat(QImage::Format_ARGB32);
    imageHistory.clear(); 
    updateImageDisplay();
}
void MainWindow::onSaveImageClicked() {
    if (!hasImage()) return;

    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPG (*.jpg)");
    if (!fileName.isEmpty()) {
        if (currentImage.save(fileName))
            QMessageBox::information(this, "Success", "Image saved successfully!");
        else
            QMessageBox::warning(this, "Error", "Could not save the image.");
    }
}
void MainWindow::updateImageDisplay() {
    if (currentImage.isNull())
        return;
    ui->imagelabel->setAlignment(Qt::AlignCenter);
    ui->imagelabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
        ui->imagelabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWindow::saveStateForUndo(){
    imageHistory.append(currentImage);
    if (imageHistory.size() > 20) {
        imageHistory.removeFirst(); 
}
}
void MainWindow::onUndoClicked() {
    if (imageHistory.isEmpty()) {
        QMessageBox::information(this, "Undo", "Nothing to undo.");
        return;
    }
    currentImage = imageHistory.takeLast();
    updateImageDisplay();
}
//***************Filters***************
void MainWindow::onGreyscaleClicked() {
    if (!hasImage())return;
    saveStateForUndo();

    for (int y = 0; y < currentImage.height(); y++) {
        QRgb *line = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
        for (int x = 0; x < currentImage.width(); x++) {
            int average = (qRed(line[x]) + qGreen(line[x]) + qBlue(line[x])) / 3;
            line[x] = qRgba(average, average, average, qAlpha(line[x]));
        }
    }
    updateImageDisplay();
}
void MainWindow::onBlackAndWhiteClicked(){
    if (!hasImage()) return;
    saveStateForUndo();
    int threshold = 128;
    for (int y = 0 ; y < currentImage.height() ; y ++){
        QRgb *line = reinterpret_cast < QRgb *> (currentImage.scanLine(y));
        for (int x = 0 ; x < currentImage.width() ; x ++){
            int average = (qRed(line[x]) + qGreen(line[x]) + qBlue(line[x])) / 3;
            line[x] = qRgba(average < threshold ? 0 : 255, average < threshold ? 0 : 255, average < threshold ? 0 : 255, qAlpha(line[x]));
        }
    }
    updateImageDisplay();
}
void MainWindow::onInvertClicked() {
    if (!hasImage())  return;
    saveStateForUndo();

    for (int y = 0; y < currentImage.height(); y++) {
        QRgb *line = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
        for (int x = 0; x < currentImage.width(); x++) {
            line[x] = qRgba(255 - qRed(line[x]), 255 - qGreen(line[x]),
                            255 - qBlue(line[x]), qAlpha(line[x]));
        }
    }
    updateImageDisplay();
}
