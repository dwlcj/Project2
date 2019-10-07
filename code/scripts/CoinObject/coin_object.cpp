#include "coin_object.h"

using namespace godot;

void CoinObject::_register_methods() {
    register_method("_physics_process", &CoinObject::_physics_process);
}

void CoinObject::_init() {}

void CoinObject::_physics_process(float delta) {
    rotate_y(delta);
}