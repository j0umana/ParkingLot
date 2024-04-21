#include <iostream>
#include "ParkingLot.h"
#define INITIAL_MOTORBIKE_PAYMENT 10
#define EXTRA_MOTORBIKE_PAYMENT 5
#define INITIAL_CAR_PAYMENT 20
#define EXTRA_CAR_PAYMENT 10
#define CONSTANT_HANDICAPPED_PAYMENT 15
#define MAX_COUNTING_HOURS 6
#define FINE_VALUE 250
#define TYPES_NUMBER 3

using namespace MtmParkingLot;
using namespace ParkingLotUtils;

ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
        motorbikeArray(parkingBlockSizes[MOTORBIKE]),
        handicappedArray(parkingBlockSizes[HANDICAPPED]),
        carArray(parkingBlockSizes[CAR])
{

}

//------------------------------------------------------------------------------

bool ParkingLot::checkIfParkingAvailable(VehicleType vehicleType,
                                         VehicleType& availableParkingBlock,
                                         unsigned int& index){
    if(vehicleType == MOTORBIKE) {
        if(motorbikeArray.getSize() != motorbikeArray.getCount()) {
            availableParkingBlock = MOTORBIKE;
            motorbikeArray.returnFirstNull(index);
            return true;
        }
        return false;
    }
    if(vehicleType == HANDICAPPED) {
        if (handicappedArray.getSize() != handicappedArray.getCount()) {
            availableParkingBlock = HANDICAPPED;
            handicappedArray.returnFirstNull(index);
            return true;
        }
        if (carArray.getSize() != carArray.getCount()) {
            carArray.returnFirstNull(index);
            availableParkingBlock = CAR;
            return true;
        }
        return false;
    }
    if(vehicleType == CAR){
        if(carArray.getSize() != carArray.getCount()) {
            carArray.returnFirstNull(index);
            availableParkingBlock = CAR;
            return true;
        }
        return false;
    }
    return false; //shouldn't get here;
}

