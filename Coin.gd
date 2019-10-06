extends Area

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

signal coin_touched

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Area_body_entered(body):
	get_parent().get_parent().get_node("CoinSound").play(0)
	emit_signal("coin_touched")
	get_parent().queue_free()
