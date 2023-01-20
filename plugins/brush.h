#ifndef BRUSH_H
#define BRUSH_H

#include "./plugin.h"

#include <iostream>

class BrushWidget : public IWidget
{
public:
    Pair<int> start_point_ = {0, 0};
    Pair<int> size_ = {0, 0};

    void set_pos(Pair<int> point) override
    {
        start_point_ = point;
    }

    void set_size(Pair<int> point)
    {
        size_ = point;
    }

    Pair<int> get_size() override
    {
        return size_;
    }

    BrushWidget(Pair<int> point, Pair<int> point_size):
        start_point_(point)
    {
        set_size(point_size);
    }

    void on_mouse_press(Pair<int> /*point*/) override {
        std::cout << "Widget::on_mouse_press(Pair<int>)\n";
    }

    void on_mouse_release(Pair<int> /*point*/) override {
        std::cout << "Widget::on_mouse_release(Pair<int>)\n";
    }

    void on_mouse_move(Pair<int> /*point*/) override {
        std::cout << "Widget::on_mouse_move(Pair<int>)\n";
    }

    void on_key_press(int /*key*/) override {
        std::cout << "Widget::on_key_press(int)\n";
    }

    void on_key_release(int /*key*/) override {
        std::cout << "Widget::on_key_release(int)\n";
    }

    void draw(unsigned int* /*screen*/, int /*width*/, int /*height*/) override {
        std::cout << "Widget::draw(unsigned int*, int, int)\n";
    }

};

class BrushTool : public ITool
{

};

#endif // BRUSH_H
