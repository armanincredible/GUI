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
    char* name_ = NULL;
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
};

class Button : public AbstractButton
{
private:
    Tool* my_tool_ = NULL;
public:
    Button(char* name, Vector color, Point start, Point end, int (*response)(Button*, void*)):
        AbstractButton(name, color, start, end, FormType{rectangle})
    {
        response_ = response;
    }
    Button(char* name, Vector color, Point start, Point end,  FormType form_type):
        AbstractButton(name, color, start, end, FormType{rectangle})
    {}
    Button(Point start, Point end, int (*response)(Button*, void*)):
        AbstractButton(start, end),
        response_(response)
    {}

    int (*response_)(Button*, void*);
    void set_tool(Tool* tool){my_tool_ = tool;}
    Tool* get_tool() const {return my_tool_;}
};

int button_with_instrument (Button*, void*);

#endif // BUTTON_H
