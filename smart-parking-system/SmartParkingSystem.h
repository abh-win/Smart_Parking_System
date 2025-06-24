 #ifndef SMART_PARKING_H
#define SMART_PARKING_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>

using std::ceil;

enum VehicleType {
    CAR,
    BIKE,
    TRUCK,
    EMERGENCY,
    ECO_FRIENDLY
};

struct Vehicle {
    std::string plateNumber;
    VehicleType type;
};

struct ParkingTicket {
    std::string plateNumber;
    std::time_t entryTime;
    std::time_t ttlExpiry; // TTL support
    double ratePerHour;
    bool isDiscounted;
    int spotNumber;
};

class ParkingLot {
private:
    int capacity;
    int occupied;
    std::unordered_map<std::string, ParkingTicket> activeTickets;
    std::unordered_map<std::string, bool> membershipRegistry;

    std::unordered_map<VehicleType, double> baseRates = {
        {CAR, 50.0},
        {BIKE, 20.0},
        {TRUCK, 80.0},
        {EMERGENCY, 0.0},
        {ECO_FRIENDLY, 40.0}
    };

    double membershipDiscount = 0.20; // 20% discount
    const int TIME_SCALE = 30; // 30 seconds = 1 hour
    int ttlDurationSeconds = 2 * 24 * TIME_SCALE; // TTL set to 2 days (scaled)

    std::unordered_map<VehicleType, std::stack<int>> freeSpots;
    std::unordered_map<std::string, VehicleType> plateToType;

public:
    ParkingLot(const std::unordered_map<VehicleType, int>& capacitiesPerType) {
        capacity = 0;
        occupied = 0;
        for (const auto& [type, cap] : capacitiesPerType) {
            for (int i = 1; i <= cap; ++i) {
                freeSpots[type].push(i);
            }
            capacity += cap;
        }
    }

    char getTypeChar(VehicleType type) {
    switch (type) {
        case CAR: return 'A';
        case BIKE: return 'B';
        case TRUCK: return 'C';
        case EMERGENCY: return 'D';
        case ECO_FRIENDLY: return 'E';
        default: return '?';
    }
}

    bool enter(Vehicle vehicle) {
        if (freeSpots[vehicle.type].empty()) {
            std::cout << "No parking spot available for this vehicle type!" << std::endl;
            return false;
        }

        double rate = baseRates[vehicle.type];
        bool discount = false;

        if (membershipRegistry.count(vehicle.plateNumber) && rate > 0) {
            rate = rate * (1 - membershipDiscount);
            discount = true;
        }

        int spotNumber = freeSpots[vehicle.type].top();
        freeSpots[vehicle.type].pop();
        plateToType[vehicle.plateNumber] = vehicle.type;

        std::time_t now = std::time(nullptr);

        activeTickets[vehicle.plateNumber] = {
            vehicle.plateNumber,
            now,
            now + ttlDurationSeconds, // TTL expiry set
            rate,
            discount,
            spotNumber
        };

        occupied++;
        std::cout << "Vehicle " << vehicle.plateNumber << " entered. Rate: Rs. " << rate << "/hr";
        if (discount) {
            std::cout << " (including membership discount)";
        }
        std::cout << ". Assigned spot: " <<getTypeChar(plateToType[vehicle.plateNumber])<<spotNumber << "\n";
        return true;
    }

    void exit(const std::string& plateNumber) {
        if (activeTickets.find(plateNumber) == activeTickets.end()) {
            std::cout << "No such vehicle found." << std::endl;
            return;
        }

        ParkingTicket ticket = activeTickets[plateNumber];
        std::time_t now = std::time(nullptr);
        double hours = std::difftime(now, ticket.entryTime) / TIME_SCALE;
        double totalCharge = std::ceil(hours) * ticket.ratePerHour;

        std::cout << "Vehicle " << plateNumber << " stayed for " << std::fixed << std::setprecision(2) << hours << " hours.\n";
        if (now > ticket.ttlExpiry) {
            std::cout << "NOTE: TTL expired. Vehicle overstayed.\n";
        }
        std::cout << "Total charge: Rs. " << std::ceil(totalCharge) << "\n";
        std::cout << "Spot number " <<getTypeChar(plateToType[plateNumber])<<ticket.spotNumber << " is now available.\n";

        // Ask for membership only if not already registered
        if (membershipRegistry.find(plateNumber) == membershipRegistry.end()) {
            char response;
            std::cout << "Would you like to register for a membership for future discounts (y/n)? ";
            std::cin >> response;
            if (response == 'y' || response == 'Y') {
                membershipRegistry[plateNumber] = true;
                std::cout << "Membership registered. You will get a " << (membershipDiscount * 100) << "% discount from now on.\n";
            }
        }

        freeSpots[plateToType[plateNumber]].push(ticket.spotNumber);
        activeTickets.erase(plateNumber);
        plateToType.erase(plateNumber);
        occupied--;
    }

    void displayStatus()  {
        std::cout << "\nOccupied: " << occupied << "/" << capacity << "\n";
        std::cout << "Currently Parked Vehicles:\n";
        for (auto& pair : activeTickets) {
            std::string plateNumber = pair.first;
            std::cout << " - " << pair.first << " (Rate/hr: Rs. " << pair.second.ratePerHour
                      << ", Spot: " <<getTypeChar(plateToType[plateNumber])<< pair.second.spotNumber << ")";
            if (std::time(nullptr) > pair.second.ttlExpiry) {
                std::cout << " [TTL EXPIRED]";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
};

#endif

