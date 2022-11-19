#include "button.h"
#include "QPixmap"
//#include "widget.h"

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

int StandartButtonPaint (Button* button, QPainter* painter)
{
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
