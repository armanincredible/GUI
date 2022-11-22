#include "widget.h"
#include "button.h"
#include "tool.h"

//WidgetManager* WidgetManager::cur_widget_painting_ = NULL;

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

int StandartWidgetPaint(WidgetManager* widget, QPainter* painter)
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
        cur_button->paint_function_(cur_button, painter);
        //cur_button->paintCoordinateSystem(painter);
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
    WidgetManager* widget = NULL;
    if (active_widget_)
    {
        widget = active_widget_;
    }
    else
    {
        widget = this;
    }

    QPainter painter(this->cast_to());

    Tool* tool = get_active_tool_from_tool_manager();
    if (tool)
    {
        tool->activity_(tool, &painter, get_click_coordinate());
    }
    else
    {
        widget->paint_function_(this, &painter);
    }
}

void WidgetManager::mouseReleaseEvent(QMouseEvent *event)
{
    fprintf (stderr, "in mouse release event\n");
    is_mouse_pressed_ = false;
}

void WidgetManager::mouseMoveEvent(QMouseEvent *event)
{
    fprintf (stderr, "in mouse move event\n");
    Point click = Point{double(event->x()), double(event->y())};
    set_click_coordinate(click);
    is_mouse_pressed_ = true;
    click_handler(click);
}

void WidgetManager::mousePressEvent(QMouseEvent *event)
{
    fprintf (stderr, "in mouse press event\n");
    Point click = Point{double(event->x()), double(event->y())};
    set_click_coordinate(click);
    click_handler(click);
}

WidgetManager *WidgetManager::get_main_widget_()
{
    static WidgetManager* widget;
    if (!widget)
    {
        widget = this;
        while(widget->get_parent_widget())
        {
            widget  = widget->get_parent_widget();
        }
    }
    return widget;
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
        //widget->setUpdatesEnabled(true);
        //widget->cur_widget_painting_ = widget;
        (widget->get_main_widget_())->set_flag(Qt::WA_OpaquePaintEvent);
        (widget->get_main_widget_())->set_active_widget(widget);
        (widget->get_main_widget_())->repaint_widget();
        //(widget->get_main_widget_())->set_active_widget(NULL);
        //(widget->get_main_widget_())->setAttribute(Qt::WA_OpaquePaintEvent, false);
    }
    return 0;
}
