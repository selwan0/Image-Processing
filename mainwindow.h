#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include<QIcon>
#include<QSize>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadImageClicked();
    void onSaveImageClicked();
    void onUndoClicked();
    void onGreyscaleClicked();
    void onBlackAndWhiteClicked();
    void onInvertClicked();
    void onFrameFilterClicked();
    void onResizeFilterClicked();
    void onBlurFilterClicked();
    void onInfraredFilterClicked();
    void updateProcessedImage(const QImage &img);
    

private:
    Ui::MainWindow *ui;
    QImage currentImage;
    QList<QImage> imageHistory; 
    void saveStateForUndo();
    void updateImageDisplay();
    bool hasImage();
};

#endif