#include <iostream>
#include <random>
#include "Animator.h"
#include "VehicleBase.h"

using namespace std;

int num_of_sections = 8;
int max_time = 100;
double prob_new_vehicle_northbound = .1;
double prob_new_vehicle_eastbound = .1;
double prob_new_vehicle_southbound = .1;
double prob_new_vehicle_westbound = .1;
double proportion_of_cars = .3;
double proportion_of_SUVs = .4;

double proportion_right_turn_cars = .4;
double proportion_right_turn_SUVs = 1;
double proportion_right_turn_trucks = .2;

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


double rand_prob_new_vehicle;
double rand_prob_vehicle_type;


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

void north_green_light();
void north_yellow_light();
void north_red_light();


void south_green_light();
void south_yellow_light();
void south_red_light();


void east_green_light();
void east_yellow_light();
void east_red_light();


void west_green_light();
void west_yellow_light();
void west_red_light();


void north_add_vehicles();
void south_add_vehicles();
void east_add_vehicles();
void west_add_vehicles();

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
        // NOTE: if he makes yellow light 0 seconds there are a lot of problems
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

        if (lightNorthSouth != LightColor::red) {
            // Northbound
            if (lightNorthSouth == LightColor::green) {
                north_green_light();
            } else if (lightNorthSouth == LightColor::yellow) {
                north_yellow_light();
            } else if (lightNorthSouth == LightColor::red) {
                north_red_light();
            }
            north_add_vehicles();

            // Southbound
            if (lightNorthSouth == LightColor::green) {
                south_green_light();
            } else if (lightNorthSouth == LightColor::yellow) {
                south_yellow_light();
            } else if (lightNorthSouth == LightColor::red) {
                south_red_light();
            }
            south_add_vehicles();

            // Eastbound
            if (lightEastWest == LightColor::green) {
                east_green_light();
            } else if (lightEastWest == LightColor::yellow) {
                east_yellow_light();
            } else if (lightEastWest == LightColor::red) {
                east_red_light();
            }
            east_add_vehicles();

            // Westbound
            if (lightEastWest == LightColor::green) {
                west_green_light();
            } else if (lightEastWest == LightColor::yellow) {
                west_yellow_light();
            } else if (lightEastWest == LightColor::red) {
                west_red_light();
            }
            west_add_vehicles();
        } else {
            // Eastbound
            if (lightEastWest == LightColor::green) {
                east_green_light();
            } else if (lightEastWest == LightColor::yellow) {
                east_yellow_light();
            } else if (lightEastWest == LightColor::red) {
                east_red_light();
            }
            east_add_vehicles();

            // Westbound
            if (lightEastWest == LightColor::green) {
                west_green_light();
            } else if (lightEastWest == LightColor::yellow) {
                west_yellow_light();
            } else if (lightEastWest == LightColor::red) {
                west_red_light();
            }
            west_add_vehicles();

            // Northbound
            if (lightNorthSouth == LightColor::green) {
                north_green_light();
            } else if (lightNorthSouth == LightColor::yellow) {
                north_yellow_light();
            } else if (lightNorthSouth == LightColor::red) {
                north_red_light();
            }
            north_add_vehicles();

            // Southbound
            if (lightNorthSouth == LightColor::green) {
                south_green_light();
            } else if (lightNorthSouth == LightColor::yellow) {
                south_yellow_light();
            } else if (lightNorthSouth == LightColor::red) {
                south_red_light();
            }
            south_add_vehicles();
        }

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        yellow_remaining--;

        anim.draw(j);
        std::cin.get(dummy);
    }
}


