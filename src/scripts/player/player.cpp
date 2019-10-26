#include "player.h"

#include <Input.hpp>
#include <SceneTree.hpp>
#include <GlobalConstants.hpp>
#include <KinematicCollision.hpp>
#include <AudioStreamPlayer3D.hpp>
#include <Camera.hpp>

using namespace godot;

void Player::_register_methods() {
	register_property<Player, bool>("strafe", &Player::strafe, true);

	register_signal<Player>("coin_collected", "node", GODOT_VARIANT_TYPE_OBJECT);

	register_method("_ready", &Player::_ready);
	register_method("hit_floor_received", &Player::hit_floor_received);
	register_method("hit_ledge_received", &Player::hit_ledge_received);
	register_method("leave_ledge_received", &Player::leave_ledge_received);
	register_method("collect_coin", &Player::collect_coin);
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
}

void Player::_init() {
}

void Player::_ready() {
	camera = Object::cast_to<Camera>(get_node("../OuterGimbal/InnerGimbal/Camera"))->get_global_transform();

	get_parent()->get_parent()->get_node("StaticBody")->get_node("Spatial")->get_node("KinematicBody")->get_node("Area")->connect("coin_touched", this, "collect_coin");
	get_parent()->get_parent()->get_node("StaticBody2")->get_node("Spatial")->get_node("KinematicBody")->get_node("Area")->connect("coin_touched", this, "collect_coin");
	get_parent()->get_parent()->get_node("StaticBody3")->get_node("Spatial")->get_node("KinematicBody")->get_node("Area")->connect("coin_touched", this, "collect_coin");
	get_parent()->get_parent()->get_node("StaticBody4")->get_node("Spatial")->get_node("KinematicBody")->get_node("Area")->connect("coin_touched", this, "collect_coin");
	get_parent()->get_parent()->get_node("StaticBody6")->get_node("Spatial")->get_node("KinematicBody")->get_node("Area")->connect("coin_touched", this, "collect_coin");
	get_parent()->get_parent()->get_node("StaticBody7")->get_node("Spatial")->get_node("KinematicBody")->get_node("Area")->connect("coin_touched", this, "collect_coin");

	get_parent()->get_parent()->get_child(1)->get_child(4)->connect("hit_ledge", this, "hit_ledge_received");
	get_parent()->get_parent()->get_child(1)->get_child(4)->connect("leave_ledge", this, "leave_ledge_received");
	set_translation(Vector3(0,15,0));
}

void Player::hit_floor_received() {
	jumps = 2;
}

bool first = true;
void Player::hit_ledge_received() {
	if (first) {
		first = false;
	} else {
		in_ledge = true;
	}
}

void Player::leave_ledge_received() {
	in_ledge = false;
	gravity = -9.3 * 3;
}

void Player::collect_coin() {
	emit_signal("coin_collected");
}

void Player::_process(float delta) {
	auto* gc = GlobalConstants::get_singleton();
	auto* input = Input::get_singleton();

	if (input->is_key_pressed(gc->KEY_COMMA)) {
		Object::cast_to<AudioStreamPlayer3D>(get_parent()->get_node("AudioStreamPlayer3D"))->stop();
	} else if (input->is_key_pressed(gc->KEY_PERIOD)) {
		Object::cast_to<AudioStreamPlayer3D>(get_parent()->get_node("AudioStreamPlayer3D"))->play(0);
	} else if (input->is_key_pressed(gc->KEY_N)) {
		sfx = 1;
	} else if (input->is_key_pressed(gc->KEY_M)) {
		sfx = 0;
	}

	if (get_translation().y < -20) {
		get_tree()->change_scene("res://GameOverScreen.tscn");
	}

	if (is_on_floor()) {
		jumps = 2;
	}
}

void Player::_physics_process(float delta) {
	auto* gc = GlobalConstants::get_singleton();
	auto* input = Input::get_singleton();

	Vector3 dir;
	if (!is_on_wall()) {
		if (input->is_action_pressed("ui_up")) {
			dir -= camera.basis[2];
		}
		if (input->is_action_pressed("ui_down")) {
			dir += camera.basis[2];
		}
		if (strafe) {
			if (input->is_action_pressed("ui_left")) {
				dir -= camera.basis[0];
			}
			if (input->is_action_pressed("ui_right")) {
				dir += camera.basis[0];
			}
		} else {
			if (input->is_action_pressed("ui_left")) {
				rotate_y(delta);
			}
			if (input->is_action_pressed("ui_right")) {
				rotate_y(-delta);
			}
		}
	}

	dir.y = 0;
	dir = dir.rotated(Vector3(0, 1, 0), get_rotation().y).normalized();

	auto hv = velocity;
	hv.y = 0;

	if (input->is_action_just_pressed("ui_space") && jumps > 0) {
		if (sfx > 0) {
			Object::cast_to<AudioStreamPlayer3D>(get_parent()->get_node("Jump"))->play(0);
		}
		jumps--;
		velocity.y = 10;
	} else if (velocity.y < -SPEED / 2 && input->is_action_pressed("ui_glide")) {
		velocity.y = -SPEED / 2;
	} else {
		velocity.y += delta * gravity;
	}

	auto new_pos = dir * SPEED;
	auto accel = DE_ACCELERATION;

	if (dir.dot(hv) > 0) {
		accel = ACCELERATION;
	}

	hv = hv.linear_interpolate(new_pos, accel * delta);

	velocity.x = hv.x;
	velocity.z = hv.z;

	if (input->is_action_pressed("ui_shift") && !input->is_action_pressed("ui_space")) {
		if (in_ledge) {
			gravity = 0;
			velocity = Vector3();
			jumps = 2;
		} else {
			gravity = -9.8 * 3;
			auto kc = move_and_collide(velocity, true, true, true);
			auto collided = kc.is_valid();
			if (!collided && is_on_floor()) {
				velocity = Vector3(0, 0, 0);
			} else {
				velocity = move_and_slide(velocity, Vector3(0, 1, 0));
			}
			prev_collided = collided;
		}
	} else {
		auto kc = move_and_collide(velocity, true, true, true);
		if (kc.is_valid()) {
			velocity = move_and_slide(velocity, Vector3(0, 1, 0), false, 4, 0.35);
		} else {
			velocity = move_and_slide(velocity, Vector3(0, 1, 0));
		}
	}
}

void Player::impulse(Vector3 dir) {
	velocity = velocity.cross(dir);
}
