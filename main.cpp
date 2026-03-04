#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;

// Appliance structure
struct Appliance
{
    string name;
    double watts;
    double hours;
};

// Function to calculate kWh for one appliance
double calcKwh(double watts, double hours)
{
    return (watts / 1000.0) * hours;
}

// Function to calculate total daily kWh
double totalDailyKwh(Appliance appliances[], int count)
{
    double total = 0;

    for (int i = 0; i < count; i++)
    {
        total += calcKwh(appliances[i].watts, appliances[i].hours);
    }

    return total;
}

// Function to register appliance
void registerAppliance(Appliance appliances[], int &count)
{

    if (count >= MAX)
    {
        cout << "Maximum appliances reached.\n";
        return;
    }

    cout << "Enter appliance name: ";
    getline(cin, appliances[count].name);

    cout << "Enter power (watts): ";
    cin >> appliances[count].watts;

    cout << "Enter hours used per day: ";
    cin >> appliances[count].hours;
    cin.ignore();

    count++;

    cout << "Appliance registered successfully.\n";
}

// Function to view appliances
void viewAppliances(Appliance appliances[], int count)
{

    if (count == 0)
    {
        cout << "No appliances registered.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n--- Appliance List ---\n";

    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << ". "
             << appliances[i].name << " | "
             << appliances[i].watts << " W | "
             << appliances[i].hours << " hrs | "
             << calcKwh(appliances[i].watts, appliances[i].hours)
             << " kWh/day\n";
    }
}

int main()
{
    Appliance appliances[MAX];
    int count = 0;
    int choice;

    do
    {
        cout << "\nElectrical Load Monitoring System\n";
        cout << "1. Register appliance\n";
        cout << "2. View appliances\n";
        cout << "3. Billing calculation\n";
        cout << "4. Save appliances\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {

        case 1:
            registerAppliance(appliances, count);
            break;

        case 2:
            viewAppliances(appliances, count);
            break;

        case 3:
            // billing(appliances, count);
            // TODO: Use totalDailyKwh() to compute billing
            break;

        case 4:
            // saveAppliances(appliances, count);
            // TODO: Save appliances to file
            break;

        case 5:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid option\n";
        }

    } while (choice != 5);

    return 0;
}
