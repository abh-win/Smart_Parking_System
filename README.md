 # Smart Parking System in C++

A command-line based Smart Parking System simulation developed in C++. It supports multiple vehicle types, dynamic pricing, and membership-based discounts, closely mimicking real-world smart parking logic.

## Features

- Supports five vehicle types: Car, Bike, Truck, Emergency, Eco-Friendly
- Each vehicle type has a separate pool of numbered parking spots (e.g., A1 to A27 for cars)
- Membership system offering 20% discount for registered vehicles
- TTL (Time-To-Live) of 2 days for a vehicle; alerts if TTL is exceeded
- Scaled time system: 30 seconds = 1 hour for quick testing
- CLI-based interaction for entry, exit, and current parking status
- Detailed ticket generation including entry time, rate, and spot allocation

## Uniqueness & Real-World Relevance

This project stands out due to its:

- **Realistic modeling of modern parking systems**, including differentiated pricing based on vehicle type and sustainability/emergency considerations.
- **Membership discount integration**, reflecting customer loyalty programs in real parking solutions.
- **TTL feature**, simulating overstay detection, which is commonly used in real-world smart parking systems to track parking violations or extended use.
- **Spot allocation tracking** using vehicle-type-specific stacks, allowing fast retrieval and release of parking spots — an efficient simulation of automated spot management.

Unlike many basic parking simulations, this system goes beyond simple entry/exit by implementing **real-world constraints**, **rate variability**, and **custom scalability**, making it ideal for academic, interview, or prototype use.

##  Technologies Used

- C++17 Standard
- STL (unordered_map, stack, queue, etc.)
- <ctime>, <iomanip>, <cmath>

##  How to Compile

Use g++ or any modern C++ compiler:

```bash
g++ main.cpp -o parking
./parking
```

Make sure `SmartParkingSystem.h` is in the same directory.

##  Files

- `main.cpp` – Command-line driver interface
- `SmartParkingSystem.h` – Header file with all class/logic
- `README.md` – Project documentation

##  Sample Usage

1. Run the executable.
2. Enter a vehicle plate and select type.
3. When a vehicle exits, you'll see charges and membership options.
4. View current parking status with assigned spot numbers and TTL alerts.

##  License

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Author
## Abhinav Jha
