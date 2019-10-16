#include "floor_area.h"
#include <iostream>
#include <stdlib.h>

using namespace godot;



void Floor_Area::_register_methods() {
	register_method("_on_Area_body_entered", &Floor_Area::_on_Area_body_entered);
	register_signal<Floor_Area>("hit_floor", "node", GODOT_VARIANT_TYPE_OBJECT);
}

void Floor_Area::_init() {

}

void Floor_Area::_on_Area_body_entered(Variant) {
	emit_signal("hit_floor");
} 
