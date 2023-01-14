#include "widget.h"
#include "button.h"
#include "tool.h"
#include "error.h"
#include "texteditor.h"

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
    START_;
    /*
     * widget which we paint can be only active, non active and prev active
     * if its prev active we repaint his lines in typical color
     */
    /*if (widget == widget->get_active_widget())
    {
        if (widget->get_prev_active_widget())
        {
            widget->get_prev_active_widget()->paintCoordinateSystem(painter);
        }
        widget->paintCoordinateSystem(painter, false, {0.2, 0.6, 0.2});
    }
    else
    {
        widget->paintCoordinateSystem(painter);
    }*/
    widget->paintCoordinateSystem(painter);
    for (int i = 0; i < widget->get_widgets_num(); i++)
    {
        WidgetManager* cur_widget = (widget->get_widgets())[i];
        cur_widget->paint_function_(cur_widget, painter);
        //widgets_[i]->paint(painter);
    }
    for (int i = 0; i < widget->get_text_editors_num(); i++)
    {
        TextEditor** text_editors = (TextEditor**)widget->get_text_editors();
        TextEditor* text_editor = text_editors[i];
        text_editor->paint_function_(text_editor, painter);
        //widgets_[i]->paint(painter);
    }
    for (int i = 0; i < widget->get_buttons_num(); i++)
    {
        Button* cur_button = (widget->get_buttons())[i];
        cur_button->paint_function_(cur_button, painter);
        //cur_button->paintCoordinateSystem(painter);
    }
    END_(0);
}

/*
 * Function find object, which area was clicked and call controller
 * If controller was called function return 0, another way -1
 */
int WidgetManager::click_handler(Point click)
{
    START_;
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
                PRINT_("found me button in widget %p\n", widget);
                if (widget->controller_)
                {
                    set_active_widget(widget);
                    widget->controller_(button, widget);
                }
                else
                {
                    PRINT_("contoller function null ptr\n");
                }
                END_(0);
            }
        }
        TextEditor* text_editor = NULL;
        TextEditor** text_editors = (TextEditor**)widget->get_text_editors();
        for (int i = 0; i < widget->get_text_editors_num(); i++)
        {
            text_editor = text_editors[i];
            if (text_editor->is_my_area(click))
            {
                PRINT_("found me text_editor in widget %p\n", widget);
                if (text_editor->controller_)
                {
                    set_active_widget(text_editor);
                    text_editor->controller_(NULL, text_editor);
                }
                else
                {
                    PRINT_("contoller function null ptr\n");
                }
                END_(0);
            }
        }
        if (widget->is_my_area(click))
        {
            PRINT_("found me widget %p\n", widget);
            if (!widget->click_handler(click))
            {
                END_(0);
            }

            widget->set_click_coordinate(click);
            if (widget->controller_)
            {
                set_active_widget(widget);
                widget->controller_(NULL, widget);
            }
            else
            {
                PRINT_("contoller function null ptr\n");
            }
            END_(0);
        }
        //widget->click_handler(click);
    }
    PRINT_("didnt find anything\n");
    //controller_(NULL, this);
    END_(-1);
}

void WidgetManager::keyPressEvent(QKeyEvent *event)
{
    START_;
    WidgetManager* active_widget = get_active_widget();
    if (active_widget && active_widget->is_need_in_key_events())
    {
        if (active_widget->is_text_editor())
        {
            TextEditor* text_editor = (TextEditor*) active_widget;
            if (event->key() == Qt::Key_Backspace)
            {
                text_editor->delete_data();
            }
            else if (event->key() == 0x01000004)//enter
            {
                text_editor->controller_(NULL, text_editor);
            }
            else
            {
                text_editor->set_data(*((char*)event->text().data()));
            }
        }
    }
    END_();
}

void WidgetManager::paintEvent(QPaintEvent *)
{
    START_;
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

    /*
     * for this stage this method know only about active widget
     * if it wants to paint it needs to have tool manager
     */
    if (widget->get_tool_manager())
    {
        Tool* tool = get_active_tool_from_tool_manager();
        if (tool)
        {
            tool->activity_(tool, &painter, get_click_coordinate());
        }
    }
    else
    {
        /*
         * paint only active widget or all widgets if active is null
         */
        widget->paint_function_(widget, &painter);
    }
    END_();
}

void WidgetManager::mouseReleaseEvent(QMouseEvent *event)
{
    START_;
    is_mouse_pressed_ = false;
    END_();
}

void WidgetManager::mouseMoveEvent(QMouseEvent *event)
{
    START_;
    Point click = Point{double(event->x()), double(event->y())};
    set_click_coordinate(click);
    is_mouse_pressed_ = true;
    click_handler(click);
    END_();
}

void WidgetManager::mousePressEvent(QMouseEvent *event)
{
    START_;
    Point click = Point{double(event->x()), double(event->y())};
    set_click_coordinate(click);
    click_handler(click);
    END_();
}

WidgetManager *WidgetManager::get_main_widget_()
{
    START_;
    static WidgetManager* widget;
    if (!widget)
    {
        widget = this;
        while(widget->get_parent_widget())
        {
            widget  = widget->get_parent_widget();
        }
    }
    END_(widget);
}


int controller_paint (Button* button, WidgetManager* widget)
{
    START_;
    if (button)
    {
        button->response_(button, widget);
        END_(0);
    }
    if (widget)
    {
        PRINT_("going to repaint, %p\n", widget);

        (widget->get_main_widget_())->set_flag(Qt::WA_OpaquePaintEvent);
        (widget->get_main_widget_())->repaint_widget();
    }

    END_(0);
}

int controller_only_buttons (Button* button, WidgetManager* widget)
{
    START_;
    if (button)
    {
        button->response_(button, widget);
        END_(0);
    }
    if (widget)
    {
        PRINT_("going to repaint, %p\n", widget);

        (widget->get_main_widget_())->set_flag(Qt::WA_OpaquePaintEvent);
        (widget->get_main_widget_())->repaint_widget();
    }
    END_(0);
}
