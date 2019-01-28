// Deadly Diamond of Death
#include <iostream>

class Animal
{
public:
    Animal() : name("x") {}
    virtual void makeSound() {std::cout << "...\n"; }

    std::string name;
};

class Fish : public Animal
{
    public:
    Fish() { name = "nemo"; }
    virtual void makeSound() override {std::cout << "blubb\n"; }
};

class Mammal : public Animal
{
public:
    Mammal() { name = "björn"; }
    virtual void makeSound() override {std::cout << "hello from " << name; }
};

class Dolphin : public Fish, public Mammal
{
    public:
    virtual void makeSound() override
    {
        std::cout << "Hej, my name is " << Fish::name;
    }
};

int main()
{
    Fish nemo;
    nemo.makeSound();

    Mammal bjorn;
    bjorn.makeSound();

    Dolphin flipper;
    flipper.makeSound();
}