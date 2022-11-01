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
            widget->controller(button, this, button->get_tool());
        }
    }

    return 0;
}

int WidgetManager::controller(Button* button, WidgetManager* widget, Tool* tool)
{
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