void north_green_light() {
    double randNum1 = rand_double(randomNumberGenerator);
    if (right_turn_counter_north) {
        right_turn_counter_north--;
        eastbound[num_of_sections] = northbound[num_of_sections - 1];
        northbound[num_of_sections - 1] = nullptr;

        for (int i = northbound.size() - 1; i > 0; i--) {
            northbound[i] = northbound[i-1];
            northbound[i-1] = nullptr;
        }

        if (!headNorthbound.empty()) {
            northbound[0] = headNorthbound.at(0);
            headNorthbound.pop_back();
        }    
    } else if (northbound[num_of_sections - 1] != northbound[num_of_sections] &&  northbound[num_of_sections - 1] != eastbound[num_of_sections + 1] && randNum1 < proportion_right_turn_cars) {
        if (northbound[num_of_sections - 1]->getVehicleType() == VehicleType::car) {
            right_turn_counter_north = 1;
        } else if (northbound[num_of_sections - 1]->getVehicleType() == VehicleType::suv) {
            right_turn_counter_north = 2;
        } else {
            right_turn_counter_north = 3;
        }

        eastbound[num_of_sections] = northbound[num_of_sections - 1];
        northbound[num_of_sections - 1] = nullptr;

        for (int i = northbound.size() - 1; i > 0; i--) {
            northbound[i] = northbound[i-1];
            northbound[i-1] = nullptr;
        }

        if (!headNorthbound.empty()) {
            northbound[0] = headNorthbound.at(0);
            headNorthbound.pop_back();
        }
    } else {
        for (int i = northbound.size() - 1; i > 0; i--) {
            northbound[i] = northbound[i-1];
            northbound[i-1] = nullptr;
        }

        if (!headNorthbound.empty()) {
            northbound[0] = headNorthbound.at(0);
            headNorthbound.pop_back();
        }
    }
}


void north_yellow_light() {
    if (northbound[num_of_sections-1] == nullptr) {
        north_green_light();
    }
    else {
        if (northbound[num_of_sections-1] == northbound[num_of_sections] || northbound[num_of_sections - 1] == eastbound[num_of_sections + 1]) {
            north_green_light();
        } else {
            vehicle_size = northbound[num_of_sections-1]->getVehicleSize();
            if (vehicle_size + 2 <= yellow_remaining) {
                north_green_light();
            } else {
                north_red_light();
            }
        }
    }
}


void north_red_light() {
    for (int i = northbound.size() - 1; i > num_of_sections; i--) {
        northbound[i] = northbound[i-1];
        northbound[i-1] = nullptr;
    }
    
    for (int i = num_of_sections-1; i > 0; i--) {
        if (northbound[i] == nullptr) {
            northbound[i] = northbound[i-1];
            northbound[i-1] = nullptr;
        }
    }

    if (!headNorthbound.empty() && northbound[0] == nullptr) {
        northbound[0] = headNorthbound.at(0);
        headNorthbound.pop_back();
    }
}

void south_green_light() {
    double randNum1 = rand_double(randomNumberGenerator);
    if (right_turn_counter_south) {
        right_turn_counter_south--;
        westbound[num_of_sections] = southbound[num_of_sections - 1];
        southbound[num_of_sections - 1] = nullptr;

        for (int i = southbound.size() - 1; i > 0; i--) {
            southbound[i] = southbound[i-1];
            southbound[i-1] = nullptr;
        }

        if (!headSouthbound.empty()) {
            southbound[0] = headSouthbound.at(0);
            headSouthbound.pop_back();
        }    
    } else if (southbound[num_of_sections - 1] != southbound[num_of_sections] &&  southbound[num_of_sections - 1] != westbound[num_of_sections + 1] && randNum1 < proportion_right_turn_cars) {
        if (southbound[num_of_sections - 1]->getVehicleType() == VehicleType::car) {
            right_turn_counter_south = 1;
        } else if (southbound[num_of_sections - 1]->getVehicleType() == VehicleType::suv) {
            right_turn_counter_south = 2;
        } else {
            right_turn_counter_south = 3;
        }

        westbound[num_of_sections] = southbound[num_of_sections - 1];
        southbound[num_of_sections - 1] = nullptr;

        for (int i = southbound.size() - 1; i > 0; i--) {
            southbound[i] = southbound[i-1];
            southbound[i-1] = nullptr;
        }

        if (!headSouthbound.empty()) {
            southbound[0] = headSouthbound.at(0);
            headSouthbound.pop_back();
        }
    } else {
        for (int i = southbound.size() - 1; i > 0; i--) {
            southbound[i] = southbound[i-1];
            southbound[i-1] = nullptr;
        }

        if (!headSouthbound.empty()) {
            southbound[0] = headSouthbound.at(0);
            headSouthbound.pop_back();
        }
    }
}


