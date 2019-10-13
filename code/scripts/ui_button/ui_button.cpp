#include "ui_button.h"

using namespace godot;

void UIButton::_register_methods() {
    register_method("_ready", &UIButton::_ready);
    register_method("_on_Button_pressed", &UIButton::_on_Button_pressed);
}

void UIButton::_init() {}

void UIButton::_ready() {
    Input* input = Input::get_singleton();

    input->set_mouse_mode(input->MOUSE_MODE_VISIBLE);
}

void UIButton::_on_Button_pressed() {
    if(get_text().nocasecmp_to("PLAY") == 0)
    {
        get_tree()->change_scene("res://Main.tscn");
    }
    else if(get_text().nocasecmp_to("Create Server") == 0)
    {
        get_parent()->get_node("StatusLabel")->set("text", "Multiplayer Host");
    }
    else if(get_text().nocasecmp_to("Join Server") == 0)
    {
        get_parent()->get_node("StatusLabel")->set("text", "Multiplayer Client");
    }
    else if(get_text().nocasecmp_to("Leave Server") == 0)
    {
        get_parent()->get_node("StatusLabel")->set("text", "Singleplayer");
    }   


    
}


