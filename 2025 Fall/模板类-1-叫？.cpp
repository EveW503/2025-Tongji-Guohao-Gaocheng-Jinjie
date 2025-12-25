#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Animal
{
public:
    Animal(const string &name) : name(name) {}
    virtual void makeSound() const = 0;
    virtual ~Animal() {}
    string getName() const
    {
        return name;
    }

protected:
    string name;
};

class Dog : public Animal
{
public:
    /****************** TODO ******************/
    // 实现派生类 Dog
    Dog(const string &name) : Animal(name) {};
    void makeSound() const override
    {
        cout << name << " says: Woof! Woof!" << endl;
    }
    /**************** TODO-END ****************/
};

class Cat : public Animal
{
public:
    /****************** TODO ******************/
    // 实现派生类 Cat
    Cat(const string &name) : Animal(name) {};
    void makeSound() const override
    {
        cout << name << " says: Meow!" << endl;
    }
    /**************** TODO-END ****************/
};

class Cow : public Animal
{
public:
    /****************** TODO ******************/
    // 实现派生类 Cow
    Cow(const string &name) : Animal(name) {};
    void makeSound() const override
    {
        cout << name << " says: Moo!" << endl;
    }
    /**************** TODO-END ****************/
};

int main()
{
    vector<unique_ptr<Animal>> animals;

    int choice;
    string animalName;
    cout << "Please enter the type of animal (1 for Dog, 2 for Cat, 3 for Cow). Enter 0 to stop." << endl;
    while (true)
    {
        cout << "Choice: ";
        cin >> choice;
        if (choice == 0)
        {
            break;
        }
        cout << "Enter the name of the animal: ";
        cin.ignore();
        getline(cin, animalName);
        switch (choice)
        {
        /****************** TODO ******************/
        // 根据用户输入的 choice 创建相应的派生类对象并添加到 animals 中
        case 1:
            // 使用 make_unique 创建 Dog 对象并加入 vector
            animals.push_back(make_unique<Dog>(animalName));
            break;
        case 2:
            animals.push_back(make_unique<Cat>(animalName));
            break;
        case 3:
            animals.push_back(make_unique<Cow>(animalName));
            break;
        /**************** TODO-END ****************/
        default:
            cout << "Invalid choice." << endl;
        }
    }

    for (const auto &animal : animals)
    {
        animal->makeSound();
    }

    return 0;
}