//------------------------------------------------------------------------------
bool ParkingLot::findVehicleByPlateNumber(LicensePlate& plateNumber,
                                          unsigned int& index,VehicleType& type, VehicleType& parkingLotType){
    VehicleType trueType=MOTORBIKE;
    for(int i=0;i<TYPES_NUMBER;i++){
        if(findVehicleInBlock(plateNumber,index,(VehicleType)i,trueType)) {
            type=trueType;
            parkingLotType=(VehicleType)i;
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

bool ParkingLot::findVehicleInBlock(LicensePlate& plateNumber,
                                    unsigned int& index,VehicleType parkingType, VehicleType& true_type){
    UniqueArray<Vehicle,Compare>* currentArray=&motorbikeArray;
    if(parkingType==MOTORBIKE) {
        currentArray=&motorbikeArray;
    }
    if(parkingType==HANDICAPPED) {
        currentArray=&handicappedArray;
    }
    if(parkingType==CAR) {
        currentArray=&carArray;
    }

    for(unsigned int i=0;i<currentArray->getSize();i++){
        if((*currentArray).findElementByIndex(i)== nullptr)
            continue;
        Vehicle* currentVehicle=(*currentArray).findElementByIndex(i);
        if(currentVehicle->getPlateNumber()==plateNumber){
            index=i;
            true_type=currentVehicle->getVehicleType();
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

void ParkingLot::enterVehicle(Vehicle &vehicle,
                              VehicleType parkingLotType, LicensePlate& licensePlate){
    UniqueArray<Vehicle,Compare>* currentArray=&motorbikeArray;
    if(parkingLotType == MOTORBIKE)
        currentArray=&motorbikeArray;
    if(parkingLotType == HANDICAPPED)
        currentArray=&handicappedArray;
    if(parkingLotType == CAR)
        currentArray=&carArray;

    currentArray->insert(vehicle);
    ParkingLotPrinter::printEntrySuccess(std::cout,
                                         vehicle.vehicleGetParkingSpot());
}

//------------------------------------------------------------------------------

bool ParkingLot::checkIfVehicleAlreadyParked(VehicleType& parkingLotType,
                                             Vehicle& vehicle, unsigned int& index){
    if(motorbikeArray.getIndex(vehicle,index)) {
        parkingLotType=MOTORBIKE;
        return true;
    }



    if(handicappedArray.getIndex(vehicle,index)){
        parkingLotType=HANDICAPPED;
        return true;
    }

    if(carArray.getIndex(vehicle,index)) {
        parkingLotType=CAR;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
                                       LicensePlate licensePlate, Time entranceTime) {

    VehicleType availableParkingBlock = MOTORBIKE;
    Vehicle tempVehicle(vehicleType, licensePlate, entranceTime,
                        MOTORBIKE, 0, false);

    unsigned int i1 = 0,i2=0;
    VehicleType parkingLotType;

    if (checkIfVehicleAlreadyParked(parkingLotType,tempVehicle, i2)){
        printAlreadyParked(parkingLotType, licensePlate, entranceTime, i2);
        return VEHICLE_ALREADY_PARKED;
    }

    if (!checkIfParkingAvailable(vehicleType, availableParkingBlock,i1)){
        ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate,
                                        entranceTime);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;
    }
    ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate,
                                    entranceTime);
    Vehicle newVehicle(vehicleType, licensePlate, entranceTime
            ,availableParkingBlock, i1, false);

    enterVehicle(newVehicle, availableParkingBlock, licensePlate);
    return SUCCESS;
}

//------------------------------------------------------------------------------
void ParkingLot::printAlreadyParked(VehicleType parkingLotType,
                                    LicensePlate licensePlate,
                                    Time entranceTime,
                                    unsigned int i2) {
    if (parkingLotType == MOTORBIKE) {
        ParkingLotPrinter::printVehicle(std::cout,
                                        MOTORBIKE, licensePlate,
          motorbikeArray.findElementByIndex(i2)->getEntranceTime());
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
     motorbikeArray.findElementByIndex(i2)->vehicleGetParkingSpot());
    }
    if (parkingLotType == HANDICAPPED) {
        ParkingLotPrinter::printVehicle(std::cout, HANDICAPPED,
                                        licensePlate,
        handicappedArray.findElementByIndex(i2)->getEntranceTime());
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
   handicappedArray.findElementByIndex(i2)->vehicleGetParkingSpot());
    }
    if (parkingLotType == CAR) {
        ParkingLotPrinter::printVehicle(std::cout,
      carArray.findElementByIndex(i2)->getVehicleType(),licensePlate,
          carArray.findElementByIndex(i2)->getEntranceTime());
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
         carArray.findElementByIndex(i2)->vehicleGetParkingSpot());
    }
}

//------------------------------------------------------------------------------
unsigned int ParkingLot::exitVehiclePayment(LicensePlate& licensePlate,
                                            unsigned int index, VehicleType parkingLotType,Time exitTime){

    unsigned int payment=0;
    if(parkingLotType == MOTORBIKE) {
        payment=calculateMotorbikePayment(
                *motorbikeArray.findElementByIndex(index),exitTime);
    }
    if(parkingLotType == HANDICAPPED) {
        payment=calculateHandicappedPayment
                (*handicappedArray.findElementByIndex(index), exitTime);
    }

    if(parkingLotType == CAR) {
        if(carArray.findElementByIndex(index)->getVehicleType()==HANDICAPPED){
            payment =
           calculateHandicappedPayment(*carArray.findElementByIndex(index),
                                                exitTime);
        }
        else if(carArray.findElementByIndex(index)->getVehicleType()==CAR) {
            payment=calculateCarPayment(*carArray.findElementByIndex(index),
                                          exitTime);
        }
    }
    return payment;
}

//------------------------------------------------------------------------------

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime){
    unsigned int vehicleIndex=0,payment=0;
    VehicleType type,parkingLotType;
    if(!findVehicleByPlateNumber(licensePlate,vehicleIndex,
                                 type,parkingLotType)){
        ParkingLotPrinter::printExitFailure(std::cout,licensePlate);
        return VEHICLE_NOT_FOUND;
    }
    payment=
            exitVehiclePayment(licensePlate,vehicleIndex,parkingLotType,exitTime);
    if(parkingLotType == MOTORBIKE){
        ParkingLotPrinter::printVehicle(std::cout,type,licensePlate,
motorbikeArray.findElementByIndex(vehicleIndex)->getEntranceTime());
        ParkingSpot p1 = motorbikeArray.findElementByIndex(vehicleIndex)->
                vehicleGetParkingSpot();
        ParkingLotPrinter::printExitSuccess(std::cout,p1,exitTime,payment);
motorbikeArray.remove(*motorbikeArray.findElementByIndex(vehicleIndex));
    }
    if(parkingLotType == HANDICAPPED){
        ParkingLotPrinter::printVehicle(std::cout,type,licensePlate,
    handicappedArray.findElementByIndex(vehicleIndex)->
    getEntranceTime());
        ParkingSpot p1=
     handicappedArray.findElementByIndex(vehicleIndex)->vehicleGetParkingSpot();
        ParkingLotPrinter::printExitSuccess(std::cout,p1,exitTime,payment);
        handicappedArray.remove
        (*handicappedArray.findElementByIndex(vehicleIndex));
    }
    if(parkingLotType == CAR){
        ParkingLotPrinter::printVehicle(std::cout,type,licensePlate,
      carArray.findElementByIndex(vehicleIndex)->getEntranceTime());
        ParkingSpot p1=carArray.findElementByIndex(vehicleIndex)
                ->vehicleGetParkingSpot();
        ParkingLotPrinter::printExitSuccess(std::cout,p1,exitTime,payment);
        carArray.remove(*carArray.findElementByIndex(vehicleIndex));
    }
    return SUCCESS;
}

//------------------------------------------------------------------------------

unsigned int ParkingLot::calculateMotorbikePayment(Vehicle &vehicle,
                                                   Time exitTime){
    unsigned int finePayment=0;
    if(vehicle.isReported())
        finePayment=FINE_VALUE;
    Time totalTime=exitTime-vehicle.getEntranceTime();
    if(totalTime.toHours()==0){
        return 0;
    }
    if(totalTime.toHours()==1){
        return INITIAL_MOTORBIKE_PAYMENT+finePayment;
    }
    if(totalTime.toHours()>=2 && totalTime.toHours()<=MAX_COUNTING_HOURS){
        return (INITIAL_MOTORBIKE_PAYMENT +
                (totalTime.toHours()-1)*EXTRA_MOTORBIKE_PAYMENT+finePayment);
    }

    return (INITIAL_MOTORBIKE_PAYMENT +
            (MAX_COUNTING_HOURS-1)*(EXTRA_MOTORBIKE_PAYMENT)+finePayment);
}

//------------------------------------------------------------------------------

unsigned int ParkingLot::calculateCarPayment(Vehicle &vehicle, Time exitTime){
    unsigned int finePayment=0;
    if(vehicle.isReported())
        finePayment=FINE_VALUE;
    Time totalTime=exitTime-vehicle.getEntranceTime();
    if(totalTime.toHours()==0){
        return 0;
    }
    if(totalTime.toHours()==1){
        return INITIAL_CAR_PAYMENT+finePayment;
    }
    if(totalTime.toHours()>=2 && totalTime.toHours()<=MAX_COUNTING_HOURS){
        return (INITIAL_CAR_PAYMENT +
                (totalTime.toHours()-1)*EXTRA_CAR_PAYMENT+finePayment);
    }

    return (INITIAL_CAR_PAYMENT +
            (MAX_COUNTING_HOURS-1)*(EXTRA_CAR_PAYMENT)+finePayment);
}

//------------------------------------------------------------------------------
unsigned int ParkingLot::calculateHandicappedPayment(Vehicle &vehicle,
                                                     Time exitTime) {
    unsigned int finePayment=0;
    if(vehicle.isReported()) {
        finePayment = FINE_VALUE;
    }
    Time totalTime = exitTime - vehicle.getEntranceTime();
    if (totalTime.toHours() == 0) {
        return 0;
    }
    return CONSTANT_HANDICAPPED_PAYMENT+finePayment;
}

//------------------------------------------------------------------------------

ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
                                         ParkingSpot& parkingSpot) const{

    Vehicle vehicle(CAR,licensePlate,0,
                    HANDICAPPED,0,false);
    for(unsigned int i=0; i<motorbikeArray.getSize();i++){
        if(Compare() (vehicle ,*motorbikeArray.constFindElementByIndex(i))) {
parkingSpot=motorbikeArray.findElementByIndex(i)->vehicleGetParkingSpot();
            return SUCCESS;
        }
    }

    for(unsigned int i=0; i<handicappedArray.getSize();i++){
    if(Compare()(vehicle,*handicappedArray.constFindElementByIndex(i))){
  parkingSpot=handicappedArray.findElementByIndex(i)->vehicleGetParkingSpot();
            return SUCCESS;
        }
    }

    for(unsigned int i=0; i<carArray.getSize();i++){
        if(Compare() (vehicle ,*carArray.constFindElementByIndex(i))) {
            parkingSpot=carArray.findElementByIndex(i)->vehicleGetParkingSpot();
            return SUCCESS;
        }
    }
    return VEHICLE_NOT_FOUND;
}

