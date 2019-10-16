#ifndef NETWORK_H
#define NETWORK_H

#include <Node.hpp>
#include <Godot.hpp>

namespace godot {

class Network : public Node {
	GODOT_CLASS(Network, Node)

	Dictionary selfData;
	Dictionary players;

public:
	static void _register_methods();

	static void _init();

	void _ready();

	void create_server(String);
	void connect_to_server(String);

	void _on_player_connected(int64_t id);
	void _on_player_disconnected(int64_t id);
	void _connected_to_server();
	void _send_player_info(int64_t, Dictionary);
};

}

#endif
