#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QInputDialog>
#include <algorithm>
#include<QIcon>
#include<QSize>
#include <QDialog>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QInputDialog>
#include<QTransform>
#include <cstdlib>
#include <cmath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->setStyleSheet("");
    const auto allWidgets = findChildren<QWidget *>();
    for (QWidget *w : allWidgets) {
        w->setStyleSheet("");
    }
    ui->LoadButton->setText("Load Image \U0001F4C2");
    ui->SaveButton->setText("Save Image \U0001F4BE");
    ui->LoadButton->setProperty("primary", true);
    ui->SaveButton->setProperty("primary", true);
    ui->LoadButton->setFixedSize(160, 44);
    ui->SaveButton->setFixedSize(160, 44);
    ui->LoadButton->setCursor(Qt::PointingHandCursor);
    ui->SaveButton->setCursor(Qt::PointingHandCursor);
    connect(ui->LoadButton, &QPushButton::clicked, this, &MainWindow::onLoadImageClicked); 
    connect(ui->SaveButton, &QPushButton::clicked, this, &MainWindow::onSaveImageClicked); 
    connect(ui->UndoButton, &QPushButton::clicked, this, &MainWindow::onUndoClicked); 
    connect(ui->RedoButton, &QPushButton::clicked, this, &MainWindow::onRedoClicked);
    connect(ui->ResetButton , &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->ThemeButton , &QPushButton::clicked, this, &MainWindow::onThemeToggleClicked);
    ui->optionsPanel->hide();
    connect(ui->applyOptionsButton, &QPushButton::clicked, this, &MainWindow::onApplyOptionsClicked);
    connect(ui->cancelOptionsButton, &QPushButton::clicked, ui->optionsPanel, &QWidget::hide);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onGreyscaleClicked); 
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onBlackAndWhiteClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::onInvertClicked); 
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onFrameFilterClicked);
    connect(ui->FlipButton, &QPushButton::clicked, this, &MainWindow::onFlipFilterClicked);
    connect(ui->RotateButton, &QPushButton::clicked, this, &MainWindow::onRotateFilterClicked);
    connect(ui->DarkenLightenButton, &QPushButton::clicked, this, &MainWindow::onDarkenAndLightenClicked);
    connect(ui->DetectButton, &QPushButton::clicked, this, &MainWindow::onDetectEdgesClicked);
    connect(ui->SunlightButton, &QPushButton::clicked, this, &MainWindow::onSunlightClicked);
    connect(ui->PurpleButton, &QPushButton::clicked, this, &MainWindow::onPurpleFilterClicked);
    connect(ui->OilpaintingButton, &QPushButton::clicked, this, &MainWindow::onOilPaintingClicked);
    connect(ui->OldTvButton, &QPushButton::clicked, this, &MainWindow::onOldTvClicked);
    connect(ui->CropButton, &QPushButton::clicked, this, &MainWindow::onCropFilterClicked);
    connect(ui->SkewButton, &QPushButton::clicked, this, &MainWindow::onSkewFilterClicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::onResizeFilterClicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::onBlurFilterClicked);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &MainWindow::onInfraredFilterClicked);
    connect(ui->pushButton_10,&QPushButton::clicked, this, &MainWindow::onMergeClicked);
    const QList<QPushButton *> roundButtons ={ ui->ResetButton , ui->UndoButton, ui->RedoButton};
    for (QPushButton *b : roundButtons){
        b->setText("");
        b->setFixedSize(48,48);
        b->setIconSize(QSize(24,24));
        b->setProperty("round", true);
        b->setCursor(Qt::PointingHandCursor);
    }
    ui->ResetButton->setToolTip("Reset to original");
    ui->UndoButton->setToolTip("Undo");
    ui->RedoButton->setToolTip("Redo");

    applyTheme();
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
    originalImage = currentImage;
    imageHistory.clear(); 
    redoHistory.clear();
    updateImageDisplay();
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
static void showScaled(QLabel *label, const QImage &img)
{
    label->setAlignment(Qt::AlignCenter);
    QSize area = label->size() - QSize(16, 16);
    label->setPixmap(QPixmap::fromImage(img).scaled(area, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWindow::updateImageDisplay() {
    if (originalImage.isNull()) return;
    showScaled(ui->before, originalImage);
}

void MainWindow::saveStateForUndo(){
    imageHistory.append(currentImage);
    if (imageHistory.size() > 20) {
        imageHistory.removeFirst(); 
    }
    redoHistory.clear();
}
void MainWindow::onUndoClicked() {
    if (imageHistory.isEmpty()) {
        QMessageBox::information(this, "Undo", "Nothing to undo.");
        return;
    }
    redoHistory.append(currentImage);
    currentImage = imageHistory.takeLast();
    updateProcessedImage(currentImage);
}
void MainWindow::onRedoClicked(){
    if (redoHistory.isEmpty()){
        QMessageBox::information(this, "Redo","Nothing to redo");
        return;
    }
    imageHistory.append(currentImage);
    currentImage = redoHistory.takeLast();
    updateProcessedImage(currentImage);
}
void MainWindow::onResetClicked(){
    if(!hasImage()) return;
    saveStateForUndo();
    currentImage = originalImage;
    updateProcessedImage(currentImage);
}
void MainWindow::onThemeToggleClicked() {
    isDarkMode = !isDarkMode;
    applyTheme();
}
static void applyShadow(QWidget *w, const QColor &color)
{
    auto *shadow = new QGraphicsDropShadowEffect(w);
    shadow->setBlurRadius(25); 
    shadow->setOffset(0, 4);
    shadow->setColor(color);
    w->setGraphicsEffect(shadow);  
}
void MainWindow::applyTheme(){
    QString dark = R"(
    QMainWindow, QWidget#centralwidget {background-color: #12121b ;}
    QLabel{color: #F7F0F0}
    QPushButton{
        background-color: #5f5f72;
        color: #c1cbeb;
        border: 2px solid #415a84 ;
        border-radius: 8px;
        padding: 6px; 
        font-weight: bold;
    }
    QPushButton:hover{background-color: #45475a;}
    QPushButton:pressed {background-color: #8db2e3;  color: #1e1e2e; }
    QScrollArea{ background-color: #292935; border: none;}
    QWidget#scrollAreaWidgetContents_2{background-color: #1c1c28;}
    QLabel#before , QLabel#after {
        border: 2px solid #2a3c5c;
        border-radius: 10px;
        padding : 6px;
    }
    QPushButton[primary="true"]{
        background-color: #3b5684;
        color: #ffffff;
        border: none;
        border-radius: 10px;
        padding: 8px 18px;
        font-weight: bold;
    }
    QPushButton[primary="true"]:hover { background-color: #486ca1; }
    QPushButton[primary="true"]:pressed { background-color: #213f67; color: #1e1e2e; }
    QPushButton[primary="true"]:disabled { background-color: #2a2a3a; color: #777; }

    QRadioButton::indicator { width: 16px; height: 16px; border-radius: 9px; border: 2px solid #415a84; background: #1c1c28; }
    QRadioButton::indicator:checked { background: #8db2e3; }
    )";

    QString light = R"(
    QMainWindow, QWidget#centralwidget {background-color: #e8e4eb ;}
    QLabel{color: #484444}
    QPushButton{
        background-color: #e2dff1;
        color: #1c1c1e;
        border: 2px solid #d6d6f2 ;
        border-radius: 8px;
        padding: 6px; 
        font-weight: bold;
    }
    QPushButton:hover{background-color: #bfc2c9;}
    QPushButton:pressed {background-color: #8d939b;  color: #fcfcff; }
    QScrollArea{ background-color: #d0ccd3; border: none;}
    QWidget#scrollAreaWidgetContents_2{background-color: #dbdbe6;}
    QLabel#before, QLabel#after {
        border: 2px solid #b4b4dc;
        border-radius: 10px;
        padding: 6px;
    }
    QPushButton[primary="true"] {
    background-color: #645f98;
    color: #ffffff;
    border: none;
    border-radius: 10px;
    padding: 8px 18px;
    font-weight: bold;
    }
    QPushButton[primary="true"]:hover { background-color: #8985bf; }
    QPushButton[primary="true"]:pressed { background-color: #7874b2; }
    QPushButton[primary="true"]:disabled { background-color: #c9c6e0; color: #888; }

    QRadioButton::indicator { width: 16px; height: 16px; border-radius: 9px; border: 2px solid #726f91; background: #ffffff; }
    QRadioButton::indicator:checked { background: #87859c; }
     QRadioButton { color: #000000; spacing: 8px; }
    )";

    setStyleSheet(isDarkMode ? dark : light);
    ui->ThemeButton->setText(isDarkMode ? "\u2600 Light Mode" : "\u263E Dark Mode");
    
    QString s = isDarkMode ? "" : "_dark";
    ui->ResetButton->setIcon(QIcon(":/icons/reset" + s + ".svg"));
    ui->UndoButton->setIcon(QIcon(":/icons/undo" + s + ".svg"));
    ui->RedoButton->setIcon(QIcon(":/icons/redo" + s + ".svg"));

    QColor shadowColor = isDarkMode ? QColor(65, 90, 132, 150) : QColor(0, 0, 0, 90);      
    applyShadow(ui->before, shadowColor);
    applyShadow(ui->after,  shadowColor);
}

void MainWindow::updateProcessedImage(const QImage &img) {
    currentImage = img;
     showScaled(ui->after, img);
}
int MainWindow::getSliderValue(const QString &title, const QString &label,int minval, int maxval, int defval, bool &ok){
    QDialog dialog(this);
    dialog.setWindowTitle(title);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(new QLabel(label, &dialog));

    QSlider *slider = new QSlider(Qt::Horizontal, &dialog);
    slider->setRange(minval , maxval);
    slider->setValue(defval);

    QLabel *valueLabel = new QLabel(QString::number(defval) , &dialog);
    valueLabel->setMinimumWidth(35);
    valueLabel->setAlignment(Qt::AlignCenter);
    connect(slider, &QSlider::valueChanged, valueLabel, [valueLabel](int v) { valueLabel->setText(QString::number(v)); });
    QHBoxLayout *row = new QHBoxLayout;
    row->addWidget(slider);
    row->addWidget(valueLabel);
    layout->addLayout(row);

    QDialogButtonBox *buttons = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.setMinimumWidth(300);
    ok = (dialog.exec() == QDialog::Accepted);
    return slider->value();
}
static QImage rotateImage(const QImage &src, int angle)
{
    const int w = src.width(), h = src.height();
    if (angle == 90) {
        QImage out(h, w, src.format());
        for (int y = 0; y < h; ++y) {
            const QRgb *line = reinterpret_cast<const QRgb *>(src.constScanLine(y));
            for (int x = 0; x < w; ++x)
                reinterpret_cast<QRgb *>(out.scanLine(x))[h - 1 - y] = line[x];
        }
        return out;
    }
    if (angle == 270) {
        QImage out(h, w, src.format());
        for (int y = 0; y < h; ++y) {
            const QRgb *line = reinterpret_cast<const QRgb *>(src.constScanLine(y));
            for (int x = 0; x < w; ++x)
                reinterpret_cast<QRgb *>(out.scanLine(w - 1 - x))[y] = line[x];
        }
        return out;
    }
    QImage out(w, h, src.format());   // 180
    for (int y = 0; y < h; ++y) {
        const QRgb *line = reinterpret_cast<const QRgb *>(src.constScanLine(y));
        QRgb *dst = reinterpret_cast<QRgb *>(out.scanLine(h - 1 - y));
        for (int x = 0; x < w; ++x)
            dst[w - 1 - x] = line[x];
    }
    return out;
}

void MainWindow::applyFlip() {
    const int w = currentImage.width(), h = currentImage.height();
    const bool horizontal = ui->radioH->isChecked() || ui->radioBoth->isChecked();
    const bool vertical   = ui->radioV->isChecked() || ui->radioBoth->isChecked();

    if (horizontal)
        for (int y = 0; y < h; ++y) {
            QRgb *line = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
            for (int x = 0; x < w / 2; ++x)
                std::swap(line[x], line[w - 1 - x]);
        }
    if (vertical)
        for (int y = 0; y < h / 2; ++y) {
            QRgb *top    = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
            QRgb *bottom = reinterpret_cast<QRgb *>(currentImage.scanLine(h - 1 - y));
            for (int x = 0; x < w; ++x)
                std::swap(top[x], bottom[x]);
        }
}

void MainWindow::applyRotate() {
    int angle = ui->radio90->isChecked()  ? 90
              : ui->radio270->isChecked() ? 270
              : 180;
    currentImage = rotateImage(currentImage, angle);
}

void MainWindow::onApplyOptionsClicked() {
    saveStateForUndo();
    QWidget *page = ui->optionsStack->currentWidget();

    if (page == ui->FlipPage)  applyFlip();
    else if (page == ui->RotatePage) applyRotate();

    updateProcessedImage(currentImage);
    ui->optionsPanel->hide();
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

    bool okType;
    int type = QInputDialog::getInt(this, tr("Frame Type"), tr("Choose Frame Type:\n1. Simple Frame\n2. Fancy Frame"),    1, 1, 2, 1, &okType);
    if (!okType) return; 

    bool okColor;
    int colorchoice = QInputDialog::getInt(this, tr("Frame Color"), tr("Choose Color Choice:\n1. White\n2. Black\n3. Red\n4. Green\n5. Blue"),    1, 1, 5, 1, &okColor);
    if (!okColor) return;  
    saveStateForUndo();

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
void MainWindow::onFlipFilterClicked() {
    if (!hasImage()) return;
    ui->optionsStack->setCurrentWidget(ui->FlipPage);
    ui->optionsPanel->show();
}

void MainWindow::onRotateFilterClicked() {
    if (!hasImage()) return;
    ui->optionsStack->setCurrentWidget(ui->RotatePage);
    ui->optionsPanel->show();
}

void MainWindow::onResizeFilterClicked() {
    if (!hasImage()) return;
    QDialog dialog(this);
    dialog.setWindowTitle("Resize");
    QFormLayout *form = new QFormLayout(&dialog);
    form->addRow(new QLabel("Orignal Size: " + QString::number(currentImage.width()) + " x " + QString::number(currentImage.height())));

    QSpinBox *widthBox = new QSpinBox(&dialog);
    widthBox->setRange(1,1000000);
    widthBox->setSingleStep(10);
    widthBox->setValue(currentImage.width());

    QSpinBox *heightBox = new QSpinBox(&dialog);
    heightBox->setRange(1,1000000);
    heightBox->setSingleStep(10);
    heightBox->setValue(currentImage.height());

    form->addRow("Width: ", widthBox);
    form->addRow("Height: ", heightBox);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form->addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec()!= QDialog::Accepted)return;
    int new_width = widthBox->value();
    int new_height = heightBox->value();

    saveStateForUndo();

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
    bool ok;
    int radius = getSliderValue("Blur filter", "Blur Intensity: ", 1, 10, 2, ok);
    if (!ok) return;
    saveStateForUndo();

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
void MainWindow::onDarkenAndLightenClicked() {
    if (!hasImage()) return;
    bool ok;
    int value = getSliderValue("Darken & Lighten", "Brightness (-100 = darker, +100 = lighter): ", -100, 100, 0, ok);
    if (!ok || value == 0) return;
    saveStateForUndo();

    const double factor = 1.0 + value / 100.0;   // -50 -> x0.5 , +50 -> x1.5

    for (int y = 0; y < currentImage.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
        for (int x = 0; x < currentImage.width(); ++x) {
            int r = std::min(255, int(qRed(line[x])   * factor));
            int g = std::min(255, int(qGreen(line[x]) * factor));
            int b = std::min(255, int(qBlue(line[x])  * factor));
            line[x] = qRgba(r, g, b, qAlpha(line[x]));
        }
    }
    updateProcessedImage(currentImage);
}
void MainWindow::onDetectEdgesClicked() {
    if (!hasImage()) return;
    const int threshold = 100;
    saveStateForUndo();
    const int w = currentImage.width();
    const int h = currentImage.height();
    QVector<int> gray(w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            QRgb p = currentImage.pixel(x, y);
            gray[y * w + x] = (qRed(p) + qGreen(p) + qBlue(p)) / 3;
        }
    }
    static const int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    static const int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    QImage result(w, h, QImage::Format_ARGB32);
    result.fill(Qt::white);
    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            int sumx = 0, sumy = 0;
            for (int a = -1; a <= 1; ++a) {
                for (int b = -1; b <= 1; ++b) {
                    int px = gray[(y + a) * w + (x + b)];
                    sumx += px * gx[a + 1][b + 1];
                    sumy += px * gy[a + 1][b + 1];
                }
            }
            int value = (qAbs(sumx) + qAbs(sumy) > threshold) ? 0 : 255;
            result.setPixel(x, y, qRgb(value, value, value));
        }
    }
    currentImage = result;
    updateProcessedImage(currentImage);
}
void MainWindow::onSunlightClicked() {
    if (!hasImage()) return;
    saveStateForUndo();
    for (int y = 0; y < currentImage.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
        for (int x = 0; x < currentImage.width(); ++x) {
            int red   = std::min(255, int(qRed(line[x])   * 1.25 + 20));
            int green = std::min(255, int(qGreen(line[x]) * 1.20 + 15));
            int blue  = std::max(0,   int(qBlue(line[x])  * 0.8));
            line[x] = qRgba(red, green, blue, qAlpha(line[x]));
        }
    }
    updateProcessedImage(currentImage);
}
void MainWindow::onPurpleFilterClicked() {
    if (!hasImage()) return;
    bool ok;
    int strength = getSliderValue("Purple filter", "Purple Intensity:", 1, 100, 30, ok);
    if(!ok) return;
    saveStateForUndo();

    for (int y = 0; y < currentImage.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
        for (int x = 0; x < currentImage.width(); ++x) {
            int red   = qRed(line[x]);
            int green = qGreen(line[x]);
            int blue  = qBlue(line[x]);

            int newRed   = std::min((red * strength) / 100 + red, 255);
            int newGreen = std::max(green - (green * strength) / 100, 0);
            int newBlue  = std::min((blue * strength) / 100 + blue, 255);

            line[x] = qRgba(newRed, newGreen, newBlue, qAlpha(line[x]));
        }
    }
    updateProcessedImage(currentImage);
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


void MainWindow::onRotateClicked() {
    if (!hasImage()) return;

    bool ok;
    int angle = getSliderValue("Rotate", "Angle: ", 0, 360, 90, ok);
    if (!ok) return;

    saveStateForUndo();

    currentImage = currentImage.transformed(QTransform().rotate(angle));
    updateProcessedImage(currentImage);
}

void MainWindow::onMergeClicked() {
    if (!hasImage()) return;

    QString path = QFileDialog::getOpenFileName(this, "Choose second image", "",  "Images (*.png *.jpg *.jpeg *.bmp)");
    if (path.isEmpty()) return;

    QImage image2;
    if (!image2.load(path)) return;

    QImage image1 = currentImage;

    image1 = image1.convertToFormat(QImage::Format_RGB32);
    image2 = image2.convertToFormat(QImage::Format_RGB32);

    int w1 = image1.width(),  h1 = image1.height();
    int w2 = image2.width(),  h2 = image2.height();

    int W, H, mode = 0;

    if (w1 == w2 && h1 == h2) {
        W = w1;  H = h1;
    }
    else {
        QStringList options;
        options << "Resize to the biggest" << "Crop to the smallest";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Merge", "Images have different sizes:",  options, 0, false, &ok);
        if (!ok) return;

        if (choice == options[0]) {
            mode = 1;
            W = std::max(w1, w2);
            H = std::max(h1, h2);
        } else {
            mode = 2;
            W = std::min(w1, w2);
            H = std::min(h1, h2);
        }
    }

    saveStateForUndo();

    QImage outputImage(W, H, QImage::Format_RGB32);

    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            int i1, j1, i2, j2;

            if (mode == 2) {
                i1 = i + (w1 - W) / 2;
                j1 = j + (h1 - H) / 2;
                i2 = i + (w2 - W) / 2;
                j2 = j + (h2 - H) / 2;
            } else {
                i1 = i * w1 / W;
                j1 = j * h1 / H;
                i2 = i * w2 / W;
                j2 = j * h2 / H;
            }

            QRgb p1 = image1.pixel(i1, j1);
            QRgb p2 = image2.pixel(i2, j2);

            int r = (qRed(p1)   + qRed(p2))   / 2;
            int g = (qGreen(p1) + qGreen(p2)) / 2;
            int b = (qBlue(p1)  + qBlue(p2))  / 2;

            outputImage.setPixel(i, j, qRgb(r, g, b));
        }
    }

    currentImage = outputImage;
    updateProcessedImage(currentImage);
}
void MainWindow::onOilPaintingClicked() {
    if (!hasImage()) return;
    bool ok;
    int radius = getSliderValue("Oil painting", "Brush Size: ", 1, 10, 3, ok);
    if (!ok) return;
    saveStateForUndo();

    const int levels = 20;
    const int w = currentImage.width();
    const int h = currentImage.height();
    QImage source = currentImage;
    QImage result = currentImage;

    for (int y = 0; y < h; ++y) {
        QRgb *dst = reinterpret_cast<QRgb *>(result.scanLine(y));
        for (int x = 0; x < w; ++x) {
            int count[levels]  = {0};
            int sumR[levels]   = {0};
            int sumG[levels]   = {0};
            int sumB[levels]   = {0};

            for (int dy = -radius; dy <= radius; ++dy) {
                int ny = y + dy;
                if (ny < 0 || ny >= h) continue;
                const QRgb *src = reinterpret_cast<const QRgb *>(source.constScanLine(ny));
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    if (nx < 0 || nx >= w) continue;

                    int r = qRed(src[nx]);
                    int g = qGreen(src[nx]);
                    int b = qBlue(src[nx]);
                    int level = ((r + g + b) / 3) * (levels - 1) / 255;

                    count[level]++;
                    sumR[level] += r;
                    sumG[level] += g;
                    sumB[level] += b;
                }
            }
            int best = 0;
            for (int i = 1; i < levels; ++i)
                if (count[i] > count[best]) best = i;

            dst[x] = qRgba(sumR[best] / count[best],
                           sumG[best] / count[best],
                           sumB[best] / count[best],
                           qAlpha(dst[x]));
        }
    }
    currentImage = result;
    updateProcessedImage(currentImage);
}
void MainWindow::onOldTvClicked() {
    if (!hasImage()) return;
    saveStateForUndo();

    const int shift = 5,noiseAmount = 10, lineGap = 3;
    const float lineDarkness = 0.4f;
    const int w = currentImage.width();
    const int h = currentImage.height();
    auto clampPixel = [](int v) { return (v < 0) ? 0 : (v > 255) ? 255 : v; };
    QImage source = currentImage;
    QImage result = currentImage;

    for (int j = 0; j < h; ++j) {
        int glitch = 0;
        if (rand() % 20 == 0) glitch = (rand() % 20) - 10;
        float lineFactor = (j % lineGap == 0) ? lineDarkness : 1.0f;

        const QRgb *src = reinterpret_cast<const QRgb *>(source.constScanLine(j));
        QRgb *dst = reinterpret_cast<QRgb *>(result.scanLine(j));

        for (int i = 0; i < w; ++i) {
            int noise = (rand() % (2 * noiseAmount + 1)) - noiseAmount;
            int channels[3];

            for (int k = 0; k < 3; ++k) {
                int shifted_i = i + glitch;
                if (k == 0) shifted_i += shift;
                else if (k == 2) shifted_i -= shift;
                shifted_i = std::max(std::min(shifted_i, w - 1), 0);
                int value = (k == 0) ? qRed(src[shifted_i]) : (k == 1) ? qGreen(src[shifted_i]) : qBlue(src[shifted_i]);
                channels[k] = clampPixel(int(value * lineFactor + noise));
            }
            dst[i] = qRgba(channels[0], channels[1], channels[2], qAlpha(src[i]));
        }
    }
    currentImage = result;
    updateProcessedImage(currentImage);
}
void MainWindow::onCropFilterClicked() {
    if (!hasImage()) return;

    const int imgW = currentImage.width();
    const int imgH = currentImage.height();

    QDialog dialog(this);
    dialog.setWindowTitle("Crop");
    QFormLayout *form = new QFormLayout(&dialog);
    form->addRow(new QLabel("Original Size: " + QString::number(imgW) + " x " + QString::number(imgH)));

    QSpinBox *xBox = new QSpinBox(&dialog);
    xBox->setRange(0, imgW - 1);
    QSpinBox *yBox = new QSpinBox(&dialog);
    yBox->setRange(0, imgH - 1);

    QSpinBox *widthBox = new QSpinBox(&dialog);
    widthBox->setRange(1, imgW);
    widthBox->setValue(imgW);
    QSpinBox *heightBox = new QSpinBox(&dialog);
    heightBox->setRange(1, imgH);
    heightBox->setValue(imgH);
    connect(xBox, QOverload<int>::of(&QSpinBox::valueChanged), widthBox,
            [=](int x) { widthBox->setMaximum(imgW - x); });
    connect(yBox, QOverload<int>::of(&QSpinBox::valueChanged), heightBox,
            [=](int y) { heightBox->setMaximum(imgH - y); });

    form->addRow("X: ", xBox);
    form->addRow("Y: ", yBox);
    form->addRow("Width: ", widthBox);
    form->addRow("Height: ", heightBox);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form->addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return;

    const int x = xBox->value();
    const int y = yBox->value();
    const int w = widthBox->value();
    const int h = heightBox->value();

    saveStateForUndo();
    QImage cropped(w, h, currentImage.format());
    for (int j = 0; j < h; ++j) {
        const QRgb *src = reinterpret_cast<const QRgb *>(currentImage.constScanLine(y + j));
        QRgb *dst = reinterpret_cast<QRgb *>(cropped.scanLine(j));
        for (int i = 0; i < w; ++i)
            dst[i] = src[x + i];
    }
    currentImage = cropped;
    updateProcessedImage(currentImage);
}
void MainWindow::onSkewFilterClicked() {
    if (!hasImage()) return;

    bool ok;
    int angle = getSliderValue("Skew", "Angle (degrees): ", -60, 60, 20, ok);
    if (!ok || angle == 0) return;
    saveStateForUndo();

    const int w = currentImage.width();
    const int h = currentImage.height();
    const double pi = 3.141592653589793;
    const double t = std::tan(std::abs(angle) * pi / 180.0);
    const int maxShift = static_cast<int>((h - 1) * t);

    QImage skewed(w + maxShift, h, QImage::Format_ARGB32);
    skewed.fill(Qt::transparent);

    for (int y = 0; y < h; ++y) {
        int shift = (angle > 0) ? static_cast<int>(y * t) : static_cast<int>((h - 1 - y) * t);

        const QRgb *src = reinterpret_cast<const QRgb *>(currentImage.constScanLine(y));
        QRgb *dst = reinterpret_cast<QRgb *>(skewed.scanLine(y));
        for (int x = 0; x < w; ++x)
            dst[x + shift] = src[x];
    }
    currentImage = skewed;
    updateProcessedImage(currentImage);
}