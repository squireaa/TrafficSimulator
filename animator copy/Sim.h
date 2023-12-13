#ifndef __SIM_H__
#define __SIM_H__

class Sim {
    private:
        int num_of_sections;
        int max_time;
        double prob_new_vehicle_northbound;
        double prob_new_vehicle_eastbound;
        double prob_new_vehicle_southbound;
        double prob_new_vehicle_westbound;
        double proportion_of_cars;
        double proportion_of_SUVs;


        double proportion_right_turn_cars;
        double proportion_right_turn_SUVs;
        double proportion_right_turn_trucks;


        int green_north_south;
        int yellow_north_south;
        int green_east_west;
        int yellow_east_west;


        int right_turn_counter_north;
        int right_turn_counter_south;
        int right_turn_counter_east;
        int right_turn_counter_west;


        int yellow_remaining;
        int vehicle_size;


        std::mt19937 randomNumberGenerator; // Mersenne twister
        std::uniform_real_distribution<double> rand_double(0,1);


        vector<VehicleBase*> westbound(num_of_sections * 2 + 2, nullptr);
        vector<VehicleBase*> eastbound(num_of_sections * 2 + 2, nullptr);
        vector<VehicleBase*> southbound(num_of_sections * 2 + 2, nullptr);
        vector<VehicleBase*> northbound(num_of_sections * 2 + 2, nullptr);


        vector<VehicleBase*> headWestbound;
        vector<VehicleBase*> headEastbound;
        vector<VehicleBase*> headSouthbound;
        vector<VehicleBase*> headNorthbound;
        
        LightColor lightNorthSouth = LightColor::green;
        LightColor lightEastWest = LightColor::red;
        
    public:
        void green_light(vector<VehicleBase*>&, vector<VehicleBase*>&, vector<VehicleBase*>&, int&);
        void yellow_light(vector<VehicleBase*>&, vector<VehicleBase*>&, vector<VehicleBase*>&, int&);
        void red_light(vector<VehicleBase*>&, vector<VehicleBase*>&);


        void add_vehicles(vector<VehicleBase*>&, vector<VehicleBase*>&, Direction, double);
        void north_south_go();
        void east_west_go();
}

#endif
