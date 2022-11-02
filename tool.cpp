#include "tool.h"

int paint_dot (Tool* tool, QPainter* p, Point click)
{
    p->pen();
    tool->set_last_click(click);
    return 0;
}
