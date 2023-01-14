#ifndef BUTTON_H
#define BUTTON_H
#include "vectors.h"
#include "tool.h"
#include "window.h"

enum FormType
{
    triangle,
    rectangle
};

class AbstractButton : public CoordinateSystem
{
private:
    const char* name_ = NULL;
    Vector color_ = {};
    FormType form_type_ = rectangle;

public:
    AbstractButton(char* name, Vector color, Point a, Point b,  FormType form_type):
        CoordinateSystem(a, b),
        name_(name),
        color_(color),
        form_type_(form_type)
    {}
    AbstractButton(Point a, Point b):
        CoordinateSystem(a, b)
    {}

    void set_name(const char* name){name_ = name;}
    const char* get_name() const {return name_;}
};

class Button : public AbstractButton
{
private:
    void* my_widget_ = nullptr;
    Tool* my_tool_ = nullptr;
    const char* image_path_ = NULL;
    Color color_{};
    bool is_colored_ = false;
public:
    Button(char* name, Vector color, Point start, Point end, int (*response)(Button*, void*)):
        AbstractButton(name, color, start, end, FormType{rectangle})
    {
        response_ = response;
    }
    Button(char* name, Vector color, Point start, Point end,  FormType form_type):
        AbstractButton(name, color, start, end, FormType{rectangle})
    {}
    Button(Point start, Point end, Tool* tool,
           int (*response)(Button*, void*),
           int (*paint_function)(Button*, QPainter*)):
        AbstractButton(start, end),
        my_tool_(tool),
        response_(response),
        paint_function_(paint_function)
    {}
    Button(Point start, Point end,
           int (*response)(Button*, void*),
           int (*paint_function)(Button*, QPainter*)):
        AbstractButton(start, end),
        response_(response),
        paint_function_(paint_function)
    {}

    int (*paint_function_)(Button*, QPainter*) = NULL;
    int (*response_)(Button*, void*);

    void set_tool(Tool* tool){my_tool_ = tool;}
    Tool* get_tool() const {return my_tool_;}

    void set_widget(void* widget){my_widget_ = widget;}
    void* get_widget() const {return my_widget_;}

    void set_image_path(const char* path){image_path_ = path;}
    const char* get_image_path(){return image_path_;}

    void set_color(Color color){color_ = color; is_colored_ = true;}
    Color get_color(){return color_;}
    bool is_colored(){return is_colored_;}
};

int button_with_instrument (Button*, void*);
int button_change_color_tool (Button*, void*);
int StandartButtonPaint (Button*, QPainter*);
int ButtonPaintFromPicture (Button*, QPainter*);

#endif // BUTTON_H
