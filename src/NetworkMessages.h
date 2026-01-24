#pragma once

#include "../utils/json.hpp"
#include "GameLogic.h"

using json = nlohmann::json;


// this struct helps structure the network data
struct GameMessage {
    std::string type; // move , chat , init
    json data;

    // helper to convert this C++ struct to JSON string
    std::string toJsonString() {
        json j;
        j["type"] = type;
        j["data"] = data;
        return j.dump(); // the dump member function return a string containing the serialization of the JSON value
    }

    // helper to create a Move Message
    static GameMessage createMove(Pos from, Pos to){
        return {"move", {{"f_r" , from.row}, {"f_c" , from.col} , {"t_r" , to.row}, {"t_c" , to.col}}};
    }
};

