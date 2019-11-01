#include "coin.h"
#include <iostream>
#include <stdlib.h>
#include "player/player.h"

using namespace godot;

void Coin::_register_methods() {
	register_property<Coin, String>("next_coin_label", &Coin::next_coin_id, String("N/A"));
	register_method("_on_Area_body_entered", &Coin::_on_Area_body_entered);
	register_signal<Coin>("coin_touched", "node", GODOT_VARIANT_TYPE_OBJECT);
}

void Coin::_init() {

}

void Coin::_on_Area_body_entered(Variant bod) {
	AudioStreamPlayer3D* temp = Object::cast_to<AudioStreamPlayer3D>(get_parent()->get_parent()->get_node("CoinSound"));
	temp->play(0);
	Player* play = Object::cast_to<Player>(bod);
	if(play != nullptr)
		emit_signal("coin_touched");

	get_parent()->queue_free();
}
