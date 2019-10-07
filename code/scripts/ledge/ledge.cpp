#include "ledge.h"

using namespace godot;

void Ledge::_register_methods() {
	register_method("_on_Ledge_body_entered", &Ledge::_on_Ledge_body_entered);
	register_method("_on_Ledge_body_exited", &Ledge::_on_Ledge_body_exited);
	register_signal<Ledge>("hit_ledge", "node", GODOT_VARIANT_TYPE_OBJECT);
	register_signal<Ledge>("leave_ledge", "node", GODOT_VARIANT_TYPE_OBJECT);
}

void Ledge::_init() {}

void Ledge::_on_Ledge_body_entered(Variant) {
	emit_signal("hit_ledge");
}

void Ledge::_on_Ledge_body_exited(Variant) {
	emit_signal("leave_ledge");
}
