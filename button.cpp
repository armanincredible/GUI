#include "button.h"
#include "widget.h"

int button_with_instrument (Button* my_button, void* obj)
{
    fprintf (stderr, "in button function interrupt\n");
    Tool* tool = my_button->get_tool();
    if (tool == NULL)
    {
        fprintf (stderr, "button's tool null ptr\n");
        return -1;
    }
    WidgetManager* widget = (WidgetManager*) obj;
    ToolManager* tools = widget->get_tool_manager();
    if (tools == NULL)
    {
        fprintf (stderr, "tool manager in widget null ptr\n");
        return -1;
    }
    tools->set_active_tool(tool);
    return 0;
}
