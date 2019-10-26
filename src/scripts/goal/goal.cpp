#include "goal.h"
#include <iostream>
#include <stdlib.h>

using namespace godot;



void Goal::_register_methods() {
	register_method("_on_Area_body_entered", &Goal::_on_Area_body_entered);
	register_method("end_game", &Goal::end_game, GODOT_METHOD_RPC_MODE_REMOTE);
}

void Goal::_init() {

}

void Goal::_on_Area_body_entered(Variant) {
	rpc("end_game");
	get_tree()->change_scene("res://WinScreen.tscn");
}

void Goal::end_game() {
	get_tree()->change_scene("res://WinScreen.tscn");
}
