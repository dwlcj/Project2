extends Spatial

var ofs = Vector3()
var invert_y = true
var invert_x = false
var mouse_control = true
var mouse_sensitivity = 0.005

func _ready():
	ofs = translation
	
func _input(event):
	if Input.is_action_pressed("ui_quit"):
		get_tree().quit()
		
	if mouse_control and event is InputEventMouseMotion:
		if event.relative.x != 0:
			var dir = 1 if invert_x else -1
			rotate_object_local(Vector3.UP, dir * event.relative.x * mouse_sensitivity)
		if event.relative.y != 0:
			var dir = 1 if invert_y else -1
			var y_rotation = clamp(event.relative.y, -30, 30)
			$InnerGimbal.rotate_object_local(Vector3.RIGHT, dir * y_rotation * mouse_sensitivity)


func _process(delta):
	translation = $"../KinematicBody".translation + ofs
