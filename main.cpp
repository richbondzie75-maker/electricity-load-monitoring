#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;

struct Appliance
{
    string name;
    double watts;
    double hours;
};

double calcKwh(double watts, double hours)
{
    return (watts / 1000.0) * hours;
}

void loadAppliances(Appliance a[], int &count)
{
    ifstream fin("appliances.txt");
    count = 0;

    if (!fin)
    {
        cout << "appliances.txt not found. Starting empty.\n";
        return;
    }

    while (fin >> ws && count < MAX)
    {
        getline(fin, a[count].name, '|');
        fin >> a[count].watts;
        fin.ignore(1); // ignore '|'
        fin >> a[count].hours;
        fin.ignore(1000, '\n');
        count++;
    }

    fin.close();
}

void saveAppliances(Appliance a[], int count)
{
    ofstream fout("appliances.txt");

    for (int i = 0; i < count; i++)
    {
        fout << a[i].name << "|"
             << a[i].watts << "|"
             << a[i].hours << endl;
    }

    fout.close();
    cout << "Appliances saved.\n";
}

void registerAppliance(Appliance a[], int &count)
{
    if (count >= MAX)
    {
        cout << "Maximum appliances reached.\n";
        return;
    }

    cout << "Enter appliance name: ";
    getline(cin, a[count].name);

    cout << "Enter watts: ";
    cin >> a[count].watts;

    cout << "Enter hours per day: ";
    cin >> a[count].hours;
    cin.ignore();

    count++;

    cout << "Appliance added.\n";
}

void viewAppliances(Appliance a[], int count)
{
    if (count == 0)
    {
        cout << "No appliances available.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n#   Name               Watts   Hours   kWh/day\n";

    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << "   "
             << a[i].name << "   "
             << a[i].watts << "   "
             << a[i].hours << "   "
             << calcKwh(a[i].watts, a[i].hours) << endl;
    }
}

void billing(Appliance a[], int count)
{
    if (count == 0)
    {
        cout << "No appliances registered.\n";
        return;
    }

    double tariff;
    cout << "Enter tariff per kWh: ";
    cin >> tariff;

    double totalDaily = 0;

    for (int i = 0; i < count; i++)
    {
        totalDaily += calcKwh(a[i].watts, a[i].hours);
    }

    double dailyCost = totalDaily * tariff;
    double monthlyCost = dailyCost * 30;

    cout << fixed << setprecision(2);
    cout << "\nTotal daily energy: " << totalDaily << " kWh\n";
    cout << "Daily cost: " << dailyCost << endl;
    cout << "Monthly cost: " << monthlyCost << endl;

    ofstream fout("billing_summary.txt", ios::app);
    fout << "Daily kWh: " << totalDaily << endl;
    fout << "Daily cost: " << dailyCost << endl;
    fout << "Monthly cost: " << monthlyCost << endl;
    fout << "---------------------------\n";
    fout.close();
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
            saveAppliances(appliances, count);
            cout << "Goodbye\n";
            break;

        default:
            cout << "Invalid option\n";
        }

    } while (choice != 5);

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 100;
const string FILE_NAME = "appliances.txt";

// Structure for appliance
struct Appliance
{
    string name;
    double watts;
    double hours;
};

// Function to calculate kWh per day
double calculateDailyKwh(Appliance a)
{
    return (a.watts / 1000) * a.hours;
}

// Save appliances to file
void saveToFile(Appliance list[], int count)
{
    ofstream file(FILE_NAME);

    if (!file)
    {
        cout << "Error saving file.\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        file << list[i].name << "|"
             << list[i].watts << "|"
             << list[i].hours << endl;
    }

    file.close();
    cout << "Appliances saved successfully!\n";
}

// Load appliances from file
void loadFromFile(Appliance list[], int &count)
{
    ifstream file(FILE_NAME);

    if (!file)
    {
        cout << "No previous data found.\n";
        return;
    }

    count = 0;

    while (file >> list[count].name >> list[count].watts >> list[count].hours)
    {
        count++;
    }

    file.close();
    cout << count << " appliances loaded.\n";
}

// Add new appliance
void addAppliance(Appliance list[], int &count)
{
    if (count >= MAX)
    {
        cout << "Maximum limit reached.\n";
        return;
    }

    cout << "Enter appliance name: ";
    cin >> list[count].name;

    cout << "Enter power in watts: ";
    cin >> list[count].watts;

    cout << "Enter usage hours per day: ";
    cin >> list[count].hours;

    count++;

    cout << "Appliance added successfully!\n";
}

// View all appliances
void viewAppliances(Appliance list[], int count)
{
    if (count == 0)
    {
        cout << "No appliances available.\n";
        return;
    }

    cout << "\n--- Appliance List ---\n";

    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << ". "
             << list[i].name << " | "
             << list[i].watts << "W | "
             << list[i].hours << " hrs/day | "
             << calculateDailyKwh(list[i]) << " kWh/day\n";
    }
}

// Billing calculation
void calculateBill(Appliance list[], int count)
{
    if (count == 0)
    {
        cout << "No appliances to calculate.\n";
        return;
    }

    double tariff;
    cout << "Enter electricity tariff per kWh: ";
    cin >> tariff;

    double totalDaily = 0;

    for (int i = 0; i < count; i++)
    {
        totalDaily += calculateDailyKwh(list[i]);
    }

    double dailyCost = totalDaily * tariff;
    double monthlyCost = dailyCost * 30;

    cout << "\nTotal Daily Usage: " << totalDaily << " kWh\n";
    cout << "Daily Cost: " << dailyCost << endl;
    cout << "Estimated Monthly Cost (30 days): " << monthlyCost << endl;
}

// Main menu
void showMenu()
{
    cout << "\n====== Electrical Load Monitoring ======\n";
    cout << "1. Add Appliance\n";
    cout << "2. View Appliances\n";
    cout << "3. Calculate Bill\n";
    cout << "4. Save to File\n";
    cout << "5. Exit\n";
    cout << "Choose option: ";
}

int main()
{
    Appliance appliances[MAX];
    int count = 0;
    int choice;

    loadFromFile(appliances, count);

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addAppliance(appliances, count);
            break;

        case 2:
            viewAppliances(appliances, count);
            break;

        case 3:
            calculateBill(appliances, count);
            break;

        case 4:
            saveToFile(appliances, count);
            break;

        case 5:
            saveToFile(appliances, count);
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
