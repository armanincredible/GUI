#ifndef ADAPTER_H
#define ADAPTER_H

#include "../plugin.h"
#include "../widget.h"

#ifndef WIN32
#include <dlfcn.h>
#else
#include <windows.h>
#endif

int WidgetAdapterPaint(WidgetManager* widget, QPainter* painter);
WidgetManager* from_iwidget_to_widget(IWidget* widget);
int controller_adapter_widget (Button* button, WidgetManager* widget);
int ToolActivityAdapter(Tool* tool, QPainter* painter, Point p);

class ToolAdapter: public Tool
{
public:
    QImage src_ = {};
    ITool* itool_ = NULL;
    ToolAdapter(ITool* tool):
        Tool(ToolActivityAdapter),
        itool_(tool)
    {}
};

int ToolActivityAdapter(Tool* tool, QPainter* painter, Point p)
{
    ToolAdapter* tool_adapter = (ToolAdapter*) tool;
    int size_x = tool_adapter->iwidget_->get_size().x;
    int size_y = tool_adapter->iwidget_->get_size().y;

    QRect target(0, 0, size_x, size_y);
    uchar* collor_buffer = tool_adapter->src_.bits();

    tool_adapter->itool_->apply((unsigned int*)collor_buffer, 0, 0,
                                {(int)p.x, (int)p.y});

    QPixmap pmap(size_x, size_y);
    pmap.convertFromImage(tool_adapter->src_);

    painter->drawPixmap(target, pmap, target);
    return 0;
}


class WidgetAdapter : public WidgetManager
{
public:
    IWidget* iwidget_ = NULL;
    QImage src_ = {};
    WidgetAdapter(IWidget* iwidget, WidgetManager* parent, Layer* layer):
        WidgetManager({(double)iwidget->get_pos().x, (double)iwidget->get_pos().y},
                      {(double)iwidget->get_pos().x + iwidget->get_size().x,
                       (double)iwidget->get_pos().y + iwidget->get_size().y},
                       parent, controller_adapter_widget, WidgetAdapterPaint, layer),
        iwidget_(iwidget)
    {}
};

int WidgetAdapterPaint(WidgetManager* widget, QPainter* painter)
{
    WidgetAdapter* widget_adapter = (WidgetAdapter*) widget;
    int size_x = widget_adapter->iwidget_->get_size().x;
    int size_y = widget_adapter->iwidget_->get_size().y;

    QRect target(0, 0, size_x, size_y);
    uchar* collor_buffer = widget_adapter->src_.bits();

    widget_adapter->iwidget_->draw((unsigned int*)collor_buffer, size_x,
                                                                 size_y);

    QPixmap pmap(size_x, size_y);
    pmap.convertFromImage(widget_adapter->src_);

    painter->drawPixmap(target, pmap, target);

    return 0;
}

WidgetManager* from_iwidget_to_widget(IWidget* widget)
{
}

int controller_adapter_widget (Button* button, WidgetManager* widget)
{
    if (button)
    {
        button->response_(button, widget);
    }
    if (widget)
    {
        //Point click = widget->get_main_widget_()->get_click_coordinate();

        (widget->get_main_widget_())->set_flag(Qt::WA_OpaquePaintEvent);
        (widget->get_main_widget_())->repaint_widget();
    }
    return 0;
}

int ButtonAdapterController (Button*, WidgetManager*);

int ButtonAdapterPaint (Button*, QPainter*);

class ButtonAdapter: public Button
{
public:
    IPushButton* ibutton_ = NULL;
    QImage src_ = {};

    ButtonAdapter(IPushButton* ibutton, Layer* layer):
        Button({(double)ibutton->get_pos().x, (double)ibutton->get_pos().y},
              {(double)ibutton->get_pos().x + ibutton->get_size().x,
               (double)ibutton->get_pos().y + ibutton->get_size().y},
                ButtonAdapterController, ButtonAdapterPaint, layer),
        ibutton_(ibutton)
    {}
};

