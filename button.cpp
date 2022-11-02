#include "button.h"
#include "widget.h"

int button_with_instrument (Button* my_button, void* obj)
{
    Tool* tool = my_button->get_tool();
    WidgetManager* widget = (WidgetManager*) obj;
    ToolManager* tools = widget->get_tool_manager();
    tools->set_active_tool(tool);
    return 0;
}
