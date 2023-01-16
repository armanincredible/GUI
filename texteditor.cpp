#include "texteditor.h"
#include "error.h"
#include <stdlib.h>

int StandartTextEditorPaint(WidgetManager* widget, QPainter* painter)
{
    START_;

    if (widget && widget->is_text_editor() && painter)
    {
        TextEditor* text_editor = (TextEditor*) widget;
        StandartWidgetPaint(text_editor, painter);

        Tool* tool = widget->get_active_tool_from_tool_manager();
        if (tool && (widget->get_work_state() == CurrentWork::ChangeActiveTool))
        {
            text_editor->delete_all_data();
            InfoType type = text_editor->get_info_type();
            int val = 0;
            if (type == InfoType::RedColor)
            {
                val = tool->get_color().r * 100;
            }
            if (type == InfoType::BlueColor)
            {
                val = tool->get_color().b * 100;
            }
            if (type == InfoType::GreenColor)
            {
                val = tool->get_color().g * 100;
            }
            if (type == InfoType::Thickness)
            {
                val = tool->get_thickness();
            }
            char data[4] = "";
            sprintf(data, "%d", val);

            if (text_editor->get_data_len() <= 4)
            {
                text_editor->realloc_data(10);
            }
            strcpy(text_editor->get_data(), data);
        }

        int x0 = text_editor->get_start_point().x;
        int y0 = text_editor->get_start_point().y;
        int height = text_editor->CoordinateSystem::heigh();
        int widtht = text_editor->CoordinateSystem::width();

        text_editor->paintCoordinateSystem(painter, true, {0, 0, 0}, {1, 1, 1});

        painter->drawText(x0, y0, widtht, height, Qt::AlignCenter, text_editor->get_data());
        END_(0);
    }
    else
    {
        END_(-1);
    }
}

static void clear_stdin()
{
    while (getchar() != '\n');
}

int TextEditor::delete_data()
{
    START_;
    if (cur_symb_ != 0)
    {
        data_[--cur_symb_] = ' ';
    }

    get_main_widget_()->set_flag(Qt::WA_OpaquePaintEvent);
    get_main_widget_()->repaint_widget();

    END_(0);
}

int TextEditor::get_num()
{
    return atoi(get_data());
}

int TextEditor::delete_all_data()
{
    START_;
    while (cur_symb_ != 0)
    {
        data_[--cur_symb_] = ' ';
    }

    END_(0);
}

int TextEditor::realloc_data(int new_size)
{
    START_;
    if (data_ == NULL)
    {
        END_(-1);
    }

    data_ = (char*) realloc(data_, new_size);
    CHECK_NULL_PTR_(data_, "realloc is failed", -1);

    END_(0);
}


int TextEditor::set_data(const int symb)
{
    START_;
    if (data_ == NULL)
    {
        END_(-1);
    }

    if (cur_symb_ > data_len_ && data_len_ > 0)
    {
        data_ = (char*) realloc(data_, data_len_ * 2);
        CHECK_NULL_PTR_(data_, "realloc is failed", -1);
    }

    data_[cur_symb_] = symb;
    cur_symb_++;

    get_main_widget_()->set_flag(Qt::WA_OpaquePaintEvent);
    get_main_widget_()->repaint_widget();

    END_(0);
}

int controller_text_editor(Button* button, WidgetManager* widget)
{
    START_;
    if (button)
    {
        button->response_(button, widget);
        END_(0);
    }
    if (widget)
    {
        if (widget->is_text_editor())
        {
            TextEditor* text_editor = (TextEditor*) widget;
            Tool* tool = widget->get_active_tool_from_tool_manager();
            if (tool)
            {
                InfoType type = text_editor->get_info_type();
                if (type == InfoType::Thickness)
                {
                    int thickness = text_editor->get_num();
                    tool->set_thickness(thickness);
                }
                else
                {
                    Color color = tool->get_color();
                    int new_color = text_editor->get_num();
                    PRINT_("new_color %d\n", new_color);

                    if (type == InfoType::RedColor)
                    {
                        color.r = (double) new_color / 100;
                    }
                    if (type == InfoType::BlueColor)
                    {
                        color.b = (double) new_color / 100;
                    }
                    if (type == InfoType::GreenColor)
                    {
                        color.g = (double) new_color / 100;
                    }
                    tool->set_color(color);
                }
            }
            END_(0);
        }
        PRINT_("going to repaint, %p\n", widget);
        (widget->get_main_widget_())->set_flag(Qt::WA_OpaquePaintEvent);
        (widget->get_main_widget_())->repaint_widget();
    }
    END_(0);
}
