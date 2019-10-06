#ifndef BUTTON_H
#define BUTTON_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Button.hpp>

namespace godot {

class UIButton : public Button {
	GODOT_CLASS(UIButton, Button)

public:
	static void _register_methods();

	static void _init();
};

}

#endif
