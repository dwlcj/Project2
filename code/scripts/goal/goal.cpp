#include "goal.h"
#include <iostream>
#include <stdlib.h>

using namespace godot;



void Goal::_register_methods() {
	register_method("_on_Area_body_entered", &Goal::_on_Area_body_entered);
}

void Goal::_init() {

}

void Goal::_on_Area_body_entered(Variant) {
	get_tree()->change_scene("res://WinScreen.tscn");
} 
