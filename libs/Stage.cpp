/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Stage.h"
#include <fstream>
#include "Exception.h"
#include "GameStateMsg.h"
#include "Point.h"
#include "yaml-cpp/yaml.h"

/**
 * @brief Parses a Point from a YAML node.
 *
 * @param node Node containing the data.
 * @return Point.
 */
static Math::Point<float> _parsePoint(YAML::Node &node) {
    if (!node.IsSequence() || node.size() != 2) {
        throw Exception{"Invalid stage: Point should be a sequence of 2 floats"};
    }

    float posX = node[0].as<float>();
    float posY = node[1].as<float>();
    return Math::Point<float>{posX, posY};
}

/**
 * @brief Parses a worm's data from a YAML node.
 *
 * @param health Worm's health.
 * @param node Node containing the data.
 * @return Worm data.
 */
static Worms::WormData _parseWorm(uint16_t health, YAML::Node &node) {
    if (node.Type() != YAML::NodeType::Map) {
        throw Exception{"Invalid stage: worm data expected as Map"};
    }

    if (!node["position"]) {
        throw Exception{"Invalid stage: worm requires 'position'"};
    }

    YAML::Node positionNode = node["position"];
    return Worms::WormData{health, _parsePoint(positionNode)};
}

/**
 * @brief Parses a girder's data from a YAML node.
 *
 * @param node Node containing the data.
 * @return Girder data.
 */
static Worms::GirderData _parseGirder(YAML::Node &node) {
    if (node.Type() != YAML::NodeType::Map) {
        throw Exception{"Invalid stage: girder data expected as Map"};
    }

    if (!node["position"]) {
        throw Exception{"Invalid stage: girder requires 'position'"};
    }
    if (!node["angle"]) {
        throw Exception{"Invalid stage: girder requires 'angle'"};
    }

    YAML::Node positionNode = node["position"];
    Math::Point<float> position = _parsePoint(positionNode);

    float angle = node["angle"].as<float>();
    float length = node["length"].as<float>();

    return Worms::GirderData{length, 1.42f, angle, position};
}

/**
 * @brief Creates a Stage object populating it from the contents of the given file.
 *
 * @param filename Name of the file with the Stage data.
 * @return Stage.
 */
Worms::Stage Worms::Stage::fromFile(const std::string &filename) {
    YAML::Node data = YAML::LoadFile(filename);

    if (!data["wormsHealth"]) {
        throw Exception{"Invalid stage: expected float 'wormsHealth'"};
    }

    uint16_t wormsHealth = data["wormsHealth"].as<unsigned short>();

    Stage stage;
    if (!data["width"] || !data["height"]) {
        throw Exception{"Invalid stage: expected stage 'width' and 'height'"};
    }
    stage.width = data["width"].as<float>();
    stage.height = data["height"].as<float>();

    if (!data["worms"] || !data["worms"].IsSequence()) {
        throw Exception{"Invalid stage: expected a sequence of 'worms'"};
    }

    if (!data["numPlayers"]) {
        throw Exception{"Invalid stage: expected integer 'numPlayers'"};
    }
    stage.numPlayers = data["numPlayers"].as<int>();

    /* loads the worms */
    for (std::size_t i = 0; i < data["worms"].size(); i++) {
        YAML::Node wormNode = data["worms"][i];
        stage.players.push_back(_parseWorm(wormsHealth, wormNode));
    }

    /* loads the girders */
    if (!data["girders"] || !data["girders"].IsSequence()) {
        throw Exception{"Invalid stage: expected a sequence of 'girders'"};
    }
    for (std::size_t i = 0; i < data["girders"].size(); i++) {
        YAML::Node girderNode = data["girders"][i];
        stage.girders.push_back(_parseGirder(girderNode));
    }

    /* loads the weapons ammo */
    YAML::Node weaponsNode;
    if (!data["weaponsAmmo"] || !data["weaponsAmmo"].IsMap()){
        weaponsNode = YAML::LoadFile(DEFAULT_WEAPON_CONFIG_PATH);
    } else{
        weaponsNode = data["weaponsAmmo"];
    }

    for (const auto &elem : weaponsNode) {
        auto weaponID = stage.weaponStrToID.at(elem.first.as<std::string>());
        int ammo = elem.second.as<uint16_t>();
        stage.ammunitionCounter.emplace(weaponID, ammo);
    }

    // -1 indicates infinite uses
    stage.ammunitionCounter.emplace(Worm::WNone, -1);

    /* background */
    if (data["background"]) {
        YAML::Node bg = data["background"];
        if (bg["color"] && bg["color"].IsSequence()) {
            stage.backgroundColor.r = bg["color"][0].as<int>();
            stage.backgroundColor.g = bg["color"][1].as<int>();
            stage.backgroundColor.b = bg["color"][2].as<int>();
        }
        if (bg["closeBackgroundFile"]) {
            stage.closerBackgroundFile = bg["closeBackgroundFile"].as<std::string>();
        }
        if (bg["midBackgroundFile"]) {
            stage.midBackgroundFile = bg["midBackgroundFile"].as<std::string>();
        }
        if (bg["fartherBackgroundFile"]) {
            stage.fartherBackgroundFile = bg["fartherBackgroundFile"].as<std::string>();
        }
    }

    return stage;
}

Worms::Stage::Stage() {
    this->weaponStrToID.emplace("aerialAttack", Worm::WAerial);
    this->weaponStrToID.emplace("banana", Worm::WBanana);
    this->weaponStrToID.emplace("baseballBat", Worm::WBaseballBat);
    this->weaponStrToID.emplace("bazooka", Worm::WBazooka);
    this->weaponStrToID.emplace("cluster", Worm::WCluster);
    this->weaponStrToID.emplace("dynamite", Worm::WDynamite);
    this->weaponStrToID.emplace("grenade", Worm::WGrenade);
    this->weaponStrToID.emplace("holy", Worm::WHoly);
    this->weaponStrToID.emplace("mortar", Worm::WMortar);
    this->weaponStrToID.emplace("teleport", Worm::WTeleport);
    return;
}

const std::vector<Worms::WormData> &Worms::Stage::getWorms() const {
    return this->players;
}

const std::vector<Worms::GirderData> &Worms::Stage::getGirders() const {
    return this->girders;
}

float Worms::Stage::getHeight() const {
    return this->height;
}

float Worms::Stage::getWidth() const {
    return this->width;
}

const std::map<Worm::WeaponID, int16_t> &Worms::Stage::getAmmoCounter() const {
    return this->ammunitionCounter;
}
