#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QInputDialog>
#include <algorithm>
#include<QIcon>
#include<QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon loadIcon("images.png");
     ui->pushButton->setIcon(loadIcon);
     ui->pushButton->setIconSize(QSize(24, 24)); 

    connect(ui->pushButton,    &QPushButton::clicked, this, &MainWindow::onLoadImageClicked); 
    connect(ui->pushButton_20, &QPushButton::clicked, this, &MainWindow::onSaveImageClicked); 
    connect(ui->UndoButton,   &QPushButton::clicked, this, &MainWindow::onUndoClicked); 
    connect(ui->pushButton_2,  &QPushButton::clicked, this, &MainWindow::onGreyscaleClicked); 
    connect(ui->pushButton_3,  &QPushButton::clicked, this, &MainWindow::onBlackAndWhiteClicked);
    connect(ui->pushButton_4,  &QPushButton::clicked, this, &MainWindow::onInvertClicked); 
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onFrameFilterClicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::onResizeFilterClicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::onBlurFilterClicked);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &MainWindow::onInfraredFilterClicked);
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
    ui->before->setPixmap(QPixmap::fromImage(currentImage).scaled(ui->before->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->after->clear();
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
    ui->before->setAlignment(Qt::AlignCenter);
    ui->before->setPixmap(QPixmap::fromImage(currentImage).scaled(
        ui->before->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

void MainWindow::updateProcessedImage(const QImage &img) {
    currentImage = img;
    ui->after->setPixmap(QPixmap::fromImage(img).scaled(ui->after->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
    updateProcessedImage(currentImage);
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
    updateProcessedImage(currentImage);
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
    updateProcessedImage(currentImage);
}

void MainWindow::onFrameFilterClicked() {
    if (!hasImage()) return;
    saveStateForUndo();

    bool okType;
    int type = QInputDialog::getInt(this, tr("Frame Type"),  tr("Choose Frame Type:\n1. Simple Frame\n2. Fancy Frame"),    1, 1, 2, 1, &okType);
    if (!okType) return;  

    bool okColor;
    int colorchoice = QInputDialog::getInt(this, tr("Frame Color"),   tr("Choose Color Choice:\n2. Black\n3. Red\n4. Green\n5. Blue"),    2, 2, 5, 1, &okColor);
    if (!okColor) return;  

    int thickness = (currentImage.width() < currentImage.height() ? currentImage.width() : currentImage.height()) / 30;
    if (thickness < 5) thickness = 5;

    int Red = 255, Green = 255, Blue = 255;
    if (colorchoice == 2) { Red = 0; Green = 0; Blue = 0; }
    else if (colorchoice == 3) { Red = 255; Green = 0; Blue = 0; }
    else if (colorchoice == 4) { Red = 0; Green = 255; Blue = 0; }
    else if (colorchoice == 5) { Red = 0; Green = 0; Blue = 255; }

    for (int i = 0; i < currentImage.height(); ++i) {
        for (int j = 0; j < currentImage.width(); ++j) {
            bool simpleframe = (j < thickness || j >= currentImage.width() - thickness || i < thickness || i >= currentImage.height() - thickness);
            int space = thickness + 20;
            int innerthickness = 10;
            bool outline = simpleframe;
            
            bool innerline = ((j - space > 0 && j < space + innerthickness && i - space > 0 && i < currentImage.height() - space) ||
                              (j > currentImage.width() - space - innerthickness && j < currentImage.width() - space && i - space > 0 && i < currentImage.height() - space) ||
                              (j > space && j < currentImage.width() - space && i - space > 0 && i < space + innerthickness) ||
                              (j > space && j < currentImage.width() - space && i > currentImage.height() - space - innerthickness && i < currentImage.height() - space));

            bool fancyframe = outline || innerline;

            if ((type == 1 && simpleframe) || (type == 2 && fancyframe)) {
                currentImage.setPixel(j, i, qRgb(Red, Green, Blue));
            }
        }
    }
    updateProcessedImage(currentImage);
}

void MainWindow::onResizeFilterClicked() {
    if (!hasImage()) return;
    saveStateForUndo();

    QString sizeMsg = "Original Size: " + QString::number(currentImage.width()) + " x " + QString::number(currentImage.height()) + "\n\nEnter new width:";

    bool ok1, ok2;
    int new_width = QInputDialog::getInt(this, "Resize", sizeMsg, currentImage.width(), 1, 100000, 1, &ok1);
    if (!ok1) return;

    QString heightMsg = "New Width: " + QString::number(new_width) + "\n\nEnter new height:";
    int new_height = QInputDialog::getInt(this, "Resize", heightMsg, currentImage.height(), 1, 100000, 1, &ok2);
    if (!ok2) return;

    QImage resized_image(new_width, new_height, currentImage.format());
    
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            int orig_i = (i * currentImage.height()) / new_height;
            int orig_j = (j * currentImage.width()) / new_width;

            resized_image.setPixel(j, i, currentImage.pixel(orig_j, orig_i));
        }
    }
    
     currentImage = resized_image;
     updateProcessedImage(currentImage);
}

void MainWindow::onBlurFilterClicked() {
    if (!hasImage()) return;
    saveStateForUndo();

    bool ok;
    int radius = QInputDialog::getInt(
        this, 
        "Blur Filter", 
        "Enter blur radius (Level 1 to 10):", 
        2,    
        1,    
        10,  
        1,     
        &ok
    );
    if (!ok) return;

    QImage sourceImage = currentImage;
    QImage resultImage = currentImage;

    int width = sourceImage.width();
    int height = sourceImage.height();

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            
            int newChannels[3] = {0, 0, 0};

            for (int c = 0; c < 3; ++c) {
                long long sum = 0;
                int count = 0;

                for (int di = -radius; di <= radius; ++di) {
                    for (int dj = -radius; dj <= radius; ++dj) {
                        int neig_i = i + di;
                        int neig_j = j + dj;

                        if (neig_i >= 0 && neig_i < width && neig_j >= 0 && neig_j < height) {
                            QColor neigColor(sourceImage.pixel(neig_i, neig_j));
                            int val = (c == 0) ? neigColor.red() : (c == 1) ? neigColor.green() : neigColor.blue();
                            sum += val;
                            count++;
                        }
                    }
                }
                if (count > 0) {
                    newChannels[c] = sum / count;
                }
            }

            resultImage.setPixel(i, j, qRgb(newChannels[0], newChannels[1], newChannels[2]));
        }
    }

    currentImage = resultImage;
    updateProcessedImage(resultImage);
}

void MainWindow::onInfraredFilterClicked() {
    if (!hasImage()) return;
    saveStateForUndo();

    int width = currentImage.width();
    int height = currentImage.height();

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            QColor color = currentImage.pixel(i, j);
            int red = color.red();
            int green = color.green();
            int blue = color.blue();

            int gray = (red + green + blue) / 3;

            int newRed = 255;
            int newGreen = gray;
            int newBlue = gray;

            currentImage.setPixel(i, j, qRgb(newRed, newGreen, newBlue));
        }
    }
    updateProcessedImage(currentImage);

}