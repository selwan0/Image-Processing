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
    void onRedoClicked();
    void onResetClicked();
    void onThemeToggleClicked();
    void onApplyOptionsClicked();
    void onRotateFilterClicked();
    void onGreyscaleClicked();
    void onBlackAndWhiteClicked();
    void onInvertClicked();
    void onFrameFilterClicked();
    void onFlipFilterClicked();
    void onResizeFilterClicked();
    void onBlurFilterClicked();
    void onInfraredFilterClicked();
    void updateProcessedImage(const QImage &img);
    void onRotateClicked();
    void onMergeClicked();
    

private:
    Ui::MainWindow *ui;
    QImage currentImage;
    QList<QImage> imageHistory; 
    QList<QImage> redoHistory;
    void saveStateForUndo();
    void updateImageDisplay();
    void applyFlip();
    void applyRotate();
    bool hasImage();
    bool isDarkMode = false;
    void applyTheme();
    int getSliderValue(const QString &title, const QString &label, int minval, int maxval, int defval, bool &ok);
    QImage originalImage;
};

#endif