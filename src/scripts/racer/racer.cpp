#include "racer.h"

#include <math.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>

using namespace godot;

void Racer::_register_methods() {
	register_method("_ready", &Racer::_ready);
	register_method("_process", &Racer::_process);
	register_method("_physics_process", &Racer::_physics_process);
}

void Racer::_init() {}

void Racer::_ready() {}

void Racer::_physics_process(float delta) {}

void Racer::_process(float delta) {}
