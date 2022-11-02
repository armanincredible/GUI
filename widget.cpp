#include "widget.h"
#include "button.h"
#include "tool.h"

template < typename T >
int find_element (T** objects, size_t objects_num, Point click)
{
    for (int i = 0; i < objects_num; i++)
    {
        if (objects[i]->is_my_area(click))
        {
            objects[i]->click_handler(click);
            return i;
        }
    }
    return -1;
}

int WidgetManager::paint(QPainter* painter)
{
    paintCoordinateSystem(painter);
    for (int i = 0; i < widgets_num_; i++)
    {
        widgets_[i]->paint(painter);
    }
    for (int i = 0; i < buttons_num_; i++)
    {
        buttons_[i]->paintCoordinateSystem(painter);
    }
    return 0;
}

int WidgetManager::click_handler(Point click)
{
    WidgetManager* widget = NULL;
    for (int i = 0; i < widgets_num_; i++)
    {
        widget = widgets_[i];
        if (widget->is_my_area(click))
        {
            widget->set_click_coordinate(click);
            widget->click_handler(click);
            return 0;
        }
    }

    Button* button = NULL;
    for (int i = 0; i < buttons_num_; i++)
    {
        button = buttons_[i];
        if (button->is_my_area(click))
        {
            widget->controller_(button, this, button->get_tool());
            return 0;
        }
    }

    widget->controller_(NULL, this, NULL);

    return 0;
}

void WidgetManager::paintEvent(QPaintEvent *event)
{
    //event->
    QPainter painter(this);
    paint(&painter);

}

void WidgetManager::mousePressEvent(QMouseEvent *event)
{
    click_handler(Point{double(event->x()), double(event->y())});
}


int controller_paint (Button* button, WidgetManager* widget, Tool* tool)
{
    if (button)
    {
        return 0;
    }
    if (widget)
    {
        QPainter painter(widget);
        ToolManager* tool_manager = widget->get_tool_manager();
        Tool* act_tool = tool_manager->get_active_tool();
        act_tool->activity_(act_tool, &painter, widget->get_click_coordinate());
    }
    return 0;
}
