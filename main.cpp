#include "qapplication.h"
#include "widget.h"
#include "button.h"
#include "tool.h"
#include "texteditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetManager main_widget ({0, 0, 0}, {1920, 1080}, NULL, StandartWidgetPaint);
    WidgetManager paint_widget ({200, 100, 0}, {1700, 600}, &main_widget, controller_paint, StandartWidgetPaint);
    WidgetManager palette_widget ({200, 800}, {1000, 1000}, &main_widget, controller_paint, StandartWidgetPaint);
    WidgetManager tool_properties ({200, 50}, {1700, 100}, &main_widget, controller_paint, StandartWidgetPaint);
    //paint_widget.resize(100, 100);
    fprintf (stderr, "%p\n", &paint_widget);

    Button pen_button ({200, 800}, {400, 1000}, button_with_instrument, ButtonPaintFromPicture);
    pen_button.set_image_path(":/stream/pencil.png");
    Button line_button ({500, 800}, {700, 1000}, button_with_instrument, ButtonPaintFromPicture);
    line_button.set_image_path(":/stream/line.jpg");
    Button third_button ({800, 800}, {1000, 1000}, button_with_instrument, ButtonPaintFromPicture);

    Button red_color_button ({250, 50}, {300, 70}, button_change_color_tool, StandartButtonPaint);
    WidgetManager red_color ({200, 50}, {300, 70}, &tool_properties, controller_paint, StandartWidgetPaint);
    TextEditor red_color_editor ({200, 50}, {250, 70}, &red_color, NULL, StandartTextEditorPaint);
    red_color.add_text_editor(&red_color_editor);
    red_color.add_button(&red_color_button);
    red_color_button.set_color({1, 0, 0});
    tool_properties.add_widget(&red_color);

    Tool cist {paint_dot};
    Tool line {paint_line};
    ToolManager tools {};
    tools.add_tool(&cist);
    tools.add_tool(&line);
    pen_button.set_tool(&cist);
    line_button.set_tool(&line);

    main_widget.add_widget(&paint_widget);
    main_widget.add_widget(&palette_widget);
    main_widget.add_widget(&tool_properties);

    paint_widget.set_tool_manager(&tools);
    palette_widget.add_button(&line_button);
    palette_widget.add_button(&pen_button);
    palette_widget.add_button(&third_button);


    main_widget.resize_widget(1920, 1080);
    /*QLineEdit lin;
    lin.setFrame(false);
    lin.setText("hui");
    lin.show();*/
    main_widget.show_widget();

    return a.exec();

}
