#include "enemy.h"

#include "player/player.h"

#include <math.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>
#include <Particles.hpp>

using namespace godot;

void Enemy::_register_methods() {
	register_method("_ready", &Enemy::_ready);
	register_method("_process", &Enemy::_process);
	register_method("_physics_process", &Enemy::_physics_process);
}

void Enemy::_init() {}

void Enemy::_ready() {
	Object::cast_to<Particles>(get_node("Particles"))->set_emitting(false);
}

Vector3 direction_to(const Vector3& a, const Vector3& b) {
	Vector3 ret(b.x - a.x, b.y-a.y, b.z - a.z);
	ret.normalize();
	return ret;
}

void Enemy::_physics_process(float delta) {
	Vector3 myT = get_global_transform().origin;
	Vector3 playerT = Object::cast_to<KinematicBody>(get_parent()->get_parent()->get_node("Spatial")->get_node("KinematicBody"))->get_global_transform().origin;
	float distance = myT.distance_to(playerT);

	bool jumping = Input::get_singleton()->is_action_just_pressed("ui_space");
	if(playerT.z > -8){
		Object::cast_to<Particles>(get_node("Particles"))->set_emitting(true);
		velocity.x = 0;
		velocity.z = 0;
		if(velocity.y == 0)
			velocity.y = 10;
		else
			velocity.y += delta * (-9.8 * 3);
		auto xe = myT.x;
		auto ze = myT.z;
		auto xp = playerT.x;
		auto zp = playerT.z;
		double angle = atan2(xe - xp, ze - zp);
		set_rotation(Vector3(0, angle, 0));
	}
	else if (distance < 15) {
		auto xe = myT.x;
		auto ze = myT.z;
		auto xp = playerT.x;
		auto zp = playerT.z;

		double angle = atan2(xe - xp, ze - zp);
		set_rotation(Vector3(0, angle, 0));

		auto dir = direction_to(myT, playerT) * 10;
		/*if (jumping) {
			velocity.y = 10;
		}*/
		velocity.x = dir.x;
		velocity.z = dir.z;

		if (is_on_wall() && distance < 5) {
			Object::cast_to<Player>(get_parent()->get_parent()->get_node("Spatial")->get_node("KinematicBody"))->impulse(dir);
		}
	} else {
		if(velocity.x == 0){
			velocity.x = 5;
		}
			
		auto kc = move_and_collide(velocity, true, true, true);
		auto collided = kc.is_valid();
		if(myT.x > 10 || myT.x < -10){
			velocity = -velocity;
		}
	}
	if (!jumping) {
		velocity.y += delta * (-9.8 * 3);
	}
	velocity = move_and_slide(velocity, Vector3(0, 1, 0));
}

void Enemy::_process(float delta) {}
