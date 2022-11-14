#ifndef WIDGET_H
#define WIDGET_H
#include "window.h"
#include "button.h"
#include "tool.h"
#include <QtWidgets>

enum WidgetType
{
    PaintWidget,
    MainWidget
};

class AbstrWidget : public CoordinateSystem, public QMainWindow
{
    virtual void paintEvent(QPaintEvent *){};
    virtual void mousePressEvent(QMouseEvent *){};
public:
    AbstrWidget(Point a, Point b):
        QMainWindow(),
        CoordinateSystem(a, b)
    {}
};

class WidgetManager : public AbstrWidget
{
private:
    Point mouse_click_coordinate_ = {};
    WidgetType type_ = {};
    WidgetManager** widgets_ = NULL;
    size_t widgets_num_ = 0;
    ToolManager* tool_manager_ = NULL;
    size_t tools_num_ = 0;
    Button** buttons_ = NULL;
    size_t buttons_num_ = 0;
    WidgetManager* parent_widget_ = NULL;
    char* widget_name = NULL;
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
public:
    int (*controller_) (Button*, WidgetManager*) = NULL;
    int (*paint_function_)(WidgetManager*, QPainter*) = NULL;

    WidgetManager(Point start_point, Point end_point, WidgetType type,
                  int (*controller) (Button*, WidgetManager*),
                  int (*paint_func) (WidgetManager*, QPainter*)):
        controller_(controller),
        AbstrWidget(start_point, end_point),
        type_(type),
        paint_function_(paint_func)
    {
        if (type != MainWidget)
        {
            setAttribute(Qt::WA_TransparentForMouseEvents);
            //setUpdatesEnabled(true);
        }
    }
    WidgetManager(Point start_point, Point end_point, WidgetType type,
                  int (*paint_func) (WidgetManager*, QPainter*)):
        AbstrWidget(start_point, end_point),
        type_(type),
        paint_function_(paint_func)
    {
        if (type != MainWidget)
        {
            setAttribute(Qt::WA_TransparentForMouseEvents);
            //setUpdatesEnabled(true);
        }
    }
    int add_widget (WidgetManager* widget)
    {
        if (!widgets_num_ && widgets_)
        {
            printf ("ERROR %d\n", __LINE__);
        }
        widgets_num_++;
        widgets_ = (WidgetManager**) realloc (widgets_, widgets_num_ * sizeof(WidgetManager*));
        if (widgets_ == NULL)
        {
            return -1;
        }
        widgets_[widgets_num_ - 1] = widget;
        widget->set_parent_widget(this);
        return 0;
    }
    WidgetManager** get_widgets (){return widgets_;}
    void set_widgets (WidgetManager** widgets){widgets_ = widgets;}
    void set_widgets_num (size_t num){widgets_num_ = num;}
    size_t get_widgets_num (){return widgets_num_;}

    int add_button (Button* button)
    {
        if (!buttons_num_ && buttons_)
        {
            printf ("ERROR %d\n", __LINE__);
        }
        buttons_num_++;
        buttons_ = (Button**) realloc (buttons_, buttons_num_ * sizeof(Button*));
        if (buttons_ == NULL)
        {
            return -1;
        }
        buttons_[buttons_num_ - 1] = button;
        return 0;
    }
    Button** get_buttons (){return buttons_;}
    void set_buttons (Button** buttons){buttons_ = buttons;}
    void set_buttons_num (size_t num){buttons_num_ = num;}
    size_t get_buttons_num (){return buttons_num_;}

    WidgetManager* get_parent_widget (){return parent_widget_;}
    void set_parent_widget (WidgetManager* widget){parent_widget_ = widget;}

    ToolManager* get_tool_manager (){return tool_manager_;}
    void set_tool_manager (ToolManager* tool_manager){tool_manager_ = tool_manager;}

    Point get_click_coordinate (){return mouse_click_coordinate_;}
    void set_click_coordinate (Point click){mouse_click_coordinate_ = click;}

    int click_handler(Point);
};

int controller_paint (Button*, WidgetManager*);
int StandartPaint(WidgetManager*, QPainter*);

#endif // WIDGET_H
