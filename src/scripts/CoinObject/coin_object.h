#ifndef COIN_OBJECT_H
#define COIN_OBJECT_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody.hpp>

namespace godot {

class CoinObject : public KinematicBody {
	GODOT_CLASS(CoinObject, KinematicBody)

public:
	static void _register_methods();

	static void _init();
    
    void _physics_process(float delta);
};

}

#endif