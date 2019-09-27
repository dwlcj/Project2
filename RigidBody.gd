extends RigidBody

func _input(event):
	if event is InputEventKey:
		if event.scancode == KEY_SPACE:
			var vel = get_linear_velocity()
			vel.y = 5
			set_linear_velocity(vel)
		elif event.scancode == KEY_W:
			var vel = get_linear_velocity()
			vel.x = 3
			set_linear_velocity(vel)