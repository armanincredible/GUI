#ifndef TOOL_H
#define TOOL_H
#include "vectors.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>

class Tool
{
private:
    Point last_click_ = {};
public:
    int (*activity_)(Tool*, QPainter*, Point);

    Tool(int (*activity) (Tool*, QPainter*, Point)):
        activity_(activity)
    {};

    Point get_last_click (){return last_click_;}
    void set_last_click (Point click){last_click_ = click;}
};

class ToolManager
{
private:
    Tool* cur_work_tool_ = NULL;
    Tool** tools_ = NULL;
    size_t tools_num_ = 0;
public:
    int add_tool (Tool* tool)
    {
        if (!tools_num_ && tools_)
        {
            printf ("ERROR %d\n", __LINE__);
        }
        tools_num_++;
        tools_ = (Tool**) realloc (tools_, tools_num_ * sizeof(Tool*));
        if (tools_ == NULL)
        {
            return -1;
        }
        tools_[tools_num_ - 1] = tool;
        return 0;
    }
    Tool* get_active_tool (){return cur_work_tool_;}
    void set_active_tool (Tool* tool){cur_work_tool_ = tool;}
};

int paint_dot (Tool*, QPainter*, Point);

#endif // TOOL_H
