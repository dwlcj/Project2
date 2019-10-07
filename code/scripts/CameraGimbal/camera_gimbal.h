#ifndef CAMERA_GIMBAL_H
#define CAMERA_GIMBAL_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Spatial.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <InputEventMouseMotion.hpp>
#include <KinematicBody.hpp>

namespace godot {

class CameraGimbal : public Spatial {
	GODOT_CLASS(CameraGimbal, Spatial)

private:
    Vector3 ofs;
    bool invert_y;
    bool invert_x;
    float mouse_sensitivity;

public:
	static void _register_methods();

	static void _init();

    void _ready();

    void _input(InputEvent *event);

    void _process(float delta);
};

}

#endif