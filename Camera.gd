extends Camera

var ofs = Vector3()

func _ready():
	ofs = translation
	print(ofs)

func _process(delta):
	translation = $"../RigidBody".translation + ofs