void south_yellow_light() {
    if (southbound[num_of_sections-1] == nullptr) {
        south_green_light();
    } else {
        if (southbound[num_of_sections-1] == southbound[num_of_sections] || southbound[num_of_sections - 1] == westbound[num_of_sections + 1]) {
            south_green_light();
        } else {
            vehicle_size = southbound[num_of_sections-1]->getVehicleSize();
            if (vehicle_size + 2 <= yellow_remaining) {
                south_green_light();
            } else {
                south_red_light();
            }
        }
    }
}


void south_red_light() {
    for (int i = southbound.size() - 1; i > num_of_sections; i--) {
        southbound[i] = southbound[i-1];
        southbound[i-1] = nullptr;
    }
    
    for (int i = num_of_sections-1; i > 0; i--) {
        if (southbound[i] == nullptr) {
            southbound[i] = southbound[i-1];
            southbound[i-1] = nullptr;
        }
    }

    if (!headSouthbound.empty() && southbound[0] == nullptr) {
        southbound[0] = headSouthbound.at(0);
        headSouthbound.pop_back();
    }
}

void east_green_light() {
    double randNum1 = rand_double(randomNumberGenerator);
    if (right_turn_counter_east) {
        right_turn_counter_east--;
        southbound[num_of_sections] = eastbound[num_of_sections - 1];
        eastbound[num_of_sections - 1] = nullptr;

        for (int i = eastbound.size() - 1; i > 0; i--) {
            eastbound[i] = eastbound[i-1];
            eastbound[i-1] = nullptr;
        }

        if (!headEastbound.empty()) {
            eastbound[0] = headEastbound.at(0);
            headEastbound.pop_back();
        }    
    } else if (eastbound[num_of_sections - 1] != eastbound[num_of_sections] &&  eastbound[num_of_sections - 1] != southbound[num_of_sections + 1] && randNum1 < proportion_right_turn_cars) {
        if (eastbound[num_of_sections - 1]->getVehicleType() == VehicleType::car) {
            right_turn_counter_east = 1;
        } else if (eastbound[num_of_sections - 1]->getVehicleType() == VehicleType::suv) {
            right_turn_counter_east = 2;
        } else {
            right_turn_counter_east = 3;
        }

        southbound[num_of_sections] = eastbound[num_of_sections - 1];
        eastbound[num_of_sections - 1] = nullptr;

        for (int i = eastbound.size() - 1; i > 0; i--) {
            eastbound[i] = eastbound[i-1];
            eastbound[i-1] = nullptr;
        }

        if (!headEastbound.empty()) {
            eastbound[0] = headEastbound.at(0);
            headEastbound.pop_back();
        }
    } else {
        for (int i = eastbound.size() - 1; i > 0; i--) {
            eastbound[i] = eastbound[i-1];
            eastbound[i-1] = nullptr;
        }

        if (!headEastbound.empty()) {
            eastbound[0] = headEastbound.at(0);
            headEastbound.pop_back();
        }
    }
}


void east_yellow_light() {
    if (eastbound[num_of_sections-1] == nullptr) {
        east_green_light();
    } else {
        if (eastbound[num_of_sections-1] == eastbound[num_of_sections] || eastbound[num_of_sections - 1] == southbound[num_of_sections + 1]) {
            east_green_light();
        } else {
            vehicle_size = eastbound[num_of_sections-1]->getVehicleSize();
            if (vehicle_size + 2 <= yellow_remaining) {
                east_green_light();
            } else {
                east_red_light();
            }
        }
    }
}


