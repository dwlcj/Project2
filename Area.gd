extends Area

signal hit_floor

func _on_Area_body_entered(body):
	emit_signal("hit_floor")
