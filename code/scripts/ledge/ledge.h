#ifndef LEDGE_H
#define LEDGE_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Area.hpp>

namespace godot {

class Ledge : public Area {
	GODOT_CLASS(Ledge, Area)

public:
	static void _register_methods();

	static void _init();

	void _on_Ledge_body_entered(Variant);
	void _on_Ledge_body_exited(Variant);
};

}

#endif
