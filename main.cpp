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

// Polished view function with headings and alignment
void viewAppliances(Appliance appliances[], int count)
{
    if (count == 0)
    {
        cout << "No appliances registered.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n#   Name                     Watts   Hours   kWh/day\n";
    cout << "------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << setw(2) << i + 1 << "  "
             << left << setw(24) << appliances[i].name
             << right << setw(6) << appliances[i].watts << "  "
             << setw(5) << appliances[i].hours << "  "
             << setw(7) << calcKwh(appliances[i].watts, appliances[i].hours) << endl;
    }
}

// Function to calculate billing and log it to a file
void billing(Appliance appliances[], int count)
{
    if (count == 0)
    {
        cout << "No appliances registered.\n";
        return;
    }

    double tariff;
    cout << "Enter electricity tariff per kWh: ";
    cin >> tariff;

    double totalEnergy = totalDailyKwh(appliances, count);
    double dailyCost = totalEnergy * tariff;
    double monthlyCost = dailyCost * 30;

    cout << fixed << setprecision(2);
    cout << "\n--- Billing Summary ---\n";
    cout << "Total daily energy: " << totalEnergy << " kWh\n";
    cout << "Daily cost: " << dailyCost << endl;
    cout << "Estimated monthly cost: " << monthlyCost << endl;

    ofstream fout("billing_summary.txt", ios::app);
    fout << "Daily kWh: " << totalEnergy << endl;
    fout << "Daily cost: " << dailyCost << endl;
    fout << "Monthly cost: " << monthlyCost << endl;
    fout << "---------------------------\n";
    fout.close();

    cout << "Billing summary saved to billing_summary.txt\n";
}

// Function to load appliances from file
void loadAppliances(Appliance appliances[], int &count)
{
    ifstream fin("appliances.txt");
    count = 0;

    if (!fin)
    {
        cout << "appliances.txt not found. Starting with empty list.\n";
        return;
    }

    while (fin >> ws && count < MAX)
    {
        getline(fin, appliances[count].name, '|');
        fin >> appliances[count].watts;
        fin.ignore(1, '|');
        fin >> appliances[count].hours;
        fin.ignore(1000, '\n');
        count++;
    }

    fin.close();
    cout << count << " appliances loaded from file.\n";
}

// Function to save appliances to file
void saveAppliances(Appliance appliances[], int count)
{
    ofstream fout("appliances.txt");
    for (int i = 0; i < count; i++)
    {
        fout << appliances[i].name << "|"
             << appliances[i].watts << "|"
             << appliances[i].hours << endl;
    }
    fout.close();
    cout << "Appliances saved to file.\n";
}

int main()
{
    Appliance appliances[MAX];
    int count = 0;
    int choice;

    loadAppliances(appliances, count);

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
            billing(appliances, count);
            break;
        case 4:
            saveAppliances(appliances, count);
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
