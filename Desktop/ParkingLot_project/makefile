CC = g++
OBJS = MtmParkingLot.o ParkingLot.o ParkingLotPrinter.o ParkingSpot.o Time.o Vehicle.o
EXEC = MtmParkingLot
DEBUG_FLAG = -DNDEBUG -g
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors 

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h UniqueArrayImp.h Vehicle.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h ParkingLotPrinter.h Time.h ParkingSpot.h UniqueArray.h UniqueArrayImp.h Vehicle.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Time.o: Time.cpp Time.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Vehicle.o: Vehicle.cpp Vehicle.h Time.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)