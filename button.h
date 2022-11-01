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
    Point size_ = {};
    FormType form_type_ = rectangle;

public:
    AbstractButton(char* name, Vector color, Point size, FormType form_type):
        name_(name),
        color_(color),
        size_(size),
        form_type_(form_type)
    {}
};

class Button : public AbstractButton
{
private:
    Tool* my_tool_ = NULL;
public:
    Button(char* name, Vector color, Point size):
        AbstractButton(name, color, size, FormType{rectangle})
    {}
    void set_tool(Tool* tool){my_tool_ = tool;}
    Tool* get_tool() const {return my_tool_;}
};

#endif // BUTTON_H
