#include "tool.h"

int paint_dot (Tool* tool, QPainter* p, Point click)
{
    Color color = tool->get_color();
    QPen paintpen(QColor(color.r * 255, color.g * 255, color.b * 255));
    paintpen.setWidth(4);
    p->setPen(paintpen);
    p->drawPoint(click.x, click.y);
    //p->pen();
    //p->drawLine(10, 20, 40, 50);

    tool->set_last_click(click);
    return 0;
}

int paint_line (Tool* tool, QPainter* p, Point click)
{
    if (tool->get_cur_num_click())
    {
        QPen paintpen(Qt::red);
        paintpen.setWidth(4);
        p->setPen(paintpen);
        p->drawLine(tool->get_last_click().x, tool->get_last_click().y,
                    click.x, click.y);
        tool->set_cur_num_click(0);
        return 0;
    }

    tool->add_cur_num_click();
    tool->set_last_click(click);
    return 0;
}

int Tool::set_active_tool_in_manager()
{
    if (my_tool_manager_)
    {
        ToolManager* tools = (ToolManager*) my_tool_manager_;
        tools->set_active_tool(this);
        return 0;
    }
    return -1;
}