void east_red_light() {
    for (int i = eastbound.size() - 1; i > num_of_sections; i--) {
        eastbound[i] = eastbound[i-1];
        eastbound[i-1] = nullptr;
    }
    
    for (int i = num_of_sections-1; i > 0; i--) {
        if (eastbound[i] == nullptr) {
            eastbound[i] = eastbound[i-1];
            eastbound[i-1] = nullptr;
        }
    }

    if (!headEastbound.empty() && eastbound[0] == nullptr) {
        eastbound[0] = headEastbound.at(0);
        headEastbound.pop_back();
    }
}

void west_green_light() {
    double randNum1 = rand_double(randomNumberGenerator);
    if (right_turn_counter_west) {
        right_turn_counter_west--;
        northbound[num_of_sections] = westbound[num_of_sections - 1];
        westbound[num_of_sections - 1] = nullptr;

        for (int i = westbound.size() - 1; i > 0; i--) {
            westbound[i] = westbound[i-1];
            westbound[i-1] = nullptr;
        }

        if (!headWestbound.empty()) {
            westbound[0] = headWestbound.at(0);
            headWestbound.pop_back();
        }    
    } else if (westbound[num_of_sections - 1] != westbound[num_of_sections] &&  westbound[num_of_sections - 1] != northbound[num_of_sections + 1] && randNum1 < proportion_right_turn_cars) {
        if (westbound[num_of_sections - 1]->getVehicleType() == VehicleType::car) {
            right_turn_counter_west = 1;
        } else if (westbound[num_of_sections - 1]->getVehicleType() == VehicleType::suv) {
            right_turn_counter_west = 2;
        } else {
            right_turn_counter_west = 3;
        }

        northbound[num_of_sections] = westbound[num_of_sections - 1];
        westbound[num_of_sections - 1] = nullptr;

        for (int i = westbound.size() - 1; i > 0; i--) {
            westbound[i] = westbound[i-1];
            westbound[i-1] = nullptr;
        }

        if (!headWestbound.empty()) {
            westbound[0] = headWestbound.at(0);
            headWestbound.pop_back();
        }
    } else {
        for (int i = westbound.size() - 1; i > 0; i--) {
            westbound[i] = westbound[i-1];
            westbound[i-1] = nullptr;
        }

        if (!headWestbound.empty()) {
            westbound[0] = headWestbound.at(0);
            headWestbound.pop_back();
        }
    }
}


void west_yellow_light() {
    if (westbound[num_of_sections-1] == nullptr) {
        west_green_light();
    } else {
        if (westbound[num_of_sections-1] == westbound[num_of_sections] || westbound[num_of_sections - 1] == northbound[num_of_sections + 1]) {
            west_green_light();
        } else {
            vehicle_size = westbound[num_of_sections-1]->getVehicleSize();
            if (vehicle_size + 2 <= yellow_remaining) {
                west_green_light();
            } else {
                west_red_light();
            }
        }
    }
}


void west_red_light() {
    for (int i = westbound.size() - 1; i > num_of_sections; i--) {
        westbound[i] = westbound[i-1];
        westbound[i-1] = nullptr;
    }
    
    for (int i = num_of_sections-1; i > 0; i--) {
        if (westbound[i] == nullptr)
        {
            westbound[i] = westbound[i-1];
            westbound[i-1] = nullptr;
        }
    }

    if (!headWestbound.empty() && westbound[0] == nullptr) {
        westbound[0] = headWestbound.at(0);
        headWestbound.pop_back();
    }
}


