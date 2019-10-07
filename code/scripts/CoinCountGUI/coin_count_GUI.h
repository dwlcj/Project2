#ifndef COIN_GUI_H
#define COIN_GUI_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Button.hpp>
#include <Input.hpp>

namespace godot {

class CoinCountGUI : public Control {
	GODOT_CLASS(CoinCountGUI, Control)

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void _on_button_pressed();
};

}

#endif