#include "camera_gimbal.h"

using namespace godot;

void CameraGimbal::_register_methods() {
    register_method("_ready", &CameraGimbal::_ready);
    register_method("_input", &CameraGimbal::_input);
    register_method("_process", &CameraGimbal::_process);
    register_property<CameraGimbal, bool>("invert_x", &CameraGimbal::invert_x, false);
    register_property<CameraGimbal, bool>("invert_y", &CameraGimbal::invert_y, false);
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
        get_tree()->quit();
    }

    InputEventMouseMotion* mouse_event = Object::cast_to<InputEventMouseMotion>(event);
    if(mouse_event != NULL)
    {
        if(mouse_event->get_relative().x != 0)
        {
            
            int dir = invert_x ? 1 : -1;
            Vector3 UP = Vector3(0, 1, 0);
            float rotationAngle = dir * mouse_event->get_relative().x * 0.005f;
            rotate_object_local(UP, (real_t)rotationAngle);
        }
        if(mouse_event->get_relative().y != 0)
        {
            int dir = invert_y ? 1 : -1;
            //float y_rotation;
            //Godot::print("relative y is not 0");
            Spatial* inner_gimbal = Object::cast_to<Spatial>(this->get_child(0));
            Vector3 RIGHT = Vector3(1, 0, 0);
            real_t rotationAngle = dir * mouse_event->get_relative().y * 0.005f;
            //Godot::print(mouse_event->get_relative());
            Vector2 test = Vector2(dir, mouse_sensitivity);
            //Godot::print(test);
            inner_gimbal->rotate_object_local(RIGHT, rotationAngle);
        }
    }
    
}

void CameraGimbal::_process(float delta)    {
    KinematicBody* player = Object::cast_to<KinematicBody>(this->get_parent()->get_child(1));

    Vector3 player_trans = player->get_translation();

    set_translation(player_trans + ofs);
}
