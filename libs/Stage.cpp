/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Stage.h"
#include <fstream>
#include "Exception.h"
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

    // TODO: use predefined length for short/long girders or load it from the YAML
    float length = 10.769f;

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

    uint16_t wormsHealth = data["wormsHealth"].as<float>();

    Stage stage;
    if (!data["worms"] || !data["worms"].IsSequence()) {
        throw Exception{"Invalid stage: expected a sequence of 'worms'"};
    }

    /* loads the worms */
    for (std::size_t i = 0; i < data["worms"].size(); i++) {
        YAML::Node wormNode = data["worms"][i];
        stage.players.push_back(_parseWorm(wormsHealth, wormNode));
    }

    /* loads the girders */
    if (!data["longGirders"] || !data["longGirders"].IsSequence()) {
        throw Exception{"Invalid stage: expected a sequence of 'longGirders'"};
    }
    for (std::size_t i = 0; i < data["longGirders"].size(); i++) {
        YAML::Node girderNode = data["longGirders"][i];
        stage.girders.push_back(_parseGirder(girderNode));
    }

    return stage;
}

Worms::Stage::Stage() {
    return;
    uint16_t health = 100;
    this->players.push_back(Worms::WormData{health, Math::Point<float>{50.0f, 20.0f}});
    this->players.push_back(Worms::WormData{health, Math::Point<float>{-3.0f, 20.0f}});
    this->players.push_back(Worms::WormData{health, Math::Point<float>{-5.0f, 20.0f}});

    this->girders.push_back(GirderData{11, 1.42f, 0.0f, Math::Point<float>{50.0f, 10.0f}});
    this->girders.push_back(GirderData{31, 1.42f, 0.0f, Math::Point<float>{-50.0f, 7.0f}});
    this->girders.push_back(GirderData{20, 1.42f, 0.0f, Math::Point<float>{-30.0f, 10.0f}});
    this->girders.push_back(GirderData{10, 1.42f, 0.0f, Math::Point<float>{0.0f, 13.0f}});
    this->girders.push_back(GirderData{4, 1.42f, 0.0f, Math::Point<float>{-5.0f, 9.5f}});
    this->girders.push_back(GirderData{8, 1.42f, 0.0f, Math::Point<float>{-17.0f, 2.0f}});
    this->girders.push_back(GirderData{14, 1.42f, 0.0f, Math::Point<float>{-11.0f, 5.0f}});
    this->girders.push_back(GirderData{2.5f, 1.42f, 0.0f, Math::Point<float>{-3.0f, 2.0f}});
    this->girders.push_back(GirderData{7, 1.42f, 0.0f, Math::Point<float>{5.0f, 2.0f}});
    this->girders.push_back(GirderData{13.4f, 1.42f, 0.0f, Math::Point<float>{30.0f, 15.0f}});
    this->girders.push_back(GirderData{13.4f, 1.42f, 0.0f, Math::Point<float>{11.0f, 2.0f}});
    this->girders.push_back(GirderData{6.0f, 1.42f, 45.0f, Math::Point<float>{21.5f, 13.0f}});
    this->girders.push_back(GirderData{8.0f, 1.42f, -30.0f, Math::Point<float>{40.0f, 13.0f}});
    this->girders.push_back(GirderData{8.0f, 1.42f, -46.0f, Math::Point<float>{7.5f, 11.0f}});
    this->girders.push_back(GirderData{10.0f, 1.42f, -60.0f, Math::Point<float>{57.0f, 6.0f}});
    this->girders.push_back(GirderData{10.0f, 1.42f, -44.0f, Math::Point<float>{61.5f, 0.0f}});
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