int ButtonAdapterController (Button* button, WidgetManager* widget)
{
    ButtonAdapter* button_adapter = (ButtonAdapter*) button;
    Point click = widget->get_main_widget_()->get_click_coordinate();
    button_adapter->ibutton_->on_mouse_press({(int)click.x, (int)click.y});
    return 0;
}

int ButtonAdapterPaint(Button* button, QPainter* painter)
{
    //IWidget* iwidget = (WidgetAdapter*) widget;
    ButtonAdapter* button_adapter = (ButtonAdapter*) button;
    int size_x = button_adapter->ibutton_->get_size().x;
    int size_y = button_adapter->ibutton_->get_size().y;

    QRect target(0, 0, size_x, size_y);
    uchar* collor_buffer = button_adapter->src_.bits();

    button_adapter->ibutton_->draw((unsigned int*)collor_buffer, size_x,
                                                                 size_y);

    QPixmap pmap(size_x, size_y);
    pmap.convertFromImage(button_adapter->src_);

    painter->drawPixmap(target, pmap, target);
}

class PluginAdapter
{
    IPlugin* iplugin_ = NULL;

    IPlugin* (*get_plugin)() = NULL;
    void* lib_ = NULL;
    void (*destroy_plugin)() = NULL;

    Tool* tool_ = NULL;

    WidgetManager* props_ = NULL;

    Button* tool_button_ = NULL;

    Tool* make_tool_from_itool(ITool* itool)
    {
        ToolAdapter* tool_adapter = new ToolAdapter(itool);
        return tool_adapter;
    }

    WidgetManager* make_widget_from_iwidget(IWidget* iwidget, WidgetManager* parent_widget, Layer* layer)
    {
        WidgetAdapter* widget_adapter = new WidgetAdapter(iwidget, parent_widget, layer);
        return widget_adapter;
    }

    Button* make_button_from_ibutton(IPushButton* ibutton, Layer* layer)
    {
        ButtonAdapter* button_adapter = new ButtonAdapter(ibutton, layer);
        return button_adapter;
    }

    int load_plugin(char* lib_name)
    {
        #ifndef WIN32
           lib_ = dlopen(lib_name, RTLD_LAZY);
        #else
           lib_ = LoadLibrary(s);
        #endif
           if (!lib_) {
             printf("cannot open library '%s'\n", lib_name);
             return -1;
           }
        #ifndef WIN32
           get_plugin = (IPlugin* (*)())dlsym(lib_, "get_plugin");
           destroy_plugin = (void (*)()) dlsym(lib_, "destroy_plugin");
        #else
           get_plugin = (IPlugin* (*)())GetProcAddress((HINSTANCE)lib_, "get_plugin");
           destroy_plugin = (void (*)())GetProcAddress((HINSTANCE)lib_, "destroy_plugin");
        #endif
           if (get_plugin == NULL || destroy_plugin == NULL) {
             printf("cannot load functions\n");
             return -1;
           }

           iplugin_ = get_plugin();
    }

    void delete_plugin()
    {
        if (destroy_plugin)
        {
            destroy_plugin();
        }
        if (lib_)
        {
            #ifndef WIN32
               dlclose(lib_);
            #else
               FreeLibrary((HINSTANCE)lib_);
            #endif
        }
    }


    PluginAdapter(char* path, WidgetManager* parent_widget, Layer* layer)
    {
        load_plugin(path);
        tool_ = make_tool_from_itool(iplugin_->get_tool());
        props_ = make_widget_from_iwidget(iplugin_->get_props(), parent_widget, layer);
        tool_button_ = make_button_from_ibutton(iplugin_->get_tool_button(), layer);
    }
};

/*
class PluginManager
{
    PluginAdapter** plugins_ = NULL;
    int plugins_num = 0;

    int add_plugin(PluginAdapter* plugin)
    {

    }
};*/

#endif // ADAPTER_H
