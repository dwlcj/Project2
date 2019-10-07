#include "ui_button/ui_button.h"
#include "CameraGimbal/camera_gimbal.h"
#include "CoinObject/coin_object.h"
#include "ledge/ledge.h"
#include "floor_area/floor_area.h"
#include "player/player.h"
#include "goal/goal.h"
#include "coin/coin.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);
	godot::register_class<godot::UIButton>();
	godot::register_class<godot::CameraGimbal>();
	godot::register_class<godot::CoinObject>();
	godot::register_class<godot::Ledge>();
	godot::register_class<godot::Floor_Area>();
	godot::register_class<godot::Player>();
	godot::register_class<godot::Goal>();
	godot::register_class<godot::Coin>();
}
