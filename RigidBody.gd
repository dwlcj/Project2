extends RigidBody

func _input(event):
	if event.is_action_pressed("ui_up"):
		apply_central_impulse(Vector3(0, 0, 5))
	elif event.is_action_pressed("ui_down"):
		apply_central_impulse(Vector3(0, 0, -5))
	elif event.is_action_pressed("ui_right"):
		apply_central_impulse(Vector3(-5, 0, 0))
	elif event.is_action_pressed("ui_left"):
		apply_central_impulse(Vector3(5, 0, 0))
	elif event.is_action_pressed("ui_space"):
		apply_central_impulse(Vector3(0, 10, 0))