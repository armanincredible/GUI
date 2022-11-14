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

int StandartPaint(WidgetManager* widget, QPainter* painter)
{
    widget->paintCoordinateSystem(painter);
    for (int i = 0; i < widget->get_widgets_num(); i++)
    {
        WidgetManager* cur_widget = (widget->get_widgets())[i];
        cur_widget->paint_function_(cur_widget, painter);
        //widgets_[i]->paint(painter);
    }
    for (int i = 0; i < widget->get_buttons_num(); i++)
    {
        Button* cur_button = (widget->get_buttons())[i];
        cur_button->paintCoordinateSystem(painter);
    }
    return 0;
}

int WidgetManager::click_handler(Point click)
{
    WidgetManager* widget = NULL;
    for (int i = 0; i < widgets_num_; i++)
    {
        widget = widgets_[i];
        Button* button = NULL;
        Button** buttons = widget->get_buttons();
        for (int i = 0; i < widget->get_buttons_num(); i++)
        {
            button = buttons[i];
            if (button->is_my_area(click))
            {
                //fprintf (stderr, "found me button in widget %p\n", widget);
                if (widget->controller_)
                {
                    widget->controller_(button, widget);
                }
                else
                {
                    fprintf (stderr, "contoller function null ptr\n");
                }
                return 0;
            }
        }
        if (widget->is_my_area(click))
        {
            fprintf (stderr, "found me widget %p\n", widget);
            widget->set_click_coordinate(click);
            if (widget->controller_)
            {
                widget->repaint();
                widget->controller_(NULL, widget);
            }
            else
            {
                fprintf (stderr, "contoller function null ptr\n");
            }
            return 0;
        }
        widget->click_handler(click);
    }
    fprintf (stderr, "didnt find anything\n");
    //controller_(NULL, this);

    return 0;
}

void WidgetManager::paintEvent(QPaintEvent *)
{
    fprintf (stderr, "in paint event\n");
    QPainter painter(this);
    //paint_function_(this, &painter);

    ToolManager* tool_manager = get_tool_manager();
    if (tool_manager == nullptr)
    {
        //fprintf (stderr, "tool_manager null ptr\n");
        paint_function_(this, &painter);
        return;
    }
    Tool* act_tool = tool_manager->get_active_tool();
    if (act_tool == nullptr)
    {
        //fprintf (stderr, "act_tool null ptr\n");
        paint_function_(this, &painter);
        return;
    }
    fprintf (stderr, "make tool activity\n");
    act_tool->activity_(act_tool, &painter, get_click_coordinate());
}

void WidgetManager::mousePressEvent(QMouseEvent *event)
{
    fprintf (stderr, "in mouse event\n");
    Point click = Point{double(event->x()), double(event->y())};
    set_click_coordinate(click);
    click_handler(click);
}


int controller_paint (Button* button, WidgetManager* widget)
{
    fprintf (stderr, "in contoller\n");
    if (button)
    {
        button->response_(button, widget);
        return 0;
    }
    if (widget)
    {
        fprintf (stderr, "going to repaint, %p\n", widget);
        widget->setUpdatesEnabled(true);
        //widget->setMinimumSize();
        //widget->resize(100, 100);
        widget->repaint();
        //QAbstractScrollArea var(widget);
        //var.viewport()->repaint();
    }
    return 0;
}
