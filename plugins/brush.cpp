#include "brush.h"

IPlugin* my_plugin;

IPlugin* get_plugin()
{
    IPlugin* plugin = new IPlugin;
    my_plugin = plugin;
    BrushButton* button = new BrushButton({0, 0}, {200, 300});
    //button->image_path_ = "/home/narman/qt_projects/GUI/stream/pencil.png";
    plugin->set_tool_button(button);
    plugin->set_props(NULL);
    plugin->set_tool(NULL);

    return plugin;
}

/**
 * Deinitializes plugin.
 */
void destroy_plugin()
{
    if (my_plugin)
    {
        delete my_plugin->get_tool_button();
        delete my_plugin;
    }
    return;
}
