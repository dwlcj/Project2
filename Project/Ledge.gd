extends Area

signal hit_ledge
signal leave_ledge

func _on_Ledge_body_entered(body):
	emit_signal("hit_ledge")

func _on_Ledge_body_exited(body):
	emit_signal("leave_ledge")
