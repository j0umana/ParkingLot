#include "Vehicle.h"

using std::string;

using namespace ParkingLotUtils;

//------------------------------------------------------------------------------

Vehicle::Vehicle(VehicleType vehicleType, LicensePlate plateNumber,
        Time entranceTime,VehicleType parkingBlock,
        unsigned int parkingNumber, bool reported) :
         vehicleType(vehicleType), plateNumber(plateNumber),
         entranceTime(entranceTime),parkingSpot(parkingBlock,parkingNumber),
         reported(false){
}

//------------------------------------------------------------------------------

VehicleType Vehicle::getVehicleType() const{
    return vehicleType;
}

//------------------------------------------------------------------------------

LicensePlate Vehicle::getPlateNumber() const{
    return plateNumber;
}

//------------------------------------------------------------------------------

Time Vehicle::getEntranceTime() const{
    return entranceTime;
}
//------------------------------------------------------------------------------

bool Vehicle::isReported(){
    return reported;
}

//------------------------------------------------------------------------------

void Vehicle::UpdateReported(){
    reported=true;
}

//------------------------------------------------------------------------------

ParkingSpot Vehicle::vehicleGetParkingSpot() const{
    return parkingSpot;
}

//------------------------------------------------------------------------------