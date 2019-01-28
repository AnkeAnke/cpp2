#include <iostream>
#include <string>

using namespace std;

struct Color
{
    Color(const string& name) : name(name) {}
    
    string name;
};

class Car
{
public:
    Car(const string& color) 
    {
        this->color = new Color(color);
        cout << "Default construction\n";
    }
    ~Car () // 1
    {
        delete color;
    }
    Car(const Car& other) // 2
    {
        color = new Color(*other.color);
    }
    Car& operator = (const Car& other) // 3
    {
        delete color;
        color = new Color(*other.color);
        return *this;
    }
    Car& operator = (const Color& other)
    {
        color = new Color(other);
    }

    Color* color;
};

Car makeNewCar()
{
    Car newOne = Car("Shiny new");
    return newOne;
}

int main()
{
    Car toyota("Turquoise"), audi("Amber"); // construction

Color blue("Blue");

    toyota = blue;
    Car volvo(std::move(makeNewCar()));
    {
        Car volkwagen = toyota; // ctor
    } // dtor

} // destruction