#include "network_button.h"

using namespace godot;

void NetworkButton::_register_methods() {
    register_method("_ready", &NetworkButton::_ready);
}

void NetworkButton::_init() {}

void NetworkButton::_ready() {
    Input* input = Input::get_singleton();

    input->set_mouse_mode(input->MOUSE_MODE_VISIBLE);

    add_item("Singleplayer");
    add_item("Create Server");
    add_item("Join Server");
}