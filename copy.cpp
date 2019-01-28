#include <iostream>
using namespace std;

class Car
{
public:
    virtual void drive() { cout << "Driving!\n"; }
    virtual bool drive(const string& dest) // Overloading / överlagring
    {
        cout << "Driving to " << dest << endl;
        return true;
    }

    string getLicensePlateNumber() { return "1337"; }
    void getLicensePlateNumber(string& name) { name = "1337"; }
};

class RacingCar : public Car
{
public:
    virtual void drive() override
    {
        cout << "Racing!\n";
    } // Override / överskuggning
    virtual bool drive(const string& dest) override
    {
        Car::drive();
        cout << "Racing to " << dest << endl;
        return true;
    }

    string fancyName;
};


int main()
{
    Car* ferrari = new RacingCar();
    ferrari->drive();
    ferrari->drive("Germany");
    // drive()
    // drive(const string&)
    // drive(string&)

    string name;
    ferrari->getLicensePlateNumber(name);

}