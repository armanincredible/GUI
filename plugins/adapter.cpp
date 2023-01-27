#include "adapter.h"
#include "../widget.h"
#include "../button.h"
#include "../error.h"


int ButtonAdapterController (Button* button, WidgetManager* widget)
{
    START_;

    ButtonAdapter* button_adapter = (ButtonAdapter*) button;
    Point click = widget->get_main_widget_()->get_click_coordinate();
    button_adapter->ibutton_->on_mouse_press({(int)click.x, (int)click.y});

    Tool* tool = button->get_tool();
    if (tool == NULL)
    {
        PRINT_("button's tool null ptr\n");
        END_(-1);
    }
    if (tool->set_active_tool_in_manager())
    {
        PRINT_("button's tool cant become active\n");
        END_(-1);
    }
    else
    {
        widget->set_active_tool_manager((ToolManager*)tool->get_tool_manager());

        widget->repaint_all_with_state(CurrentWork::ChangeActiveTool);

        END_(0);
    }
    END_(0);
}

int ButtonAdapterPaint(Button* button, QPainter* painter)
{
    START_;
    //IWidget* iwidget = (WidgetAdapter*) widget;
    ButtonAdapter* button_adapter = (ButtonAdapter*) button;
    int size_x = button_adapter->ibutton_->get_size().x;
    int size_y = button_adapter->ibutton_->get_size().y;

    int x0 = button_adapter->ibutton_->get_pos().x;
    int y0 = button_adapter->ibutton_->get_pos().y;

    QRect target(x0, y0, size_x, size_y);
    QRect src_rect(0, 0, size_x, size_y);

    uchar* collor_buffer = button_adapter->src_.bits();

    button_adapter->ibutton_->draw((unsigned int*)collor_buffer, size_x,
                                                                 size_y);

    QPixmap pmap(size_x, size_y);
    pmap.convertFromImage(button_adapter->src_);

    painter->drawPixmap(target, pmap, src_rect);

    END_(0);
}

int WidgetAdapterPaint(WidgetManager* widget, QPainter* painter)
{
    START_;

    WidgetAdapter* widget_adapter = (WidgetAdapter*) widget;
    int size_x = widget_adapter->iwidget_->get_size().x;
    int size_y = widget_adapter->iwidget_->get_size().y;

    int x0 = widget_adapter->iwidget_->get_pos().x;
    int y0 = widget_adapter->iwidget_->get_pos().y;

    QRect target(x0, y0, size_x, size_y);
    //QRect target(0, 0, 1920, 1080);
    uchar* collor_buffer = widget_adapter->src_.bits();

    widget_adapter->iwidget_->draw((unsigned int*)collor_buffer, size_x,
                                                                 size_y);

    QPixmap pmap(size_x, size_y);
    pmap.convertFromImage(widget_adapter->src_);

    painter->drawPixmap(target, pmap, target);

    END_(0);
}

int controller_adapter_widget (Button* button, WidgetManager* widget)
{
    START_;
    if (button)
    {
        button->response_(button, widget);
    }
    if (widget)
    {
        //Point click = widget->get_main_widget_()->get_click_coordinate();

        (widget->get_main_widget_())->set_flag(Qt::WA_OpaquePaintEvent);
        (widget->get_main_widget_())->repaint_widget();
    }
    END_(0);
}

int ToolActivityAdapter(Tool* tool, QPainter* painter, Point p)
{
    START_;

    ToolAdapter* tool_adapter = (ToolAdapter*) tool;
    int size_x = 100;//tool_adapter->iwidget_->get_size().x;
    int size_y = 100;//tool_adapter->iwidget_->get_size().y;

    QRect target(0, 0, size_x, size_y);
    uchar* collor_buffer = tool_adapter->src_.bits();

    tool_adapter->itool_->apply((unsigned int*)collor_buffer, 0, 0,
                                {(int)p.x, (int)p.y});

    QPixmap pmap(size_x, size_y);
    pmap.convertFromImage(tool_adapter->src_);

    painter->drawPixmap(target, pmap, target);

    END_(0);
}
