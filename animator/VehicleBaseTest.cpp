#include <iostream>
#include "VehicleBase.h"

using namespace std;

int main() {
    // Tests the getVehicleSize method
    VehicleBase vb1(VehicleType::car, Direction::north);
    std::cout << "Vehicle 1 size: " << vb1.getVehicleSize() << std::endl;

    VehicleBase vb2(VehicleType::suv, Direction::north);
    std::cout << "Vehicle 2 size: " << vb2.getVehicleSize() << std::endl;

    VehicleBase vb3(VehicleType::truck, Direction::south);
    std::cout << "Vehicle 3 size: " << vb3.getVehicleSize() << std::endl;


    // Tests the copy constructor for equivalency
    VehicleBase vb4(VehicleType::truck, Direction::south);
    VehicleBase vb5 = vb4;
    std::cout << (vb4.getVehicleID() == vb5.getVehicleID()) << std::endl;
    std::cout << (vb4.getVehicleType() == vb5.getVehicleType()) << std::endl;
    std::cout << (vb4.getVehicleOriginalDirection() == vb5.getVehicleOriginalDirection()) << std::endl;


    // Tests the move constructor
    VehicleBase vb6 = move(vb5);
    std::cout << (vb6.getVehicleID() != vb5.getVehicleID()) << std::endl;
    std::cout << (vb6.getVehicleType() != vb5.getVehicleType()) << std::endl;
    std::cout << (vb6.getVehicleOriginalDirection() != vb5.getVehicleOriginalDirection()) << std::endl;
    std::cout << (vb6.getVehicleID() == vb4.getVehicleID()) << std::endl;
    std::cout << (vb6.getVehicleType() == VehicleType::truck) << std::endl;
    std::cout << (vb6.getVehicleOriginalDirection() == Direction::south) << std::endl;
    
    // Tests the copy constructor was independence
    std::cout << (vb4.getVehicleID() != vb5.getVehicleID()) << std::endl;
    std::cout << (vb4.getVehicleType() != vb5.getVehicleType()) << std::endl;
    std::cout << (vb4.getVehicleOriginalDirection() != vb5.getVehicleOriginalDirection()) << std::endl;


    // Tests the copy assignment operator for equivalency
    VehicleBase vb7(VehicleType::suv, Direction::west);
    vb6 = vb7;
    std::cout << (vb6.getVehicleID() == vb7.getVehicleID()) << std::endl;
    std::cout << (vb6.getVehicleType() == vb7.getVehicleType()) << std::endl;
    std::cout << (vb6.getVehicleOriginalDirection() == vb7.getVehicleOriginalDirection()) << std::endl;


    // Tests the move assignment operator
    vb3 = move(vb7);
    std::cout << (vb7.getVehicleType() != VehicleType::suv) << std::endl;
    std::cout << (vb7.getVehicleOriginalDirection() != Direction::west) << std::endl;
    std::cout << (vb3.getVehicleType() == VehicleType::suv) << std::endl;
    std::cout << (vb3.getVehicleOriginalDirection() == Direction::west) << std::endl;

    std::cout << (vb6.getVehicleID() != vb7.getVehicleID()) << std::endl;
    std::cout << (vb6.getVehicleType() != vb7.getVehicleType()) << std::endl;
    std::cout << (vb6.getVehicleOriginalDirection() != vb7.getVehicleOriginalDirection()) << std::endl;
    return 0;
}
