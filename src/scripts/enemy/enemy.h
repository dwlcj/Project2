#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody.hpp>

namespace godot {

class Enemy : public KinematicBody {
	GODOT_CLASS(Enemy, KinematicBody)

private:
	Vector3 velocity;

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void _process(float);
	void _physics_process(float);
};

}

#endif
