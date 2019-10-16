#ifndef NET_BUTTON_H
#define NET_BUTTON_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <OptionButton.hpp>
#include <Input.hpp>

namespace godot {

class NetworkButton : public OptionButton {
	GODOT_CLASS(NetworkButton, OptionButton)

public:
	static void _register_methods();

	static void _init();

	void _ready();
};

}

#endif
