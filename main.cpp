#include "qapplication.h"
#include "widget.h"
#include "button.h"
#include "tool.h"
#include "texteditor.h"
#include <QTimerEvent>

int make_photoshop(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetManager main_widget ({0, 0, 0}, {1920, 1080}, NULL, StandardWidgetPaint);
    WidgetManager paint_widget ({200, 110, 0}, {1700, 600}, &main_widget, controller_paint, StandardWidgetPaint);
    WidgetManager palette_widget ({200, 800}, {1000, 1000}, &main_widget, controller_paint, StandardWidgetPaint);
    WidgetManager tool_properties ({200, 50}, {1700, 110}, &main_widget, controller_paint, StandardWidgetPaint);
    //paint_widget.resize(100, 100);
    fprintf (stderr, "%p\n", &main_widget);

    Button pen_button ({200, 800}, {400, 1000}, button_with_instrument, ButtonPaintFromPicture);
    pen_button.set_image_path(":/stream/pencil.png");
    Button line_button ({400, 800}, {600, 1000}, button_with_instrument, ButtonPaintFromPicture);
    line_button.set_image_path(":/stream/line.jpg");
    Button eraser_button ({600, 800}, {800, 1000}, button_with_instrument, ButtonPaintFromPicture);
    eraser_button.set_image_path(":/stream/eraser.jpg");

/*Add tools*/
    Tool cist {paint_dot};
    Tool line {paint_line};
    Tool eraser {clear_dot};

/*Add colors properties*/
    Button red_color_button ({250, 50}, {300, 70}, button_change_color_tool, StandardButtonPaint);
    WidgetManager red_color ({200, 50}, {300, 70}, &tool_properties, controller_paint, StandardWidgetPaint);
    TextEditor red_color_editor ({200, 50}, {250, 70}, &red_color, controller_text_editor, StandardTextEditorPaint, InfoType::RedColor);
    red_color_editor.set_timer(1000);
    red_color_editor.set_timer_controller(timer_controller_text_editor);
    red_color_editor.last_activity_ = last_activity_text_editor;
    red_color.add_widget(&red_color_editor);
    red_color.add_button(&red_color_button);
    red_color_button.set_color({1, 0, 0});
    tool_properties.add_widget(&red_color);

    Button green_color_button ({250, 70}, {300, 90}, button_change_color_tool, StandardButtonPaint);
    WidgetManager green_color ({200, 70}, {300, 90}, &tool_properties, controller_paint, StandardWidgetPaint);
    TextEditor green_color_editor ({200, 70}, {250, 90}, &green_color, controller_text_editor, StandardTextEditorPaint, InfoType::GreenColor);
    green_color_editor.set_timer_controller(timer_controller_text_editor);
    green_color_editor.last_activity_ = last_activity_text_editor;
    green_color_editor.set_timer(1000);
    green_color.add_widget(&green_color_editor);
    green_color.add_button(&green_color_button);
    green_color_button.set_color({0, 1, 0});
    tool_properties.add_widget(&green_color);

    Button blue_color_button ({250, 90}, {300, 110}, button_change_color_tool, StandardButtonPaint);
    WidgetManager blue_color ({200, 90}, {300, 110}, &tool_properties, controller_paint, StandardWidgetPaint);
    TextEditor blue_color_editor ({200, 90}, {250, 110}, &blue_color, controller_text_editor, StandardTextEditorPaint, InfoType::BlueColor);
    blue_color_editor.set_timer(1000);
    blue_color_editor.set_timer_controller(timer_controller_text_editor);
    blue_color_editor.last_activity_ = last_activity_text_editor;
    blue_color.add_widget(&blue_color_editor);
    blue_color.add_button(&blue_color_button);
    blue_color_button.set_color({0, 0, 1});
    tool_properties.add_widget(&blue_color);

    WidgetManager line_width ({300, 50}, {400, 110}, &tool_properties, controller_paint, StandardWidgetPaint);
    Button line_width_button ({300, 50}, {400, 90}, button_change_thickness, ButtonPaintFromPicture);
    line_width_button.set_image_path(":/stream/thickness.png");
    TextEditor line_width_editor ({300, 90}, {400, 110}, &line_width, controller_text_editor, StandardTextEditorPaint, InfoType::Thickness);
    line_width_editor.set_timer_controller(timer_controller_text_editor);
    line_width_editor.last_activity_ = last_activity_text_editor;
    line_width_editor.set_timer(1000);
    line_width.add_widget(&line_width_editor);
    line_width.add_button(&line_width_button);
    tool_properties.add_widget(&line_width);

    ToolManager tools {};
    tools.add_tool(&cist);
    tools.add_tool(&line);
    tools.add_tool(&eraser);
    pen_button.set_tool(&cist);
    line_button.set_tool(&line);
    eraser_button.set_tool(&eraser);

    main_widget.add_widget(&paint_widget);
    main_widget.add_widget(&palette_widget);
    main_widget.add_widget(&tool_properties);

    paint_widget.set_tool_manager(&tools);
    palette_widget.add_button(&line_button);
    palette_widget.add_button(&pen_button);
    palette_widget.add_button(&eraser_button);

    main_widget.resize_widget(1920, 1080);
    main_widget.show_widget();

    return a.exec();

}

int main(int argc, char *argv[])
{
    return make_photoshop(argc, argv);
}
