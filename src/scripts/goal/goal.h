#ifndef GOAL_H
#define GOAL_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <SceneTree.hpp>
#include <Area.hpp>


namespace godot {

	class Goal : public Area {
		GODOT_CLASS(Goal, Area)

	public:
		static void _register_methods();
		static void _init();
		void _on_Area_body_entered(Variant);
		void end_game();
		 

	};

	

}

#endif