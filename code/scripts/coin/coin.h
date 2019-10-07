#ifndef COIN_H
#define COIN_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <SceneTree.hpp>
#include <Area.hpp>
#include <AudioStreamPlayer3D.hpp>


namespace godot {

	class Coin : public Area {
		GODOT_CLASS(Coin, Area)

	public:
		static void _register_methods();
		static void _init();
		void _on_Area_body_entered(Variant);
		 

	};

	

}

#endif