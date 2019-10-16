#include "coin_count_GUI.h"

#include <Input.hpp>
#include <string>

using namespace godot;

void CoinCountGUI::_register_methods() {
	register_method("_ready", &CoinCountGUI::_ready);
	register_method("increment_coin_label", &CoinCountGUI::increment_coin_label);
}
int coin_count = 0;

void CoinCountGUI::_init() {}

void CoinCountGUI::_ready() {
	coin_count = 0;
	Input::get_singleton()->set_mouse_mode(Input::get_singleton()->MOUSE_MODE_CAPTURED);
	get_parent()->get_parent()->get_child(5)->get_child(1)->connect("coin_collected", this, "increment_coin_label");
}



void CoinCountGUI::increment_coin_label() {
	coin_count++;
	auto str = "Coins: " + std::to_string(coin_count);
	get_node("Label")->set("text", String(str.c_str()));
}
