#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "Vehicle.h"
#include "ParkingLotPrinter.h"

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {
        /**
         * motorbikeArray is a unique array were we store all the data about
         * the motorbike parking lot and about all the vehicles that parked in
         * the array.
         *
         * handicappedArray is a unique array were we store all the data about
         * the handicapped parking lot and about all the vehicles that parked in
         * the array.
         *
         * carArray is a unique array were we store all the data about
         * the car parking lot and about all the vehicles that parked in
         * the array.
         */
        UniqueArray<Vehicle,Compare> motorbikeArray;
        UniqueArray<Vehicle,Compare> handicappedArray;
        UniqueArray<Vehicle,Compare> carArray;

        /**
         * findVehicleByPlateNumber:
         * @param plateNumber the license plate of the vehicle we want to find.
         * @param index a reference that we put into it the parking number of
         * the vehicle in case we found it.
         * @param type  reference that we put into it the type of
         * the vehicle in case we found it.
         * @param parkingLotType  reference that we put into it the parking
         * block were the vehicle parked in case we found it.
         * @return true if found, else, false.
         */
        bool findVehicleByPlateNumber(LicensePlate& plateNumber,
                unsigned int& index,VehicleType& type,
                VehicleType& parkingLotType);

        /**
         * checkIfParkingAvailable:
         * @param vehicleType the type of the vehicle we want to enter.
         * @param availableParkingBlock the type of the parking block that we
         * can enter the vehicle into. (if there is any valid and available
         * parking block)
         * @param index the parking number of the availableParkingBlock were we
         * can insert the vehicle.
         * @return true if there is a valid ParkingBlock available for the
         * vehicle, else, false.
         */
        bool checkIfParkingAvailable(VehicleType vehicleType,
                VehicleType& availableParkingBlock,unsigned int& index);

        /**
         * calculateMotorbikePayment: a helping function that calculates the
         * total amount a certain motorbike has to pay when exiting the parking.
         * @param vehicle the motorbike we want to calculate its payment.
         * @param exitTime
         * @return the total amount the motorbike has to pay.
         */
        unsigned int calculateMotorbikePayment(Vehicle &vehicle, Time exitTime);
/**
         * calculateCarPayment: a helping function that calculates the
         * total amount a certain car has to pay when exiting the parking.
         * @param vehicle the car we want to calculate its payment.
         * @param exitTime
         * @return the total amount the car has to pay.
         */
        unsigned int calculateCarPayment(Vehicle &vehicle, Time exitTime);

        /**
         * calculateMotorbikePayment: a helping function that calculates the
         * total amount a certain handicapped has to pay when exiting the
         * parking.
         * @param vehicle the handicapped vehicle we want to calculate
         * its payment.
         * @param exitTime
         * @return the total amount the handicapped vehicle has to pay.
         */
        unsigned int calculateHandicappedPayment(Vehicle &vehicle,
                                                 Time exitTime);

        /**
         * findVehicleInBlock:searches if a certain vehicle exists in the
         * certain parking block.
         * @param plateNumber
         * @param index: the parking number it is parked in, in case it is
         * already parked.
         * @param parkingType: the parking lot type it is parked in, in case it
         * is already parked.
         * @param true_type: the true type of the parked vehicle. (we need to
         * know that especially when the vehicle is parked in the car parking
         * lot.)
         * @return true, if the vehicle is already parked, else, false.
         */
        bool findVehicleInBlock(LicensePlate& plateNumber,
                                unsigned int& index,VehicleType parkingType,
                                VehicleType& true_type);

        /**
         * enterVehicle: a function that inserts the vehicle in a valid parking
         * block and parking number.
         * @param vehicle
         * @param parkingLotType: the parking lot type it can park at.
         * @param licensePlate
         */
        void enterVehicle(Vehicle &vehicle, VehicleType parkingLotType,
                                   LicensePlate& licensePlate);

        /**
         * checkIfVehicleAlreadyParked: checks if the vehicle is parked in the
         * parking lot.
         * @param parkingLotType: a reference that we put in it the parking
         * block of the vehicle in case it is already parked.
         * @param vehicle
         * @param index: the parking number of the parking block were the
         * vehicle parked in case it is already parked.
         * @return true if the vehicle is already parked, else, false.
         */
        bool checkIfVehicleAlreadyParked(VehicleType& parkingLotType,
                Vehicle& vehicle, unsigned int& index);

        /**
         * exitVehiclePayment: a function that calculates the payment the
         * vehicle has to pay when it exists.
         * @param licensePlate
         * @param index: the parking number of the vehicle
         * @param parkingLotType: the parking block of the vehicle.
         * @param exitTime
         * @return the amount that the vehicle has to pay.
         */
        unsigned int exitVehiclePayment(LicensePlate& licensePlate,
                unsigned int index, VehicleType parkingLotType, Time exitTime);

        /**
         * inspectOneBlock: a function that inspects one parking block to find
         * vehicles that should receive a fine/report.
         * @param inspectionTime
         * @param parkingLotType
         * @return the number of vehicles fined in that block.
         */
        int inspectOneBlock(Time inspectionTime, unsigned int parkingLotType);

        /**
         * sortArrays: a function that sorts the vehicles of all the arrays to
         * print them in a sorted way according to their parking spot.
         * @param os
         */
        void sortArrays(ostream& os) const;

        /**
         * bubbleSort: sorting function that we learned in introduction to computer science
         * which sorts a given array.
         * here it sorts it according to the parking spot.
         * @param array
         */
        void bubbleSort(UniqueArray<Vehicle,Compare> array) const;

        /**
         * swap:
         * a helping function that swaps between two indexes during the sort.
         * @param vehicle1
         * @param vehicle2
         */
        void swap ( Vehicle* vehicle1, Vehicle* vehicle2) const;

        /**
         * printAlreadyParked: a helping function to print that the vehicle is
         * already parked.
         * @param parkingLotType the parking block of the vehicle
         * @param licensePlate
         * @param entranceTime
         * @param index the parking number of the vehicle.
         */
        void printAlreadyParked(VehicleType parkingLotType,
                                            LicensePlate licensePlate,
                                            Time entranceTime,
                                            unsigned int index);





    public:

        ParkingLot(unsigned int parkingBlockSizes[]);

        ~ParkingLot() = default;

        ParkingResult enterParking(VehicleType vehicleType,
                LicensePlate licensePlate, Time entranceTime);

        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                ParkingSpot& parkingSpot) const;

        void inspectParkingLot(Time inspectionTime);

        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
    };

}


#endif //MTMPARKINGLOT_PARKINGLOT_H
