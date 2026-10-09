#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    if (buttons.size() > 0) {
        connect(buttons[0], &QPushButton::clicked, this, &MainWindow::onLoadImageClicked);
    }
    if (buttons.size() > 1) {
        connect(buttons[1], &QPushButton::clicked, this, &MainWindow::onSaveImageClicked);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoadImageClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        currentImage.load(fileName);
        updateImageDisplay();
    }
}

void MainWindow::onSaveImageClicked() {
    if (currentImage.isNull()) {
        QMessageBox::warning(this, "Warning", "No image loaded to save!");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPG (*.jpg)");
    if (!fileName.isEmpty()) {
        currentImage.save(fileName);
        QMessageBox::information(this, "Success", "Image saved successfully!");
    }
}

void MainWindow::updateImageDisplay() {
    QLabel *label = findChild<QLabel*>();
    if (label && !currentImage.isNull()) {
        label->setPixmap(QPixmap::fromImage(currentImage).scaled(
            label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}