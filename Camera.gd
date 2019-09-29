extends Camera

var ofs = Vector3()

func _ready():
	ofs = translation

func _process(delta):
	translation = $"../RigidBody".translation + ofs
