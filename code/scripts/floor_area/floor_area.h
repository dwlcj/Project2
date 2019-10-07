#ifndef FLOOR_AREA_H
#define FLOOR_AREA_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Area.hpp>


namespace godot {

	class Floor_Area : public Area {
		GODOT_CLASS(Floor_Area, Area)

	public:
		static void _register_methods();
		static void _init();
		void _on_Area_body_entered(Variant);
		 

	};

	

}

#endif