 #include "SmartParkingSystem.h"
#include <iostream>

VehicleType getVehicleTypeFromUser() {
    std::cout << "Enter vehicle type (0: Car, 1: Bike, 2: Truck, 3: Emergency, 4: Eco-Friendly): ";
    int type;
    std::cin >> type;
    return static_cast<VehicleType>(type);
}

int main() {
    std::unordered_map<VehicleType, int> capacities = {
        {CAR, 27},
        {BIKE, 12},
        {TRUCK, 4},
        {EMERGENCY, 2},
        {ECO_FRIENDLY, 8}
    };

    ParkingLot lot(capacities);
    int choice;

    while (true) {
        std::cout << "\n----- Smart Parking System CLI -----\n";
        std::cout << "1. Enter Vehicle\n";
        std::cout << "2. Exit Vehicle\n";
        std::cout << "3. Display Status\n";
        std::cout << "4. Exit Program\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string plate;
            std::cout << "Enter vehicle plate number: ";
            std::cin >> plate;
            VehicleType type = getVehicleTypeFromUser();
            lot.enter({plate, type});
        } else if (choice == 2) {
            std::string plate;
            std::cout << "Enter vehicle plate number to exit: ";
            std::cin >> plate;
            lot.exit(plate);
        } else if (choice == 3) {
            lot.displayStatus();
        } else if (choice == 4) {
            std::cout << "Exiting. Thank you for using Smart Parking System.\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