//------------------------------------------------------------------------------
namespace MtmParkingLot {
    ostream &operator<<(ostream &os, const ParkingLot &parkingLot) {
        ParkingLotPrinter::printParkingLotTitle(os);
        parkingLot.sortArrays(os);
        return os;
    }
}
//------------------------------------------------------------------------------
int ParkingLot::inspectOneBlock(Time inspectionTime,
                                unsigned int parkingLotType) {
    int counter = 0;
    UniqueArray<Vehicle, Compare> *currentArray = &motorbikeArray;
    if ((VehicleType) parkingLotType == MOTORBIKE)
        currentArray = &motorbikeArray;
    if ((VehicleType) parkingLotType == HANDICAPPED)
        currentArray = &handicappedArray;
    if ((VehicleType) parkingLotType == CAR)
        currentArray = &carArray;

    for (unsigned int i = 0; i < currentArray->getSize(); i++) {
        if ((*(currentArray)).findElementByIndex(i) == nullptr) {
            continue;
        }

        Time differenceTime =inspectionTime -
                ((*(currentArray)).findElementByIndex(i)->getEntranceTime());

        if (differenceTime.toHours() > 24) {
            if (!((*(currentArray)).findElementByIndex(i)->isReported())) {
                counter++;
                (*(currentArray)).findElementByIndex(i)->UpdateReported();
            }
        }
    }
    return counter;
}


