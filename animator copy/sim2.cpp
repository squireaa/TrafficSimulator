#include <iostream>
#include <random>
#include "Animator.h"
#include "VehicleBase.h"

using namespace std;

int how_long_left_on_yellow(int, int, int, int, int);

int main() {
    Animator::MAX_VEHICLE_COUNT = 999;
    int num_of_sections = 8;
    int max_time = 100;
    double prob_vehicle_n = .2;
    double prob_vehicle_e = 0;
    double prob_vehicle_s = .2;
    double prob_vehicle_w = 0;
    double prop_car = .4;
    double prop_suv = .3;
    int green_north_south = 10;
    int yellow_north_south = 5;
    int green_east_west = 12;
    int yellow_east_west = 7;
    vector<VehicleBase*> northhead;
    vector<VehicleBase*> northtail;
    Animator anim(num_of_sections);
    char dummy;

    std::mt19937 randomNumberGenerator; // Mersenne twister
    std::uniform_real_distribution<double> rand_double(0,1);
    randomNumberGenerator.seed(391);

    anim.setLightNorthSouth(LightColor::green);
    anim.setLightEastWest(LightColor::red);

    LightColor lightNorthSouth = LightColor::green;
    LightColor lightEastWest = LightColor::red;
    int lightClock = 0;

    vector<VehicleBase*> westbound(num_of_sections * 2 + 2, nullptr);
    vector<VehicleBase*> eastbound(num_of_sections * 2 + 2, nullptr);
    vector<VehicleBase*> southbound(num_of_sections * 2 + 2, nullptr);
    vector<VehicleBase*> northbound(num_of_sections * 2 + 2, nullptr);

    for (int i = 0; i < max_time; i++) {
        // controls lights
        // THIS SECTION CONTROLS LIGHT SWITCHING
        if ((lightNorthSouth == LightColor::green) && (lightClock == green_north_south)) {
            lightNorthSouth = LightColor::yellow;
            anim.setLightNorthSouth(LightColor::yellow);
        } else if ((lightNorthSouth == LightColor::yellow) && (lightClock == green_north_south + yellow_north_south)) {
            lightNorthSouth = LightColor::red;
            lightEastWest = LightColor::green;
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
            lightClock = 0;
        } else if ((lightEastWest == LightColor::green) && (lightClock == green_east_west)) {
            lightEastWest = LightColor::yellow;
            anim.setLightEastWest(LightColor::yellow);
        } else if ((lightEastWest == LightColor::yellow) && (lightClock == green_east_west + yellow_east_west)) {
            lightNorthSouth = LightColor::green;
            lightEastWest = LightColor::red;
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::red);
            lightClock = 0;
        }
        lightClock++;


        if (lightNorthSouth == LightColor::green) {
            // moves up everything
            for (int i = northbound.size() - 1; i > 0; i--) {
                northbound[i] = northbound[i-1];
                northbound[i-1] = nullptr;
            }
            
            // moves up the vehicles in the loaders
            if (!northhead.empty()) {
                northbound[0] = northhead.at(0);
                northhead.pop_back();
            }
        } else if (lightNorthSouth == LightColor::yellow) {
            if (northbound[num_of_sections - 1] == northbound[num_of_sections - 2] && how_long_left_on_yellow(i, yellow_east_west, green_east_west, yellow_north_south, green_north_south) < 4) {
                // treat like red light
                for (int i = northbound.size() - 1; i > num_of_sections; i--) {
                    northbound[i] = northbound[i-1];
                    northbound[i-1] = nullptr;
                }
                for (int i = num_of_sections - 1; i > 0; i--) {
                    if (northbound[i] == nullptr) {
                        northbound[i] = northbound[i-1];
                        northbound[i-1] = nullptr;
                    }
                }
                if (!northhead.empty() && northbound[0] == nullptr) {
                    northbound[0] = northhead.at(0);
                    northhead.pop_back();
                }
            } else {
                // treat like green light
                for (int i = northbound.size() - 1; i > 0; i--) {
                    northbound[i] = northbound[i-1];
                    northbound[i-1] = nullptr;
                }
                if (!northhead.empty() && northbound[0] == nullptr) {
                    northbound[0] = northhead.at(0);
                    northhead.pop_back();
                }
            }
        } else if (lightNorthSouth == LightColor::red) {
            for (int i = northbound.size() - 1; i > num_of_sections; i--) {
                northbound[i] = northbound[i-1];
                northbound[i-1] = nullptr;
            }
            for (int i = num_of_sections - 1; i > 0; i--) {
                if (northbound[i] == nullptr) {
                    northbound[i] = northbound[i-1];
                    northbound[i-1] = nullptr;
                }
            }
            if (!northhead.empty() && northbound[0] == nullptr) {
                northbound[0] = northhead.at(0);
                northhead.pop_back();
            }
        }

        double randNum1 = rand_double(randomNumberGenerator);

        // loads the car into the head vector
        if (randNum1 < prob_vehicle_n && northhead.empty()) {
            double randNum2 = rand_double(randomNumberGenerator);
            if (0 <= randNum2 && randNum2 < prop_car) {
                VehicleBase* car = new VehicleBase(VehicleType::car, Direction::north);
                for (int i = 0; i < 2; i++) {
                    northhead.push_back(car);
                }
            } else if (prop_car <= randNum2 && randNum2 < prop_car + prop_suv) {
                VehicleBase* suv = new VehicleBase(VehicleType::suv, Direction::north);
                for (int i = 0; i < 3; i++) {
                    northhead.push_back(suv);
                }
            } else {
                VehicleBase* truck = new VehicleBase(VehicleType::truck, Direction::north);
                for (int i = 0; i < 4; i++) {
                    northhead.push_back(truck);
                }
            }
        }

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        anim.draw(i);
        //std::cin.get(dummy);
    }
}

int how_long_left_on_yellow(int timePassed, int yellow_north_south, int green_north_south, int yellow_east_west, int green_east_west) {
    int num = timePassed % (yellow_north_south + yellow_east_west + green_north_south + green_east_west);
    if (0 < num && num <= green_east_west) {
        return -1;
    } else if (green_east_west < num && num <= green_east_west + yellow_east_west) {
        return yellow_east_west - (num - green_east_west);
    } else if (green_east_west + yellow_east_west < num && num <= green_east_west + yellow_east_west + green_north_south) {
        return -1;
    } else if (green_east_west + yellow_east_west + green_north_south < num && num <= green_east_west + yellow_east_west + green_north_south + yellow_east_west) {
        return yellow_north_south - (num - (green_east_west + yellow_east_west + green_north_south));
    } else {
        return 0;
    }
}
