extends Camera

var ofs = Vector3()

func _ready():
	ofs = translation
	
func _input(event):
	if Input.is_action_pressed("ui_quit"):
		get_tree().quit()

func _process(delta):
	translation = $"../KinematicBody".translation + ofs
