#ifndef WIDGET_H
#define WIDGET_H
#include "window.h"
#include "button.h"
#include "tool.h"
#include <QtWidgets>

enum TypeWidget
{
    RedColorProperty,
    GreenColorProperty,
    BlueColorProperty,
};

class AbstrWidget : public CoordinateSystem, public QMainWindow
{
    virtual void paintEvent(QPaintEvent *){};
    virtual void mousePressEvent(QMouseEvent *){};
    virtual void mouseReleaseEvent(QMouseEvent *){};
    virtual void mouseMoveEvent(QMouseEvent *){};
public:
    QPaintDevice* cast_to(){return (QPaintDevice*)this;}
    void repaint_widget(){repaint();}
    void resize_widget(int a, int b){resize(a, b);}
    void show_widget(){show();}
    void set_flag(Qt::WidgetAttribute attribute, bool on = true){
        setAttribute(attribute, on);
    }

    AbstrWidget(Point a, Point b):
        QMainWindow(),
        CoordinateSystem(a, b)
    {}
};

class WidgetManager : public AbstrWidget
{
private:
    Point mouse_click_coordinate_ = {};
    bool is_mouse_pressed_ = 0;
    WidgetManager** widgets_ = NULL;
    size_t widgets_num_ = 0;
    ToolManager* tool_manager_ = NULL;
    size_t tools_num_ = 0;
    Button** buttons_ = NULL;
    size_t buttons_num_ = 0;
    WidgetManager* parent_widget_ = NULL;
    char* widget_name = NULL;

    WidgetManager* active_widget_ = NULL;
    ToolManager* active_tool_manager_ = NULL;
    //Tool* tool_ = NULL; // this ptr for tool, which properties widget shows
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
public:
    int (*controller_) (Button*, WidgetManager*) = NULL;
    int (*paint_function_)(WidgetManager*, QPainter*) = NULL;

    WidgetManager(Point start_point, Point end_point,
                  WidgetManager* parent_widget,
                  int (*controller) (Button*, WidgetManager*),
                  int (*paint_func) (WidgetManager*, QPainter*)):
        parent_widget_(parent_widget),
        controller_(controller),
        AbstrWidget(start_point, end_point),
        paint_function_(paint_func)
    {
        if (parent_widget)
        {
            set_flag(Qt::WA_TransparentForMouseEvents);
            //setVisible(true);
        }
    }

    WidgetManager(Point start_point, Point end_point,
                  WidgetManager* parent_widget,
                  int (*paint_func) (WidgetManager*, QPainter*)):
        parent_widget_(parent_widget),
        AbstrWidget(start_point, end_point),
        paint_function_(paint_func)
    {
        if (parent_widget)
        {
            set_flag(Qt::WA_TransparentForMouseEvents);
            //setVisible(true);
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
        button->set_widget(this);
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

    WidgetManager* get_main_widget_ ();

    WidgetManager* get_active_widget (){return get_main_widget_()->active_widget_;}
    void set_active_widget (WidgetManager* tool_manager){get_main_widget_()->active_widget_ = tool_manager;}

    ToolManager* get_active_tool_manager (){return get_main_widget_()->active_tool_manager_;}
    void set_active_tool_manager (ToolManager* tool_manager){get_main_widget_()->active_tool_manager_ = tool_manager;}

    Tool* get_active_tool_from_tool_manager()
    {
        if (get_active_tool_manager())
        {
            return get_active_tool_manager()->get_active_tool();
        }
        else
        {
            return NULL;
        }
    }
    int set_active_tool_from_tool_manager(Tool* tool)
    {
        if (get_active_tool_manager())
        {
            get_active_tool_manager()->set_active_tool(tool);
            return 0;
        }
        else
        {
            return -1;
        }
    }

    bool is_mouse_pressed (){return is_mouse_pressed_;}

    Point get_click_coordinate (){return mouse_click_coordinate_;}
    void set_click_coordinate (Point click){mouse_click_coordinate_ = click;}

    int click_handler(Point);
};

int controller_paint (Button*, WidgetManager*);
int StandartWidgetPaint(WidgetManager*, QPainter*);

#endif // WIDGET_H
