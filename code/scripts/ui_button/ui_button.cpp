#include "ui_button.h"
#include <OptionButton.hpp>

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
	auto* button = Object::cast_to<OptionButton>(get_parent()->get_node("NetworkChooseLabel"));
	auto str = button->get_item_text(button->get_selected());

	if (str == "Singleplayer") {
		// do nothing
	} else if (str == "Create Server") {
		Godot::print("create");
		get_node("Network")->call("create_server", "noviv");
	} else if (str == "Join Server") {
		Godot::print("join");
		get_node("Network")->call("connect_to_server", "noviv");
	}
	get_tree()->change_scene("res://Main.tscn");
}


