extends KinematicBody

var gravity = -9.8 * 3
var velocity = Vector3()
var camera
var jumps = 2

const SPEED = 10
const ACCELERATION = 8
const DE_ACCELERATION = 14

func _ready():
	camera = get_node("../Camera").get_global_transform()
	get_parent().get_parent().get_child(0).get_child(2).connect("hit_floor", self, "hit_floor_received")
	get_parent().get_parent().get_child(1).get_child(2).connect("hit_floor", self, "hit_floor_received")
	get_parent().get_parent().get_child(2).get_child(2).connect("hit_floor", self, "hit_floor_received")
	get_parent().get_parent().get_child(3).get_child(2).connect("hit_floor", self, "hit_floor_received")

func hit_floor_received():
	jumps = 2

func _process(delta):
	if translation.y < -12:
		get_tree().change_scene("res://GameOverScreen.tscn")
		
func _physics_process(delta):
	var dir = Vector3()
	
	if Input.is_action_pressed("ui_up"):
		dir -= camera.basis[2]
	if Input.is_action_pressed("ui_down"):
		dir += camera.basis[2]
	if Input.is_action_pressed("ui_left"):
		dir -= camera.basis[0]
	if Input.is_action_pressed("ui_right"):
		dir += camera.basis[0]
		
	dir.y = 0
	dir = dir.normalized()
	
	var hv = velocity
	hv.y = 0
	
	if Input.is_action_just_pressed("ui_space") and jumps > 0:
		jumps = jumps - 1
		velocity.y = 10
	elif velocity.y < -SPEED / 2 and Input.is_action_pressed("ui_glide"):
		velocity.y = -SPEED / 2
	else:
		velocity.y += delta * gravity
	
	var new_pos = dir * SPEED
	var accel = DE_ACCELERATION
	
	if dir.dot(hv) > 0:
		accel = ACCELERATION
	
	hv = hv.linear_interpolate(new_pos, accel * delta)
	
	velocity.x = hv.x
	velocity.z = hv.z
	
	velocity = move_and_slide(velocity, Vector3(0, 1, 0))
