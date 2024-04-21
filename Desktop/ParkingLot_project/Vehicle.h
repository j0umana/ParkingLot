#ifndef MTMPARKINGLOT_VEHICLE_H
#define MTMPARKINGLOT_VEHICLE_H

#include "ParkingLotTypes.h"
#include "ParkingSpot.h"
#include "Time.h"

using std::string;

using namespace ParkingLotUtils;

/**
 * Vehicle is a class were we store the data about a vehicle in the parking lot.
 * vehicleType: the type of the vehicle.
 * plateNumber: is the plateNumber of the vehicle.
 * entranceTime: is the time the vehicle entered the parking lot.
 * parkingSpot: is a class that stores the parking block and parking number of
 * the vehicle.
 * reported: a boolean value: true if the vehicle was reported, else, false.
 */
class Vehicle{

    VehicleType vehicleType;
    LicensePlate plateNumber;
    Time entranceTime;
    ParkingSpot parkingSpot;
    bool reported;

public:
    /**
     * The Vehicle class constructor.
     * @param vehicleType
     * @param plateNumber
     * @param entranceTime
     * @param parkingBlock
     * @param parkingNumber
     * @param reported
     */
   Vehicle(VehicleType vehicleType, LicensePlate plateNumber,
           Time entranceTime,VehicleType parkingBlock,
           unsigned int parkingNumber, bool reported);

   /**
    * Copy constructor for the class.
    * @param vehicle
    */
   Vehicle(const Vehicle& vehicle) = default;

   /**
    * Destructor of the class.
    */
   ~Vehicle() = default;

   /**
    *
    * @return the type of the vehicle.
    */
    VehicleType getVehicleType() const;

    /**
     *
     * @return the plate number of the vehicle.
     */
    LicensePlate getPlateNumber() const;

    /**
     *
     * @return the entrance time of the vehicle.
     */
    Time getEntranceTime() const;

    /**
     *
     * @return whether the vehicle received a report(fined) or not
     */
    bool isReported();

    /**
     * updates the report field of the vehicle to true (in case the vehicle
     * received a report)
     */
    void UpdateReported();

    /**
     *
     * @return the parking spot of a vehicle.
     */
    ParkingSpot vehicleGetParkingSpot() const;
    };

/**
 * class compare is a class that includes the compare function that we use to
 * compare between two vehicles. We compare according the the license plate.
 */
class Compare {

public:
    /**
     *
     * @param vehicle1
     * @param vehicle2
     * @return true if the vehicles are the same (if they have the same license
     * plate), else, false.
     */
    bool operator()(const Vehicle& vehicle1,const Vehicle& vehicle2) const {
        return vehicle1.getPlateNumber() == vehicle2.getPlateNumber();
    }
};




#endif //MTMPARKINGLOT_VEHICLE_H