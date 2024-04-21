cmake_minimum_required(VERSION 3.15)
project(ParkingLot)

set(CMAKE_CXX_STANDARD 11)

add_executable(ParkingLot UniqueArray.h ParkingSpot.cpp Vehicle.cpp ParkingLot.cpp ParkingLotTypes.h ParkingLotPrinter.cpp MtmParkingLot.cpp Time.cpp)