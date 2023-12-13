#include <iostream>
#include <random>
#include "Animator.h"
#include "VehicleBase.h"




using namespace std;




int main() {
   Animator::MAX_VEHICLE_COUNT = 999;
   int num_of_sections = 12;
   int max_time = 100;
   double prob_new_vehicle_northbound = .3;
   double prob_vehicle_e = 0;
   double prob_vehicle_s = .2;
   double prob_vehicle_w = 0;
   double proportion_of_cars = .3;
   double proportion_of_SUVs = .3;


   int green_north_south = 18;
   int yellow_north_south = 1;
   int green_east_west = 30;
   int yellow_east_west = 30;


   int left_to_spawn_n = 0;
   int left_to_spawn_s = 0;
   int left_to_spawn_e = 0;
   int left_to_spawn_w = 0;
   Animator anim(num_of_sections);
   char dummy;




   double rand_prob_new_vehicle_northbound;
   double rand_prob_vehicle_type;
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


   vector<VehicleBase*> headWestbound(4, nullptr);
   vector<VehicleBase*> headEastbound(4, nullptr);
   vector<VehicleBase*> headouthbound(4, nullptr);
   vector<VehicleBase*> headNorthbound(4, nullptr);


   vector<VehicleBase*> tailWestbound(4, nullptr);
   vector<VehicleBase*> tailEastbound(4, nullptr);
   vector<VehicleBase*> tailSouthbound(4, nullptr);
   vector<VehicleBase*> tailNorthbound(4, nullptr);




   for (int j = 0; j < max_time; j++)
   {


       // Controls lights
       if ((lightNorthSouth == LightColor::green) && (lightClock == green_north_south))
       {
           lightNorthSouth = LightColor::yellow;
           anim.setLightNorthSouth(LightColor::yellow);
       }
       else if ((lightNorthSouth == LightColor::yellow) && (lightClock == green_north_south + yellow_north_south))
       {
           lightNorthSouth = LightColor::red;
           lightEastWest = LightColor::green;
           anim.setLightNorthSouth(LightColor::red);
           anim.setLightEastWest(LightColor::green);
           lightClock = 0;
       }
       else if ((lightEastWest == LightColor::green) && (lightClock == green_east_west))
       {
           lightEastWest = LightColor::yellow;
           anim.setLightEastWest(LightColor::yellow);
       }
       else if ((lightEastWest == LightColor::yellow) && (lightClock == green_east_west + yellow_east_west))
       {
           lightNorthSouth = LightColor::green;
           lightEastWest = LightColor::red;
           anim.setLightNorthSouth(LightColor::green);
           anim.setLightEastWest(LightColor::red);
           lightClock = 0;
       }
       lightClock++;
      


       // Deallocates the last index of tail
       // delete tailNorthbound[3]; //THIS DOESNT WORK BUT NEED TO DO EVENTUALLY


       // Northbound
       // Moves vehicles up one in tail
       if (lightNorthSouth == LightColor::green)
       {
           for (int i = 3; i > 0; i--) {
               tailNorthbound[i] = tailNorthbound[i-1];
               tailNorthbound[i-1] = nullptr;
           }


           // Moves last section of road into first section of tail
           tailNorthbound[0] = northbound[northbound.size() - 1];
           northbound[northbound.size() - 1] = nullptr;


           // Moves up vehicles in road
           for (int i = northbound.size() - 1; i > 0; i--) {
               northbound[i] = northbound[i-1];
               northbound[i-1] = nullptr;
           }


           // Moves last section of head into first section of road
           northbound[0] = headNorthbound[3];
           headNorthbound[3] = nullptr;


           // Moves vehicles up on in head
           for (int i = 3; i > 0; i--) {
               headNorthbound[i] = headNorthbound[i-1];
               headNorthbound[i-1] = nullptr;
           }
       }
       else if (lightNorthSouth == LightColor::red)
       {
           for (int i = 3; i > 0; i--) {
               tailNorthbound[i] = tailNorthbound[i-1];
               tailNorthbound[i-1] = nullptr;
           }


           // Moves last section of road into first section of tail
           tailNorthbound[0] = northbound[northbound.size() - 1];
           northbound[northbound.size() - 1] = nullptr;
          
           // Moves up vehicles in road 
           for (int i = northbound.size() - 1; i > num_of_sections; i--) {
               northbound[i] = northbound[i-1];
               northbound[i-1] = nullptr;
           }
          
           for (int i = num_of_sections-1; i > 0; i--) {
               if (northbound[i] == nullptr)
               {
                   northbound[i] = northbound[i-1];
                   northbound[i-1] = nullptr;
               }
           }


           // Moves last section of head into first section of road
           if (northbound[0] == nullptr)
           {
               northbound[0] = headNorthbound[3];
               headNorthbound[3] = nullptr;
           }


           // Moves vehicles up on in head
           for (int i = 3; i > 0; i--) {
               if (headNorthbound[3] == nullptr)
               {
                   headNorthbound[i] = headNorthbound[i-1];
                   headNorthbound[i-1] = nullptr;
               }
           }
          
       }


       // Adds vehicles
       if (headNorthbound[3] == nullptr) // can't actually use .empty() because it will have nullptrs
       {
           // Randomly decide to add a new vehicle or not based on probabilty
           rand_prob_new_vehicle_northbound = rand_double(randomNumberGenerator);
           if (rand_prob_new_vehicle_northbound < prob_new_vehicle_northbound)
           {
               // Determine which vehicle based off random
               rand_prob_vehicle_type = rand_double(randomNumberGenerator);
               if (rand_prob_vehicle_type < proportion_of_cars)
               {
                   // Add car
                   headNorthbound[3] = new VehicleBase(VehicleType::car, Direction::north);
                   headNorthbound[2] = headNorthbound[3];
               }
               else if ((rand_prob_vehicle_type > proportion_of_cars) && (rand_prob_vehicle_type < proportion_of_SUVs + proportion_of_cars))
               {
                   // Add SUV
                   headNorthbound[3] = new VehicleBase(VehicleType::suv, Direction::north);
                   headNorthbound[2] = headNorthbound[3];
                   headNorthbound[1] = headNorthbound[2];
               }
               else
               {
                   // Add truck
                   headNorthbound[3] = new VehicleBase(VehicleType::truck, Direction::north);
                   headNorthbound[2] = headNorthbound[3];
                   headNorthbound[1] = headNorthbound[2];
                   headNorthbound[0] = headNorthbound[4];
               }
           }
       }
       anim.setVehiclesNorthbound(northbound);
       anim.setVehiclesWestbound(westbound);
       anim.setVehiclesSouthbound(southbound);
       anim.setVehiclesEastbound(eastbound);


       /*
       cout << tailNorthbound[3] << endl;
       cout << tailNorthbound[2] << endl;
       cout << tailNorthbound[1] << endl;
       cout << tailNorthbound[0] << endl;
       cout << endl;
       */
       //cout << lightClock << endl;
       anim.draw(j);
       std::cin.get(dummy);
  }
}
