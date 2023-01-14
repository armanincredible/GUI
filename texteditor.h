#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "widget.h"

enum TextType
{
    text,
    num,
};

enum InfoType
{
    RedColor,
    BlueColor,
    GreenColor,
};

class TextEditor : public WidgetManager
{
private:
    const char* str_ = NULL;
    double num_ = 0;
    char* data_ = NULL;
    int data_len_ = 0;
    int cur_symb_ = 0;
    InfoType info_type_ = {};

public:

    TextEditor(Point start_point, Point end_point,
               WidgetManager* parent_widget,
               int (*controller) (Button*, WidgetManager*),
               int (*paint_func) (WidgetManager*, QPainter*),
               InfoType info_type):
        WidgetManager(start_point, end_point, parent_widget, controller, paint_func),
        info_type_(info_type)
    {
        data_ = (char*) calloc (10, sizeof(char));
        data_len_ = 10;
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

    InfoType get_info_type(){return info_type_;}
    void set_info_type(InfoType type){info_type_ = type;}

    int realloc_data(int new_size);
    int delete_all_data();
};

int StandartTextEditorPaint(WidgetManager*, QPainter*);
int controller_text_editor(Button*, WidgetManager*);

#endif // TEXTEDITOR_H
