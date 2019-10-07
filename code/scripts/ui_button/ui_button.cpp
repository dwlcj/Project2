#include "ui_button.h"

using namespace godot;

void UIButton::_register_methods() {
    register_method("_ready", &UIButton::_ready);
    register_method("_on_button_pressed", &UIButton::_on_button_pressed);
}

void UIButton::_init() {}

void UIButton::_ready() {
    Input* input = Input::get_singleton();

    input->set_mouse_mode(input->MOUSE_MODE_VISIBLE);
}

void UIButton::_on_button_pressed() {
    this->get_tree()->change_scene("res:://Main.tscn");
}


