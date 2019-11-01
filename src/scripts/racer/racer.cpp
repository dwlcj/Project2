#include "racer.h"

#include <math.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>

#include <optional>

using namespace godot;

Node* Racer::get_current_waypoint() {
	static size_t curr_waypoint = 0;
	for (size_t i = curr_waypoint; i < 6; i++) {
		auto str = String("StaticBody") + (i + '0');
		Node* node = get_parent()->get_parent()->get_node(NodePath(str))->get_node("Spatial");
		if (node->has_node("KinematicBody")) {
			curr_waypoint = i;
			return node->get_node("KinematicBody");
		}
	}
	return nullptr;
}

void Racer::_register_methods() {
	register_method("_ready", &Racer::_ready);
	register_method("_process", &Racer::_process);
	register_method("_physics_process", &Racer::_physics_process);
}

void Racer::_init() {}

void Racer::_ready() {}

void Racer::_physics_process(float delta) {
	auto* waypoint = get_current_waypoint();
	if (!waypoint) {
		return;
	}

	Vector3 myT = get_global_transform().origin;
	Vector3 waypointT = Object::cast_to<KinematicBody>(waypoint)->get_global_transform().origin;

	auto xe = myT.x;
	auto ze = myT.z;
	auto xp = waypointT.x;
	auto zp = waypointT.z;
	double angle = atan2(xp - xe, zp - ze);
	set_rotation(Vector3(0, angle, 0));

	Vector3 dir(waypointT.x - myT.x, waypointT.y - myT.y, waypointT.z - myT.z);
	dir = dir.normalized() * 10;
	velocity.x = dir.x;
	velocity.y += delta * (-9.8 * 3);
	velocity.z = dir.z;

	if (jumping) {
		if (velocity.y < 0) {
			velocity.y = 10;
			jumping = false;
		}
	} else {
		auto kc = move_and_collide(velocity * delta, true, true, true);
		if ((!kc.is_valid() && is_on_floor()) || is_on_wall()) {
			jumping = true;
			velocity.y = 10;
		}
	}

	velocity = move_and_slide(velocity, Vector3(0, 1, 0), false, 4, 0.4);
}

void Racer::_process(float delta) {}
