#ifndef BUTTON_H
#define BUTTON_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Button.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>

namespace godot {

class UIButton : public Button {
	GODOT_CLASS(UIButton, Button)

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void _on_Button_pressed();
};

}

#endif
