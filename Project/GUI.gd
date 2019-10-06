extends Control

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	get_parent().get_parent().get_child(5).get_child(1).connect("coin_collected", self, "increment_coin_label")

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func increment_coin_label(coins):
	$Label.text = "Coins: " + str(coins)
