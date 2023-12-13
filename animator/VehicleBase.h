// Aaron Squire and Eric Markstein
// 3/19/23
// This translation unit is the header file for the VehicleBase class
#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};


class VehicleBase
{
  public:
     static int vehicleCount;


  private:
     int         vehicleID;
     VehicleType vehicleType;
     Direction   vehicleDirection;


  public:
      VehicleBase(VehicleType type, Direction originalDirection);


      VehicleBase(const VehicleBase& other);
      VehicleBase& operator=(const VehicleBase& other);
      ~VehicleBase();
      VehicleBase(VehicleBase&& other) noexcept;
      VehicleBase& operator=(VehicleBase&& other) noexcept;
      int  getVehicleSize();


      inline int getVehicleID() const { return this->vehicleID; }


      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
    
};


#endif
