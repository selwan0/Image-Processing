/*Header:
Student Name:Selwan Ayman Mustafa     Student ID: 20250292    Filters: greyscale, flip , Merge , sunlight
Student Name:Sama Ahmed Ibrahim       Student ID: 20250294    Filters: black and white, rotate ,detect image , old TV  
Student Name:Kenzi Ali Nosier         Student ID: 20250499    Filters: invert, darken and lighten , crop image , purple
Student Name:Nada Mohamed Refaat      Student ID: 20250704    Filters: frame, resize , blur , infrared
Repo & Menu & GUI & BONUS FILTERS 17,18 are common between all members
Section: S40 [all team]
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName("SaNaD Palettes");
    MainWindow w;
    w.show();
    return a.exec();
}