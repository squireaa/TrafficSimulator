// Aaron Squire and Eric Markstein
// 3/19/23
// This translation unit defines the methods for the VehicleBase class
#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__


#include "VehicleBase.h"


int VehicleBase::vehicleCount = 0;


// Constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction)
   : vehicleID(VehicleBase::vehicleCount++),
     vehicleType(type),
     vehicleDirection(direction)
{}


// Copy constructor
VehicleBase::VehicleBase(const VehicleBase& other)
   : vehicleID(other.vehicleID),
     vehicleType(other.vehicleType),
     vehicleDirection(other.vehicleDirection)
{}


// Copy assignment operator
VehicleBase& VehicleBase::operator=(const VehicleBase& other)
{
   if (this == &other)
   {
       return *this;
   }
  
   this->vehicleType = other.vehicleType;
   this->vehicleDirection = other.vehicleDirection;
   this->vehicleID = other.vehicleID;
  
   return *this;
}


// Destructor
VehicleBase::~VehicleBase() {}


// Move constructor
VehicleBase::VehicleBase(VehicleBase&& other) noexcept
{
  this->vehicleID = other.vehicleID;
  this->vehicleType = other.vehicleType;
  this->vehicleDirection = other.vehicleDirection;
 
  other.vehicleID = -1;
  other.vehicleType = VehicleType::car;
  other.vehicleDirection = Direction::north;
}


// Move assignment operator
VehicleBase& VehicleBase::operator=(VehicleBase&& other) noexcept {
   if (this == &other) {
       return *this;
   }

   this->vehicleID = other.vehicleID;
   this->vehicleType = other.vehicleType;
   this->vehicleDirection = other.vehicleDirection;
  
   // sets defailt type to default of car and north
   other.vehicleID = -1;
   other.vehicleType = VehicleType::car;
   other.vehicleDirection = Direction::north;

   return *this;
}

int VehicleBase::getVehicleSize() {
   if (this->vehicleType == VehicleType::car) {
      return 2;
   } else if (this->vehicleType == VehicleType::suv) {
      return 3;
   } else if (this->vehicleType == VehicleType::truck) {
      return 4;
   } else {
      return -1;
   }
}


#endif
