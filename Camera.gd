extends Camera

var ofs = Vector3()

func _ready():
	ofs = translation

func _process(delta):
	translation = $"../KinematicBody".translation + ofs
