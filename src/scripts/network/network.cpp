#include "network.h"

#include <SceneTree.hpp>
#include <NetworkedMultiplayerENet.hpp>

using namespace godot;

void Network::_register_methods() {
    register_method("_ready", &Network::_ready);


    register_method("create_server", &Network::create_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("connect_to_server", &Network::connect_to_server, GODOT_METHOD_RPC_MODE_DISABLED);

    register_method("_on_player_connected", &Network::_on_player_connected);
    register_method("_on_player_disconnected", &Network::_on_player_connected);
    register_method("_connected_to_server", &Network::_connected_to_server);

    register_method("_send_player_info", &Network::_send_player_info, GODOT_METHOD_RPC_MODE_REMOTE);
}

void Network::_init() {}

void Network::_ready() {
	get_tree()->connect("network_peer_connected", this, "_on_player_connected");
	get_tree()->connect("network_peer_disconnected", this, "_on_player_disconnected");
    create_server("test");
}

void Network::create_server(String username) {
	selfData["username"] = username;
	players[1] = selfData;
	NetworkedMultiplayerENet* peer = NetworkedMultiplayerENet::_new();
	peer->set_bind_ip("127.0.0.1");
	peer->create_server(13123, 3);
	get_tree()->set_network_peer(peer);
    Godot::print("created server");
}

void Network::connect_to_server(String username) {
    selfData["username"] = username;
    get_tree()->connect("connected_to_server", this, "_connected_to_server");
    NetworkedMultiplayerENet* peer = NetworkedMultiplayerENet::_new();
    peer->create_client("127.0.0.1", 13123);
    get_tree()->set_network_peer(peer);
}

void Network::_on_player_connected(int64_t id) {
	Godot::print(String(id));
}

void Network::_on_player_disconnected(int64_t id) {
	Godot::print(String(id));
}

void Network::_connected_to_server() {
    int64_t localPlayerId = get_tree()->get_network_unique_id();
    players[localPlayerId] = selfData;
    rpc("_send_player_info", localPlayerId, selfData);
}

void Network::_send_player_info(int64_t id, Dictionary dict) {
    players[id] = dict;

	Godot::print("send_player_info");

/*    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    PlayerScene = resourceLoader->load("res://player/Player.tscn");
    godot::Player* player = static_cast<godot::Player*>(PlayerScene->instance());
    player->set_name(String(id));
    player->set_network_master(id);
    get_node("/root/Game")->add_child(player);
    player->init(info["name"], info["position"], true);*/
}
