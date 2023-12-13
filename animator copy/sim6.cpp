#include <iostream>
#include <random>
#include "Animator.h"
#include "VehicleBase.h"

using namespace std;

int num_of_sections = 8;
int max_time = 150;
double prob_new_vehicle_northbound = .2;
double prob_new_vehicle_eastbound = .2;
double prob_new_vehicle_southbound = .2;
double prob_new_vehicle_westbound = .2;
double proportion_of_cars = .4;
double proportion_of_SUVs = .4;

double proportion_right_turn_cars = 0;
double proportion_right_turn_SUVs = 0;
double proportion_right_turn_trucks = 0;

int green_north_south = 15;
int yellow_north_south = 8;
int green_east_west = 10;
int yellow_east_west = 6;

int right_turn_counter_north = 0;
int right_turn_counter_south = 0;
int right_turn_counter_east = 0;
int right_turn_counter_west = 0;


int yellow_remaining = -1;
int vehicle_size = -1;

std::mt19937 randomNumberGenerator; // Mersenne twister
std::uniform_real_distribution<double> rand_double(0,1);


vector<VehicleBase*> westbound(num_of_sections * 2 + 2, nullptr);
vector<VehicleBase*> eastbound(num_of_sections * 2 + 2, nullptr);
vector<VehicleBase*> southbound(num_of_sections * 2 + 2, nullptr);
vector<VehicleBase*> northbound(num_of_sections * 2 + 2, nullptr);


vector<VehicleBase*> headWestbound(4, nullptr);
vector<VehicleBase*> headEastbound(4, nullptr);
vector<VehicleBase*> headSouthbound(4, nullptr);
vector<VehicleBase*> headNorthbound(4, nullptr);

void green_light(vector<VehicleBase*>&, vector<VehicleBase*>&, vector<VehicleBase*>&, int&);
void yellow_light(vector<VehicleBase*>&, vector<VehicleBase*>&, vector<VehicleBase*>&, int&);
void red_light(vector<VehicleBase*>&, vector<VehicleBase*>&);

void add_vehicles(vector<VehicleBase*>&, vector<VehicleBase*>&, Direction, double);
void north_south_go();
void east_west_go();

LightColor lightNorthSouth = LightColor::green;
LightColor lightEastWest = LightColor::red;

int main() {
    Animator::MAX_VEHICLE_COUNT = 999;
    Animator anim(num_of_sections);
    char dummy;
    randomNumberGenerator.seed(391);

    anim.setLightNorthSouth(LightColor::green);
    anim.setLightEastWest(LightColor::red);

    int lightClock = 0;

    for (int j = 0; j < max_time; j++) {
        // THIS SECTION CONTROLS LIGHT SWITCHING
        if ((lightNorthSouth == LightColor::green) && (lightClock == green_north_south)) {
            yellow_remaining = yellow_north_south;
            lightNorthSouth = LightColor::yellow;
            anim.setLightNorthSouth(LightColor::yellow);
        }
        else if ((lightNorthSouth == LightColor::yellow) && (lightClock == green_north_south + yellow_north_south)) {
            lightNorthSouth = LightColor::red;
            lightEastWest = LightColor::green;
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
            lightClock = 0;
        }
        else if ((lightEastWest == LightColor::green) && (lightClock == green_east_west)) {
            yellow_remaining = yellow_east_west;
            lightEastWest = LightColor::yellow;
            anim.setLightEastWest(LightColor::yellow);
        }
        else if ((lightEastWest == LightColor::yellow) && (lightClock == green_east_west + yellow_east_west)) {
            lightNorthSouth = LightColor::green;
            lightEastWest = LightColor::red;
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::red);
            lightClock = 0;
        }
        lightClock++;

        // moves everything
        if (lightNorthSouth != LightColor::red) {
            north_south_go();
            east_west_go();
        } else {
            east_west_go();
            north_south_go();
        }

        // updates the animator
        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        yellow_remaining--;

        anim.draw(j);
        std::cin.get(dummy);
    }
}

void green_light(vector<VehicleBase*>& road, vector<VehicleBase*>& headRoad, vector<VehicleBase*>& rightRoad, int& counter) {
    // checks prop of right turn against rng to see if vehicle is turning
    double rand_right_turn = rand_double(randomNumberGenerator);
    bool turning_right = false;
    if (road[num_of_sections - 1] != nullptr) {
        if (road[num_of_sections - 1]->getVehicleType() == VehicleType::car && rand_right_turn < proportion_right_turn_cars) {
            turning_right = true;
        } else if (road[num_of_sections - 1]->getVehicleType() == VehicleType::suv && rand_right_turn < proportion_right_turn_SUVs) {
            turning_right = true;
        } else if (road[num_of_sections - 1]->getVehicleType() == VehicleType::truck && rand_right_turn < proportion_right_turn_trucks) {
            turning_right = true;
        }
    }

    // condition where vehicle is in process of turning
    if (counter) {
        counter--;
        rightRoad[num_of_sections] = road[num_of_sections - 1];
        road[num_of_sections - 1] = nullptr;

        for (int i = road.size() - 1; i > 0; i--) {
            road[i] = road[i - 1];
            road[i - 1] = nullptr;
        }

        if (!headRoad.empty()) {
            road[0] = headRoad.at(0);
            headRoad.pop_back();
        }
    } 
    // condition where vehicle is making its first right turn move
    else if (road[num_of_sections - 1] != road[num_of_sections] && road[num_of_sections - 1] != rightRoad[num_of_sections + 1] && turning_right) {
        if (road[num_of_sections - 1]->getVehicleType() == VehicleType::car) {
            counter = 1;
        } else if (road[num_of_sections - 1]->getVehicleType() == VehicleType::suv) {
            counter = 2;
        } else {
            counter = 3;
        }

        rightRoad[num_of_sections] = road[num_of_sections - 1];
        road[num_of_sections - 1] = nullptr;

        for (int i = road.size() - 1; i > 0; i--) {
            road[i] = road[i - 1];
            road[i - 1] = nullptr;
        }

        if (!headRoad.empty()) {
            road[0] = headRoad.at(0);
            headRoad.pop_back();
        }
    }
    // condition for when its not turning at all
    else {
        for (int i = road.size() - 1; i > 0; i--) {
            road[i] = road[i - 1];
            road[i - 1] = nullptr;
        }

        if (!headRoad.empty()) {
            road[0] = headRoad.at(0);
            headRoad.pop_back();
        }
    }
}

