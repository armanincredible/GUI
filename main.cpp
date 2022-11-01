#include "qapplication.h"
#include "widget.h"
#include "button.h"
#include "tool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetManager main_widget ({0, 0, 0}, {1920, 1080});

    main_widget.resize(1920, 1080);

    main_widget.show();

    return a.exec();
}
