#include <iostream>
#include <list>
#include <memory>
#include <string>
using namespace std;

class Building {
protected:
    string name;
    int floor;

public:
    Building(const string& n, int f) : name(n), floor(f) {}
    virtual ~Building() {}

    virtual void display() const {
        cout << "Название здания: " << name << ", этажей: " << floor << endl;
    }
    void setName(const string& n) {
        name = n; 
    }
    void setFloors(int f) {
        floor = f; 
    }
};

class ResidentialBuilding : public Building {
private:
    int apartment;
public:
    ResidentialBuilding(const string& n, int f, int a): Building(n, f), apartment(a) {
    }

    void display() const override {
        cout << "Название жилого дома: " << name
            << ", этажей: " << floor
            << ", квартир: " << apartment << endl;
    }
    ~ResidentialBuilding() override {};
};

class OfficeBuilding : public Building {
private:
    int offices;

public:
    OfficeBuilding(const string& n, int f, int o): Building(n, f), offices(o) {}

    void display() const override {
        std::cout << "Название здания офисного типа: " << name
            << ", этажей: " << floor
            << ", офисов: " << offices << endl;
    }
    ~OfficeBuilding() override {};
};

void modifyBuilding(Building* b, const string& n, int f) {

    if (ResidentialBuilding* resBuilding = dynamic_cast<ResidentialBuilding*>(b)) {
        cout << "Изменение жилого здания" << endl;
    }
    else if (OfficeBuilding* offBuilding = dynamic_cast<OfficeBuilding*>(b)) {
        cout << "Изменение офисного здания" << endl;
    }
    b->setName(n);
    b->setFloors(f);
    cout << "Новое название: " << n << ", измененное количество этажей: " << f << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    list<shared_ptr<Building>> buildings;

    buildings.push_back(make_shared<ResidentialBuilding>("Дом", 5, 20));
    buildings.push_back(make_shared<OfficeBuilding>("Офис", 10, 50));
    buildings.push_back(make_shared<ResidentialBuilding>("Гостиница", 8, 30));
    buildings.push_back(make_shared<OfficeBuilding>("Технопарк", 12, 100));

    for (const auto& building : buildings) {
        building->display();
    }

    for (const auto& building : buildings) {
        modifyBuilding(building.get(), "Новое имя здания", 15);
    }

    return 0;
}