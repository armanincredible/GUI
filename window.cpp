#include "window.h"
#include "math.h"

int CoordinateSystem::paintCoordinateSystem (QPainter* painter)
{
    if (painter == NULL)
    {
        return -1;
    }
    int x0 = start_point_.x;
    int y0 = start_point_.y;
    int height = heigh();
    int widtht = width();

    //int origin_x = origin_point_.x;
    //int origin_y = origin_point_.y;

    painter->drawRect(x0, y0, widtht, height);
    /*painter->drawLine(origin_x, y0 + height,
                     origin_x, y0);*/

    /*painter->drawLine(x0,         origin_y,
                     x0 + widtht, origin_y);*/
    return 0;
}

/*
void Window_Clock::paintEvent(QPaintEvent *)
{
    static double alpha = 0;

    QPainter painter(this);

    Point origin_point = get_origin_point();
    paintCoordinateSystem(&painter);

    Vector vec = {{0, 0}, {get_radius() * sin(alpha), get_radius() * cos(alpha)}};
    Vector vec2 = vec - vec * 2;
    vec.paintVector(&painter, origin_point);
    vec2.paintVector(&painter, origin_point);

    alpha += 3.14/10000;
    update();
}


void Window_Click::mousePressEvent(QMouseEvent *event)
{
    Point origin_point = get_origin_point();
    mouse_click_.x = event->x() - origin_point.x;
    mouse_click_.y = origin_point.y - event->y();
    repaint();
}


void Window_Click::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    Point origin_point = get_origin_point();
    paintCoordinateSystem(&painter);

    Vector vec = {{0, 0}, {mouse_click_.x, mouse_click_.y}};

    vec.paintVector(&painter, origin_point);
}*/

int CoordinateSystem::is_my_area(Point click) const
{
    Point start_point = get_start_point();
    Point end_point = get_end_point();
    //fprintf (stderr, "start x and y %lg %lg\n", start_point.x, start_point.y);
    //fprintf (stderr, "end x and y %lg %lg\n", end_point.x, end_point.y);
    if (click.x > start_point.x && click.x < end_point.x &&
        click.y > start_point.y && click.y < end_point.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
