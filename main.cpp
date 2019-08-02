#include <QApplication>
#include "camera/camerawindow.h"
#include "camera/cameraform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    CameraWindow w;
    CameraForm w;
    w.show();

    return a.exec();
}
