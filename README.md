# Electrical Load Monitoring System

## Overview

The Electrical Load Monitoring System is a simple C++ console application that helps monitor household electricity usage. It allows users to register appliances, calculate daily energy consumption, and estimate electricity bills based on a given tariff rate.

This project demonstrates basic C++ concepts such as structures, arrays, functions, loops, and file handling.

---

## Objectives

- Practice structured programming in C++
- Implement file input and output
- Perform basic energy consumption calculations
- Build a menu-driven console application

---

## Features

- Add new appliances (name, watts, hours used per day)
- View all registered appliances
- Calculate kWh per appliance automatically
- Calculate total daily energy usage
- Estimate daily and monthly electricity costs
- Save appliance data to a file
- Load saved appliance data when the program starts

---

## How the Program Works

Each appliance stores:

- Name
- Power rating (in watts)
- Usage time per day (in hours)

### Energy Calculation

Daily energy consumption is calculated using:

kWh = (Watts / 1000) × Hours per day

Example:

If an appliance uses 1000 watts for 2 hours:

(1000 / 1000) × 2 = 2 kWh per day

### Billing Calculation

After calculating total daily energy usage:

Daily Cost = Total kWh × Tariff  
Monthly Cost = Daily Cost × 30

The monthly estimate is based on 30 days.

---

## Program Structure

The program uses:

- A `struct` to store appliance information
- An array that can store up to 100 appliances
- Separate functions for:
  - Adding appliances
  - Viewing appliances
  - Calculating billing
  - Saving data to file
  - Loading data from file
- File handling using `fstream`

---

## Files Used

- `main.cpp` – main source file
- `appliances.txt` – stores saved appliance data
- `billing_summary.txt` – stores billing results (if generated)

### Data Format (appliances.txt)

Appliance data is stored in this format:

ApplianceName|Watts|Hours

Example:

Fan|75|8  
TV|120|5  
Refrigerator|200|24

---

## Compile and Run

### Compile (using g++)

g++ main.cpp -o monitor

### Run

On macOS/Linux:
./monitor

On Windows:
monitor.exe

---

## Limitations

- Maximum of 100 appliances
- Monthly calculation assumes 30 days
- Console-based (no graphical interface)
- No option to edit or delete appliances

---

## Possible Improvements

- Add edit and delete functionality
- Use vectors instead of fixed-size arrays
- Add yearly cost estimation
- Improve table formatting
- Add input validation
- Create a graphical user interface

---

## Conclusion

This project is a basic electricity usage monitoring system written in C++. It helps users understand how energy consumption is calculated while also demonstrating core programming concepts such as structures, arrays, and file handling.
