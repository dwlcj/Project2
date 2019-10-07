#include "camera_gimbal.h"

using namespace godot;

void CameraGimbal::_register_methods() {
    register_method("_ready", &CameraGimbal::_ready);
    register_method("_input", &CameraGimbal::_input);
    register_method("_process", &CameraGimbal::_process);
    register_property<CameraGimbal, bool>("invert_x", &CameraGimbal::invert_x, false);
    register_property<CameraGimbal, bool>("invert_y", &CameraGimbal::invert_y, true);
    register_property<CameraGimbal, float>("mouse_sensitivity", &CameraGimbal::mouse_sensitivity, 0.005f);
}


void CameraGimbal::_init() {
    
}

void CameraGimbal::_ready() {
    ofs = get_translation();
}

void CameraGimbal::_input(InputEvent *event) {
    Input* input = Input::get_singleton();
    
    if(input->is_action_just_pressed("ui_quit"))
    {
        //GetTree()/quit();
    }

    InputEventMouseMotion* mouse_event = Object::cast_to<InputEventMouseMotion>(event);
    if(mouse_event->get_relative().x != 0)
    {
        int dir = 1 ? invert_x : -1;
        Vector3 UP = Vector3(0, 1, 0);
        float rotationAngle = dir * mouse_event->get_relative().x * mouse_sensitivity;
        rotate_object_local(UP, rotationAngle);
    }
    if(mouse_event->get_relative().y != 0)
    {
        int dir = 1 ? invert_y : -1;
        //float y_rotation;
        Spatial* inner_gimbal = Object::cast_to<Spatial>(this->get_child(0));
        Vector3 RIGHT = Vector3(1, 0, 0);
        float rotationAngle = dir * mouse_event->get_relative().y * mouse_sensitivity;
        inner_gimbal->rotate_object_local(RIGHT, rotationAngle);
    }
}

void CameraGimbal::_process(float delta)    {
    KinematicBody* player = Object::cast_to<KinematicBody>(this->get_parent()->get_child(1));

    Vector3 player_trans = player->get_translation();

    set_translation(player_trans + ofs);
}