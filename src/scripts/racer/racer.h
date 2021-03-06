#ifndef RACER_H
#define RACER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody.hpp>

namespace godot {

class Racer : public KinematicBody {
	GODOT_CLASS(Racer, KinematicBody)

private:
	Vector3 velocity;
	size_t curr_waypoint = 0;
	bool jumping = false;
	bool fleeing = false;

	Node* get_current_waypoint();

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void _process(float);
	void _physics_process(float);
};

}

#endif
