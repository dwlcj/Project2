#include "ui_button.h"
#include <OptionButton.hpp>
#include <fstream>

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
		std::ofstream file("data.txt");
		file << "1";
		Godot::print("singleplayer");
	} else if (str == "Create Server") {
		std::ofstream file("data.txt");
		file << "1";
		Godot::print("create");
	} else if (str == "Join Server") {
		std::ofstream file("data.txt");
		file << "2";
		Godot::print("join");
	}
	get_tree()->change_scene("res://Main.tscn");
}


