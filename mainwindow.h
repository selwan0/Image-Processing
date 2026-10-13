#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include<QIcon>
#include<QSize>
#include <QSlider>
#include <QSpinBox>

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
    void onDarkenAndLightenClicked();
    void onDetectEdgesClicked();
    void onSunlightClicked();
    void onPurpleFilterClicked();
    void onOilPaintingClicked();
    void onOldTvClicked();
    void onCropFilterClicked();
    void onSkewFilterClicked();
    


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

    enum class PendingFilter { None, Blur, Purple, Darken, Skew, OilPainting };
    PendingFilter pendingFilter = PendingFilter::None;

    QWidget *sliderPage = nullptr;
    QLabel  *sliderLabel = nullptr;
    QSlider *optionSlider = nullptr;
    QLabel  *sliderValueLabel = nullptr;

    void showSliderPanel(const QString &label, int minval, int maxval, int defval, PendingFilter f);
    void applyBlur(int radius);
    void applyDarkenLighten(int value);
    void applyPurple(int strength);
    void applySkew(int angle);
    void applyOilPainting(int radius);
    void applyResize();
    void applyCrop();

    
};

#endif