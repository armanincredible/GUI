#include "qapplication.h"
#include "widget.h"
#include "button.h"
#include "tool.h"
#include "texteditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetManager main_widget ({0, 0, 0}, {1920, 1080}, NULL, StandartWidgetPaint);
    WidgetManager paint_widget ({200, 110, 0}, {1700, 600}, &main_widget, controller_paint, StandartWidgetPaint);
    WidgetManager palette_widget ({200, 800}, {1000, 1000}, &main_widget, controller_paint, StandartWidgetPaint);
    WidgetManager tool_properties ({200, 50}, {1700, 110}, &main_widget, controller_paint, StandartWidgetPaint);
    //paint_widget.resize(100, 100);
    fprintf (stderr, "%p\n", &paint_widget);

    Button pen_button ({200, 800}, {400, 1000}, button_with_instrument, ButtonPaintFromPicture, ButtonTargetType::ChangeTool);
    pen_button.set_image_path(":/stream/pencil.png");
    Button line_button ({400, 800}, {600, 1000}, button_with_instrument, ButtonPaintFromPicture, ButtonTargetType::ChangeTool);
    line_button.set_image_path(":/stream/line.jpg");
    Button eraser_button ({600, 800}, {800, 1000}, button_with_instrument, ButtonPaintFromPicture, ButtonTargetType::ChangeTool);
    eraser_button.set_image_path(":/stream/eraser.jpg");

/*Add colors properties*/
    Button red_color_button ({250, 50}, {300, 70}, button_change_color_tool, StandartButtonPaint, ButtonTargetType::ChangeRedColor);
    WidgetManager red_color ({200, 50}, {300, 70}, &tool_properties, controller_paint, StandartWidgetPaint);
    TextEditor red_color_editor ({200, 50}, {250, 70}, &red_color, controller_text_editor, StandartTextEditorPaint, InfoType::RedColor);
    red_color.add_text_editor(&red_color_editor);
    red_color.add_button(&red_color_button);
    red_color_button.set_color({1, 0, 0});
    tool_properties.add_widget(&red_color);

    Button green_color_button ({250, 70}, {300, 90}, button_change_color_tool, StandartButtonPaint, ButtonTargetType::ChangeRedColor);
    WidgetManager green_color ({200, 70}, {300, 90}, &tool_properties, controller_paint, StandartWidgetPaint);
    TextEditor green_color_editor ({200, 70}, {250, 90}, &green_color, controller_text_editor, StandartTextEditorPaint, InfoType::GreenColor);
    green_color.add_text_editor(&green_color_editor);
    green_color.add_button(&green_color_button);
    green_color_button.set_color({0, 1, 0});
    tool_properties.add_widget(&green_color);

    Button blue_color_button ({250, 90}, {300, 110}, button_change_color_tool, StandartButtonPaint, ButtonTargetType::ChangeRedColor);
    WidgetManager blue_color ({200, 90}, {300, 110}, &tool_properties, controller_paint, StandartWidgetPaint);
    TextEditor blue_color_editor ({200, 90}, {250, 110}, &blue_color, controller_text_editor, StandartTextEditorPaint, InfoType::BlueColor);
    blue_color.add_text_editor(&blue_color_editor);
    blue_color.add_button(&blue_color_button);
    blue_color_button.set_color({0, 0, 1});
    tool_properties.add_widget(&blue_color);

    WidgetManager line_width ({300, 50}, {400, 110}, &tool_properties, controller_paint, StandartWidgetPaint);
    Button line_width_button ({300, 50}, {400, 90}, button_change_thickness, ButtonPaintFromPicture, ButtonTargetType::ChangeThickness);
    line_width_button.set_image_path(":/stream/thickness.png");
    TextEditor line_width_editor ({300, 90}, {400, 110}, &line_width, controller_text_editor, StandartTextEditorPaint, InfoType::Thickness);
    line_width.add_text_editor(&line_width_editor);
    line_width.add_button(&line_width_button);
    tool_properties.add_widget(&line_width);

    Tool cist {paint_dot};
    Tool line {paint_line};
    Tool eraser {clear_dot};
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
    /*QLineEdit lin;
    lin.setFrame(false);
    lin.setText("hui");
    lin.show();*/
    main_widget.show_widget();

    return a.exec();

}
