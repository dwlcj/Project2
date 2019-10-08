#ifndef COIN_GUI_H
#define COIN_GUI_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Control.hpp>

namespace godot {

class CoinCountGUI : public Control {
	GODOT_CLASS(CoinCountGUI, Control)

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void increment_coin_label();
};

}

#endif
