#include "qapplication.h"
#include "widget.h"
#include "button.h"
#include "tool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetManager main_widget ({0, 0, 0}, {1920, 1080}, MainWidget, StandartPaint);
    WidgetManager paint_widget ({200, 50, 0}, {1700, 500}, PaintWidget, controller_paint, StandartPaint);
    //paint_widget.resize(100, 100);
    fprintf (stderr, "%p\n", &paint_widget);

    Button first_button ({200, 800}, {400, 1000}, button_with_instrument);
    Button second_button ({500, 800}, {700, 1000}, button_with_instrument);
    Button third_button ({800, 800}, {1000, 1000}, button_with_instrument);

    Tool cist {paint_dot};
    ToolManager tools {};
    tools.add_tool(&cist);
    first_button.set_tool(&cist);

    main_widget.add_widget(&paint_widget);
    paint_widget.set_tool_manager(&tools);
    paint_widget.add_button(&first_button);
    paint_widget.add_button(&second_button);
    paint_widget.add_button(&third_button);

    main_widget.resize(1920, 1080);
    //txCreateWindow (800, 600);
    //txLine (320, 290, 320, 220);

    main_widget.show();

    return a.exec();

}
