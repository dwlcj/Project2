#include "network.h"
#include <SceneTree.hpp>
#include <NetworkedMultiplayerENet.hpp>
#include <filesystem>
#include <fstream>
#include <ResourceLoader.hpp>
#include "player/player.h"
#include <Camera.hpp>

using namespace godot;

void Network::_register_methods()
{
    register_method("_init", &Network::_init, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_ready", &Network::_ready, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("create_server", &Network::create_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("connect_to_server", &Network::connect_to_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_connected_to_server", &Network::_connected_to_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_player_disconnected", &Network::_on_player_disconnected, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_player_connected", &Network::_on_player_connected, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_request_player_info", &Network::_request_player_info, GODOT_METHOD_RPC_MODE_REMOTE);
    register_method("_request_players", &Network::_request_players, GODOT_METHOD_RPC_MODE_REMOTE);
    register_method("_send_player_info", &Network::_send_player_info, GODOT_METHOD_RPC_MODE_REMOTE);
    register_method("update_position", &Network::update_position, GODOT_METHOD_RPC_MODE_DISABLED);

    register_property<Network, Dictionary>("selfData", &Network::selfData, Dictionary(), GODOT_METHOD_RPC_MODE_DISABLED);
    register_property<Network, Dictionary>("players", &Network::players, Dictionary(), GODOT_METHOD_RPC_MODE_DISABLED);
}

Network::Network()
{

}

Network::~Network()
{

}

void Network::_init()
{
    selfData["name"] = "";
    selfData["position"] = Vector3(400, 40, 0);
}

void Network::_ready()
{
    get_tree()->connect("network_peer_disconnected", this, "_on_player_disconnected");
    get_tree()->connect("network_peer_connected", this, "_on_player_connected");

    std::fstream datafile("data.txt");
    int type;
    datafile >> type;
    if (type == 1) {
        create_server("noviv");
    } else if (type == 2) {
        connect_to_server("test");
    }
}

int64_t origin_id;

void Network::create_server(String playerNickname)
{
    origin_id = 1;
    selfData["name"] = playerNickname;
    players[1] = selfData;
    NetworkedMultiplayerENet* peer = NetworkedMultiplayerENet::_new();
    peer->set_bind_ip("*");
    peer->create_server(SERVER_PORT, MAX_PLAYERS);
    get_tree()->set_network_peer(peer);
    Godot::print("created");

    get_parent()->print_tree();
    auto* player = get_parent()->get_node("Spatial");
    // player->set_name(String(peer->get_unique_id()));
    player->set_network_master(peer->get_unique_id());
}

void Network::connect_to_server(String playerNickname)
{
    selfData["name"] = playerNickname;
    get_tree()->connect("connected_to_server", this, "_connected_to_server");
    NetworkedMultiplayerENet* peer = NetworkedMultiplayerENet::_new();
    peer->create_client(SERVER_IP, SERVER_PORT);
    get_tree()->set_network_peer(peer);
    auto* player = get_parent()->get_node("Spatial");
    // player->set_name(String(peer->get_unique_id()));
    player->set_network_master(peer->get_unique_id());
}

void Network::_connected_to_server()
{
    int64_t localPlayerId = get_tree()->get_network_unique_id();
    origin_id = localPlayerId;
    players[localPlayerId] = selfData;
    rpc("_send_player_info", localPlayerId, selfData);
}

void Network::_on_player_disconnected(int64_t id)
{
    players.erase(id);
}

void Network::_on_player_connected(int64_t connectedPlayerId)
{
    std::cout << "Player connected to server" << std::endl;
    int64_t localPlayerId = get_tree()->get_network_unique_id();
    if(!get_tree()->is_network_server())
    {
        rpc_id(1, "_request_player_info", localPlayerId, connectedPlayerId);
    }
}

void Network::_request_player_info(int64_t requestFromId, int64_t playerId)
{
    if(get_tree()->is_network_server())
    {
        rpc_id(requestFromId, "_send_player_info", playerId, players[playerId]);
    }
}

void Network::_request_players(int64_t requestFromId)
{
    if(get_tree()->is_network_server())
    {
        for(int64_t peerId = 0; peerId < players.size(); peerId++)
        {
            if(peerId != requestFromId)
            {
                rpc_id(requestFromId, "_send_player_info", peerId, players[peerId]);
            }
        }
    }
}

void Network::_send_player_info(int64_t id, Dictionary info)
{
    players[id] = info;

    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    PlayerScene = resourceLoader->load("res://NewPlayer.tscn");
    Godot::print("loaded newplayer");
    godot::Player* player = static_cast<godot::Player*>(PlayerScene->instance());
    player->set_name(String(id));
    player->set_network_master(id);
    player->is_base_player = id == origin_id;
    if (id == origin_id) {
        Godot::print("adding base player");
    }
    get_parent()->add_child(player);

    auto* l0 = get_parent();
    Godot::print(">---------------");
    l0->print_tree();
    Godot::print("<---------------");
    auto* l1 = l0->get_node("Spatial");
    auto* l2 = l1->get_node("./OuterGimbal/InnerGimbal/Camera");
    auto* camera = Object::cast_to<Camera>(l2);
    camera->make_current();
}

void Network::update_position(int64_t id, Vector3 position)
{
    Dictionary playerInfo = players[id];
    playerInfo["position"] = position;
}