//------------------------------------------------------------------------------
void ParkingLot::inspectParkingLot(Time inspectionTime){
    int counter=0;
    for(unsigned int i=0;i<TYPES_NUMBER;i++){
        counter+=inspectOneBlock(inspectionTime,i);
    }

    ParkingLotPrinter::printInspectionResult(std::cout,
                                             inspectionTime,counter);

}

//------------------------------------------------------------------------------

void ParkingLot::sortArrays(ostream& os) const {
    unsigned int size = motorbikeArray.getSize() + handicappedArray.getSize() +
                        carArray.getSize();
    UniqueArray<Vehicle, Compare> newArray(size);
    for (unsigned int i = 0; i < motorbikeArray.getSize(); i++) {
        if (motorbikeArray.findElementByIndex(i) == nullptr)
            continue;
        newArray.insert(*motorbikeArray.constFindElementByIndex(i));
    }
    for (unsigned int i = 0; i < handicappedArray.getSize(); i++) {
        if (handicappedArray.findElementByIndex(i) == nullptr)
            continue;
        newArray.insert(*handicappedArray.constFindElementByIndex(i));
    }
    for (unsigned int i = 0; i < carArray.getSize(); i++) {
        if (carArray.findElementByIndex(i) == nullptr)
            continue;
        newArray.insert(*carArray.constFindElementByIndex(i));
    }
    bubbleSort(newArray);
    for (unsigned int i = 0; i < size; i++) {
        if (newArray.findElementByIndex(i) == nullptr)
            continue;
        const Vehicle *vehicle = newArray.constFindElementByIndex(i);
        ParkingLotPrinter::printVehicle(os, vehicle->getVehicleType(),
                                        vehicle->getPlateNumber(),
                                        vehicle->getEntranceTime());
        ParkingLotPrinter::printParkingSpot(os,
                                            vehicle->vehicleGetParkingSpot());
    }
}

//------------------------------------------------------------------------------

void ParkingLot::bubbleSort(UniqueArray<Vehicle,Compare> array) const
{
    unsigned int i, j;
    bool swapped;
    if(array.getCount()==0)
        return;
    for (i = 0; i < array.getCount()-1; i++)
    {
        swapped = false;
        for (j = 0; j < array.getCount()-i-1; j++)
        {
            if (array.findElementByIndex(j+1)->vehicleGetParkingSpot()
                < array.findElementByIndex(j)->vehicleGetParkingSpot())
            {
                swap(array.findElementByIndex(j), array.findElementByIndex(j+1));
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

//------------------------------------------------------------------------------
void ParkingLot::swap( Vehicle* vehicle1, Vehicle* vehicle2) const
{
    Vehicle *vehicle3=vehicle1;
    vehicle1=vehicle2;
    vehicle2=vehicle3;

}
//------------------------------------------------------------------------------