void yellow_light(vector<VehicleBase*>& road, vector<VehicleBase*>& headRoad, vector<VehicleBase*>& rightRoad, int& counter) {
    if (road[num_of_sections - 1] == nullptr) {
        green_light(road, headRoad, rightRoad, counter);
    } else {
        // checks if its already in the intersection
        if (road[num_of_sections - 1] == road[num_of_sections] || road[num_of_sections - 1] == rightRoad[num_of_sections + 1]) {
            green_light(road, headRoad, rightRoad, counter);
        } else {
            // checks if it has enough time to go
            vehicle_size = road[num_of_sections - 1]->getVehicleSize();
            if (vehicle_size + 1 <= yellow_remaining) {
                green_light(road, headRoad, rightRoad, counter);
            } else {
                red_light(road, headRoad);
            }
        }
    }
}

void red_light(vector<VehicleBase*>& road, vector<VehicleBase*>& headRoad) {
    // moves everything after the intersection
    for (int i = road.size() - 1; i > num_of_sections; i--) {
        road[i] = road[i - 1];
        road[i - 1] = nullptr;
    }
    
    // moves everything before the intersection
    for (int i = num_of_sections - 1; i > 0; i--) {
        if (road[i] == nullptr) {
            road[i] = road[i - 1];
            road[i - 1] = nullptr;
        }
    }

    // moves everything from the headRoad
    if (!headRoad.empty() && road[0] == nullptr) {
        road[0] = headRoad.at(0);
        headRoad.pop_back();
    }
}

void add_vehicles(vector<VehicleBase*>& road, vector<VehicleBase*>& headRoad, Direction direction, double probability) {
    double rand_add_vehicle = rand_double(randomNumberGenerator);

    if (rand_add_vehicle < probability && headRoad.empty()) {
        double rand_vehicle_type = rand_double(randomNumberGenerator);
        if (0 <= rand_vehicle_type && rand_vehicle_type < proportion_of_cars) {
            VehicleBase* car = new VehicleBase(VehicleType::car, direction);
            for (int i = 0; i < 2; i++) {
                headRoad.push_back(car);
            }
        } else if (proportion_of_cars <= rand_vehicle_type && rand_vehicle_type < proportion_of_cars + proportion_of_SUVs) {
            VehicleBase* suv = new VehicleBase(VehicleType::suv, direction);
            for (int i = 0; i < 3; i++) {
                headRoad.push_back(suv);
            }
        } else {
            VehicleBase* truck = new VehicleBase(VehicleType::truck, direction);
            for (int i = 0; i < 4; i++) {
                headRoad.push_back(truck);
            }
        }
    }
}

void north_south_go() {
    if (lightNorthSouth == LightColor::green) {
        green_light(northbound, headNorthbound, eastbound, right_turn_counter_north);
        green_light(southbound, headSouthbound, westbound, right_turn_counter_south);
    } else if (lightNorthSouth == LightColor::yellow) {
        yellow_light(northbound, headNorthbound, eastbound, right_turn_counter_north);
        yellow_light(southbound, headSouthbound, westbound, right_turn_counter_south);
    } else {
        red_light(northbound, headNorthbound);
        red_light(southbound, headSouthbound);
    }
    add_vehicles(northbound, headNorthbound, Direction::north, prob_new_vehicle_northbound);
    add_vehicles(southbound, headSouthbound, Direction::south, prob_new_vehicle_southbound);
}

void east_west_go() {
    if (lightEastWest == LightColor::green) {
        green_light(eastbound, headEastbound, southbound, right_turn_counter_east);
        green_light(westbound, headWestbound, northbound, right_turn_counter_west);
    } else if (lightEastWest == LightColor::yellow) {
        yellow_light(eastbound, headEastbound, southbound, right_turn_counter_east);
        yellow_light(westbound, headWestbound, northbound, right_turn_counter_west);
    } else {
        red_light(eastbound, headEastbound);
        red_light(westbound, headWestbound);
    }
    add_vehicles(eastbound, headEastbound, Direction::east, prob_new_vehicle_eastbound);
    add_vehicles(westbound, headWestbound, Direction::west, prob_new_vehicle_westbound);
}