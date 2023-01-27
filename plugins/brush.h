#ifndef BRUSH_H
#define BRUSH_H

#include "../plugin.h"
//#include <QPixmap>
#include "QImage"

#include <iostream>
#include "string.h"

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

class BrushButton : public IPushButton
{
public:
    Pair<int> start_point_ = {0, 0};
    Pair<int> size_ = {0, 0};
    const char* image_path_ = NULL;
    bool isContains_ = false;


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

    BrushButton(Pair<int> point, Pair<int> point_size):
        start_point_(point)
    {
        set_size(point_size);
    }

    void contains(Pair<int> point) override {
        if (start_point_.x <= (unsigned) point.x && (unsigned) point.x <= (start_point_.x + size_.x)) {
            if (start_point_.y <= (unsigned) point.y && (unsigned) point.y <= (start_point_.y + size_.y)) {
                isContains_ = true;
                return;
            }
        }

        isContains_ = false;
    }

    Pair<int> get_pos() override {
        std::cout << "ToolButton::get_pos()\n";

        return Pair<int>{(int) start_point_.x, (int) start_point_.y};
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

    void draw(unsigned int* screen, int width, int height) override {
        std::cout << "Widget::draw(unsigned int*, int, int)\n";
        //QPixmap pix (image_path_);
        //pix.
        fprintf (stderr, "in draw\n");
        if (image_path_)
        {
            fprintf (stderr, "in draw image\n");
            QImage image(image_path_);
            if (image.isNull())
            {
                fprintf (stderr, "image is null\n");
                return;
            }
            image.scaledToHeight(height);
            fprintf (stderr, "in draw1\n");
            image.scaledToWidth(width);
            //image.copy()
            //fprintf (stderr, "%d in bytes", width * 3 * height);
            memcpy(screen, image.bits(), width * 3 * height);
            //memcpy(screen, image.bits(), width * 3 * height);
            fprintf (stderr, "in draw2\n");
        }
        else
        {
            unsigned x_ = start_point_.x;
            unsigned weight_ = size_.x;
            unsigned hight_ = size_.y;
            unsigned y_ = start_point_.y;
            unsigned outlineThickness_ = 3;
            for (int j = 0; j < height; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    //fprintf (stderr, "iaaaaa\n");
                    screen[j * 3 * width + i * 3] = 250;
                    screen[j * 3 * width + i * 3 + 1] = 250;
                    screen[j * 3 * width + i * 3 + 2] = 250;
                }
            }

            /*for (unsigned j = (y_ - outlineThickness_); j < y_; j++) {
                for (unsigned i = 3 * x_; i < 3 * (x_ + weight_) - (3 - 1); i += 3) {
                    screen[j * 3 * (unsigned) width + i] =
                    screen[j * 3 * (unsigned) width + i + 1] = 0;
                    screen[j * 3 * (unsigned) width + i + 2] = 255;
                }
            }

            //     --------------------
            //     |                  |
            //     |                  |
            //     |                  |
            // (*) --------------------
            for (unsigned j = (y_ + hight_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 3 * x_; i < 3 * (x_ + weight_) - (3 - 1); i += 3) {
                    screen[j * 3 * (unsigned) width + i] =
                    screen[j * 3 * (unsigned) width + i + 1] = 0;
                    screen[j * 3 * (unsigned) width + i + 2] = 255;
                }
            }

            // (*)
            //  --------------------
            //  |                  |
            //  |                  |
            //  |                  |
            //  --------------------
            for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 3 * (x_ - outlineThickness_); i < 3 * (x_) - (3 - 1); i += 3) {
                    screen[j * 3 * (unsigned) width + i] =
                    screen[j * 3 * (unsigned) width + i + 1] = 0;
                    screen[j * 3 * (unsigned) width + i + 2] = 255;
                }
            }

            //                    (*)
            //  --------------------
            //  |                  |
            //  |                  |
            //  |                  |
            //  --------------------
            for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 3 * (x_ + weight_); i < 3 * (x_ + weight_ + outlineThickness_) - (3 - 1); i += 3) {
                    screen[j * 3 * (unsigned) width + i] =
                    screen[j * 3 * (unsigned) width + i + 1] = 0;
                    screen[j * 3 * (unsigned) width + i + 2] = 255;
                }
            }*/

        }
    }
    void set_signal(void (* /*signal*/)(IPushButton*)) override {
    }

};



#endif // BRUSH_H
