#ifndef WIDGET_H
#define WIDGET_H
#include "window.h"
#include "button.h"
#include "tool.h"

class AbstrWidget : public CoordinateSystem, public QWidget
{
    virtual void paintEvent(QPaintEvent *){};
    virtual void mousePressEvent(QMouseEvent *){};
public:
    AbstrWidget(Point a, Point b):
        CoordinateSystem(a, b)
    {}
};

class WidgetManager : public AbstrWidget
{
private:
    WidgetManager** widgets_ = NULL;
    size_t widgets_num_ = 0;
    ToolManager** tools_ = NULL;
    size_t tools_num_ = 0;
    Button** buttons_ = NULL;
    size_t buttons_num_ = 0;
    WidgetManager* parent_widget_ = NULL;
    char* widget_name = NULL;
protected:
    int controller (Button*, WidgetManager*, Tool*);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
public:
    WidgetManager(Point start_point, Point end_point):
        AbstrWidget(start_point, end_point)
    {}
    int add_widget (WidgetManager* widget)
    {
        widgets_num_++;
        widgets_ = (WidgetManager**) realloc (widgets_, widgets_num_ * sizeof(WidgetManager*));
        if (widgets_ == NULL)
        {
            return -1;
        }
        widgets_[widgets_num_ - 1] = widget;
        return 0;
    }
    WidgetManager** get_widgets (){return widgets_;}
    void set_widgets (WidgetManager** widgets){widgets_ = widgets;}
    void set_widgets_num (size_t num){widgets_num_ = num;}
    size_t get_widgets_num (){return widgets_num_;}

    int add_button (Button* button)
    {
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

    int paint(QPainter*);
    int click_handler(Point);
};


#endif // WIDGET_H
