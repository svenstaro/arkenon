#ifndef _GUI_FRAME_HPP
#define _GUI_FRAME_HPP

#include "gui/Widget.hpp"

class Frame : public Widget {
    void render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader_program);
};

#endif
