extends StaticBody

var origin
var sum = 0

func _ready():
	origin = translation
	sum = randi() % 100

func _process(delta):
	sum += delta
	translation = origin + Vector3(2 * sin(sum), cos(sum), 0)
