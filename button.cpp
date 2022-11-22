#include "button.h"
#include "QPixmap"
#include "widget.h"

int button_with_instrument (Button* my_button, void* obj)
{
    fprintf (stderr, "in button function interrupt\n");
    Tool* tool = my_button->get_tool();
    if (tool == NULL)
    {
        fprintf (stderr, "button's tool null ptr\n");
        return -1;
    }
    if (tool->set_active_tool_in_manager())
    {
        fprintf (stderr, "button's tool cant become active\n");
        return -1;
    }
    else
    {
        WidgetManager* widget = (WidgetManager*) obj;
        widget->set_active_tool_manager((ToolManager*)tool->get_tool_manager());
    }
    /*WidgetManager* widget = (WidgetManager*) obj;
    ToolManager* tools = widget->get_tool_manager();
    if (tools == NULL)
    {
        fprintf (stderr, "tool manager in widget null ptr\n");
        return -1;
    }
    tools->set_active_tool(tool);*/
    return 0;
}

int button_change_color_tool (Button* my_button, void* obj)
{
    fprintf (stderr, "in button function interrupt\n");
    WidgetManager* wid = (WidgetManager*)my_button->get_widget();
    if (wid != obj)
    {
        fprintf (stderr, "button's widget and his real widget controller are not equal\n");
        return -1;
    }

    Tool* tool = wid->get_active_tool_from_tool_manager();
    if (tool)
    {
        tool->set_color(my_button->get_color());
    }
    else
    {
        fprintf (stderr, "hasnt activity tool\n");
        return -1;
    }

    return 0;
}

int StandartButtonPaint (Button* button, QPainter* painter)
{
    if (button->is_colored())
    {
        int x0 = button->get_start_point().x;
        int y0 = button->get_start_point().y;
        //QPen pen(Qt::red);
        Color color = button->get_color();
        QBrush brush(QColor(color.r * 255, color.g * 255, color.b * 255));
        //painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(x0, y0, button->width(), button->heigh());
        return 0;
    }
    button->paintCoordinateSystem(painter);
    return 0;
}

int ButtonPaintFromPicture (Button* button, QPainter* painter)
{
    if (button->get_image_path())
    {
        Point start {button->get_start_point()};
        Point end {button->get_end_point()};

        int w = end.x - start.x;
        int h = end.y - start.y;

        QRect target(start.x, start.y,
                     w, h);

        QPixmap pix (button->get_image_path());

        if (pix.isNull())
        {
            painter->drawText(target, button->get_image_path(), Qt::AlignHCenter | Qt::AlignVCenter);
            fprintf (stderr, "Pixmap is emty because file image doesnt exit\n");
            return 0;
        }

        QRect source(0, 0, (pix.size()).width(), (pix.size()).height());
        pix.scaled(w, h, Qt::IgnoreAspectRatio);

        painter->drawPixmap(target, pix, source);
        button->paintCoordinateSystem(painter);
        return 0;
    }
    else
    {
        fprintf (stderr, "buttons image path is NULL\n");
        button->paintCoordinateSystem(painter);// add text with info abput file name
    }

    return -1;
}
