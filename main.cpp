#include "window.h"
#include "sphere.h"
#include "QTimer"
#include <QApplication>
#include <QVBoxLayout>
#include "QPushButton"
#include "control.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

#ifdef VECTORS
    QWidget window;
    window.resize(1200, 1200);
    Window_Clock w2({100, 100}, {400, 400}, {250, 250});
    w2.set_radius(80);
    Window_Click w1({100, 100}, {400, 400}, {250, 250});

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(&w2);
    layout->addWidget(&w1);

    window.setLayout(layout);
    window.show();
#endif

#ifdef ONLY_SPHERE

    Window_Sphere w(1920, 1080);
    w.add_sphere(300, 20, {0, 0, 0}, {0.6, 0.2, 0.45}, 1);
    w.add_lamp({400, 200, 500}, {0.9, 0.7, 0.3});
    //w.set_lamp_point({400, 200, 500});
    w.set_viewer_point({400, 200, 500});
    //w.set_color_material ({0.6, 0.2, 0.45});
    w.resize(1920, 1080);
    w.show();

#endif


#ifdef RACING

    Window_Sphere w(1920, 1080, {0, 1080/2, 0});
    //Window_Sphere w(1920, 1080, 300 , 20);

    w.add_lamp({1920/2 - 500 - 300, 10000, 1000000}, {0.5, 0.5, 0.4});
    //w.add_lamp({300, -100, 200}, {0.5, 0.2, 0.4});
    //w.add_lamp({1700, 300, 200}, {0.2, 0.3, 0.9});
    //w.add_lamp({1920/2 + 4, 1080/2, 200}, {0.2, 0.9, 0.1});
    w.add_sphere(200, 20, {500, 400, 400}, {0.2, 0.5, 0.35}, 1);
    //w.add_sphere(200, 20, {1920/2 + 500, 0, 400}, {0.2, 0.4, 0.65}, 1);
    w.add_sphere(200, 20, {1920/2, 0, 400}, {0.2, 0.4, 0.65}, 1);
    //w.add_sphere(300, 20, {1760, 400, 400}, {0.3, 0.1, 0.15}, 1);
    w.set_max_num_reflection(4);
    w.set_viewer_point({1920/2, 1000, -100000});
    w.resize(1920, 1080);
    w.show();

#endif
    return a.exec();
}
