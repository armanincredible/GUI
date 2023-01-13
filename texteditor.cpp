#include "texteditor.h"
#include "error.h"

int StandartTextEditorPaint(WidgetManager* widget, QPainter* painter, void* text_editor_void)
{
    START_;

    TextEditor* text_editor = (TextEditor*) widget;
    StandartWidgetPaint(text_editor, painter, NULL);


    int x0 = text_editor->get_start_point().x;
    int y0 = text_editor->get_start_point().y;
    int height = text_editor->CoordinateSystem::heigh();
    int widtht = text_editor->CoordinateSystem::width();


    painter->drawText(x0, y0, widtht, height, Qt::AlignCenter, text_editor->get_data());

    /*if (text_editor->get_str())
    {
        painter->drawText(x0, y0, widtht, height, Qt::AlignCenter, text_editor->get_str());
    }
    else if (text_editor->get_num())
    {
        int num_digits = text_editor->get_num()/10 + 1;
        char* str = (char*) calloc (num_digits, sizeof(char));// its must be changed cause we can calloc in init function once time
        CHECK_NULL_PTR_(str, "calloc is failed", -1);

        sprintf(str, "%d", (int)text_editor->get_num());
        painter->drawText(x0, y0, widtht, height, Qt::AlignCenter, str);

        free(str);
    }*/

    END_(0);
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

