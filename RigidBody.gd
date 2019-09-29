extends RigidBody

var x = 0
var y = 0
var z = 0

func _input(event):
	if event.is_action_pressed("ui_up"):
		z = 3
	elif event.is_action_released("ui_up"):
		z = 0
	elif event.is_action_pressed("ui_down"):
		z = -3
	elif event.is_action_released("ui_down"):
		z = 0
	elif event.is_action_pressed("ui_right"):
		x = -3
	elif event.is_action_released("ui_right"):
		x = 0
	elif event.is_action_pressed("ui_left"):
		x = 3
	elif event.is_action_released("ui_left"):
		x = 0
	elif event.is_action_pressed("ui_space"):
		y = 5
	elif event.is_action_released("ui_space"):
		y = 0
		
func _process(delta):
	if(translation.y < -12):
		get_tree().change_scene("res://GameOverScreen.tscn")
	if x != 0 or y != 0 or z != 0:
		var vel = get_linear_velocity()
		if x != 0:
			vel.x = x
		if y != 0:
			vel.y = y
		if z != 0:
			vel.z = z
		set_linear_velocity(vel)