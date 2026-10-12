#include "mainwindow.h"
#include "./ui_mainwindow.h"
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

    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::onResizeFilterClicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::onBlurFilterClicked);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &MainWindow::onInfraredFilterClicked);
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

void MainWindow::updateImageDisplay() {
    if (originalImage.isNull())
        return;
    ui->before->setAlignment(Qt::AlignCenter);
    ui->before->setPixmap(QPixmap::fromImage(originalImage).scaled( ui->before->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QSize area = ui->before->size() - QSize(16, 16);
    ui->before->setPixmap(QPixmap::fromImage(originalImage).scaled(area, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
    ui->after->setPixmap(QPixmap::fromImage(img).scaled(ui->after->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
void MainWindow::onFlipFilterClicked(){
    if (!hasImage()) return;
    ui->optionsStack->setCurrentWidget(ui->FlipPage);
    ui->optionsPanel->show();
    QStringList options ={"Horizontal (left <-> right)" , "Vertical (top <-> bottom) " , "Both"};
    bool ok;
    QString choice = QInputDialog::getItem(this,"Flip", "Choose flip direction: " , options , 0, false, &ok);
    if(!ok) return;
    saveStateForUndo();

    const int w = currentImage.width();
    const int h = currentImage.height();
    const bool horizontal = (choice == options[0] || choice == options[2]);
    const bool vertical   = (choice == options[1] || choice == options[2]);

    if (horizontal){
        for (int y=0 ; y < h ; y++){
            QRgb *line = reinterpret_cast<QRgb*> (currentImage.scanLine(y));
            for (int x=0 ; x < w /2 ; x++) {
                std::swap(line[x], line[w -1 -x]);
            }
        }
    }
    if (vertical) {
        for (int y = 0; y < h / 2; ++y) {
            QRgb *top    = reinterpret_cast<QRgb *>(currentImage.scanLine(y));
            QRgb *bottom = reinterpret_cast<QRgb *>(currentImage.scanLine(h - 1 - y));
            for (int x = 0; x < w; ++x){
                std::swap(top[x], bottom[x]);
            }
        }
    }
    updateProcessedImage(currentImage);
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