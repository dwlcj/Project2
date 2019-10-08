#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody.hpp>

namespace godot {

class Player : public KinematicBody {
	GODOT_CLASS(Player, KinematicBody)

private:
	static const int SPEED = 10;
	static const int ACCELERATION = 8;
	static const int DE_ACCELERATION = 14;

	bool strafe = true;

	double gravity = -9.8 * 3;
	Vector3 velocity;
	Transform camera;
	int jumps = 2;
	bool prev_collided = false;
	bool in_ledge = false;
	int sfx = 1;

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void hit_floor_received();
	void hit_ledge_received();
	void leave_ledge_received();
	void collect_coin();
	void _process(float);
	void _physics_process(float);
};

}

#endif