void north_add_vehicles() {
    double randNum1 = rand_double(randomNumberGenerator);
    
    if (randNum1 < prob_new_vehicle_northbound && headNorthbound.empty()) {
        double randNum2 = rand_double(randomNumberGenerator);
        if (0 <= randNum2 && randNum2 < proportion_of_cars) {
            VehicleBase* car = new VehicleBase(VehicleType::car, Direction::north);
            for (int i = 0; i < 2; i++) {
                headNorthbound.push_back(car);
            }
        } else if (proportion_of_cars <= randNum2 && randNum2 < proportion_of_cars + proportion_of_SUVs) {
            VehicleBase* suv = new VehicleBase(VehicleType::suv, Direction::north);
            for (int i = 0; i < 3; i++) {
                headNorthbound.push_back(suv);
            }
        } else {
            VehicleBase* truck = new VehicleBase(VehicleType::truck, Direction::north);
            for (int i = 0; i < 4; i++) {
                headNorthbound.push_back(truck);
            }
        }
    }
}


void south_add_vehicles() {
    double randNum1 = rand_double(randomNumberGenerator);
    
    if (randNum1 < prob_new_vehicle_southbound && headSouthbound.empty()) {
        double randNum2 = rand_double(randomNumberGenerator);
        if (0 <= randNum2 && randNum2 < proportion_of_cars) {
            VehicleBase* car = new VehicleBase(VehicleType::car, Direction::north);
            for (int i = 0; i < 2; i++) {
                headSouthbound.push_back(car);
            }
        } else if (proportion_of_cars <= randNum2 && randNum2 < proportion_of_cars + proportion_of_SUVs) {
            VehicleBase* suv = new VehicleBase(VehicleType::suv, Direction::north);
            for (int i = 0; i < 3; i++) {
                headSouthbound.push_back(suv);
            }
        } else {
            VehicleBase* truck = new VehicleBase(VehicleType::truck, Direction::north);
            for (int i = 0; i < 4; i++) {
                headSouthbound.push_back(truck);
            }
        }
    }
}


void east_add_vehicles() {
    double randNum1 = rand_double(randomNumberGenerator);
    
    if (randNum1 < prob_new_vehicle_eastbound && headEastbound.empty()) {
        double randNum2 = rand_double(randomNumberGenerator);
        if (0 <= randNum2 && randNum2 < proportion_of_cars) {
            VehicleBase* car = new VehicleBase(VehicleType::car, Direction::north);
            for (int i = 0; i < 2; i++) {
                headEastbound.push_back(car);
            }
        } else if (proportion_of_cars <= randNum2 && randNum2 < proportion_of_cars + proportion_of_SUVs) {
            VehicleBase* suv = new VehicleBase(VehicleType::suv, Direction::north);
            for (int i = 0; i < 3; i++) {
                headEastbound.push_back(suv);
            }
        } else {
            VehicleBase* truck = new VehicleBase(VehicleType::truck, Direction::north);
            for (int i = 0; i < 4; i++) {
                headEastbound.push_back(truck);
            }
        }
    }
}


void west_add_vehicles() {
    double randNum1 = rand_double(randomNumberGenerator);
    
    if (randNum1 < prob_new_vehicle_westbound && headWestbound.empty()) {
        double randNum2 = rand_double(randomNumberGenerator);
        if (0 <= randNum2 && randNum2 < proportion_of_cars) {
            VehicleBase* car = new VehicleBase(VehicleType::car, Direction::north);
            for (int i = 0; i < 2; i++) {
                headWestbound.push_back(car);
            }
        } else if (proportion_of_cars <= randNum2 && randNum2 < proportion_of_cars + proportion_of_SUVs) {
            VehicleBase* suv = new VehicleBase(VehicleType::suv, Direction::north);
            for (int i = 0; i < 3; i++) {
                headWestbound.push_back(suv);
            }
        } else {
            VehicleBase* truck = new VehicleBase(VehicleType::truck, Direction::north);
            for (int i = 0; i < 4; i++) {
                headWestbound.push_back(truck);
            }
        }
    }
}
