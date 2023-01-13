#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "widget.h"

enum TextType
{
    text,
    num,
};

class TextEditor : public WidgetManager
{
private:
    const char* str_ = NULL;
    double num_ = 0;
    char* data_ = NULL;
    int data_len_ = 0;
    int cur_symb_ = 0;

public:

    TextEditor(Point start_point, Point end_point,
               WidgetManager* parent_widget,
               int (*controller) (Button*, WidgetManager*, void*),
               int (*paint_func) (WidgetManager*, QPainter*, void*)):
        WidgetManager(start_point, end_point, parent_widget, controller, paint_func)
    {
        data_ = (char*) calloc (10, sizeof(char));
        data_len_ = 10;
        data_[0] = 'a';
        set_is_text_editor(true);
    }

    void set_str (const char* str){str_ = str;}
    void set_num (const double num){num_ = num;}
    int set_data(const int symb);
    int delete_data();
    int init_data ();

    char* get_data(){return data_;}
    double get_num(){return num_;}

    int get_data_len(){return data_len_;}
    void set_data_len(int len){data_len_ = len;}

    int get_cur_symb_index(){return cur_symb_;}
    void set_cur_symb_index(int index){cur_symb_ = index;}
};

int StandartTextEditorPaint(WidgetManager*, QPainter*, void*);
int controller_text_editor(Button*, WidgetManager*, void*);

#endif // TEXTEDITOR_H
