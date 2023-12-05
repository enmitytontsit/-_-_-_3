#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Базовый класс для представления блюда
class MenuItem {
protected:
    std::string name;
    double price;

public:
    MenuItem(const std::string& _name, double _price) : name(_name), price(_price) {}

    virtual void printInfo() const {
        std::cout << "Название: " << name << ", Цена: " << price << std::endl;
    }

    virtual std::string getInfo() const {
        return "Название: " + name + ", Цена: " + std::to_string(price);
    }

    double getPrice() const {
        return price;
    }
};

// Шаблонный класс Pair для связи характеристик блюда
template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(const T1& _first, const T2& _second) : first(_first), second(_second) {}

    T1 getFirst() const {
        return first;
    }

    T2 getSecond() const {
        return second;
    }
};

// Класс для представления блюда "Пицца"
class Pizza : public MenuItem {
private:
    std::string topping;

public:
    Pizza(const std::string& _name, double _price, const std::string& _topping) : MenuItem(_name, _price), topping(_topping) {}

    void printInfo() const override {
        std::cout << "Название: " << name << ", Цена: " << price << ", Топпинг: " << topping << std::endl;
    }

    std::string getInfo() const override {
        return "Название: " + name + ", Цена: " + std::to_string(price) + ", Топпинг: " + topping;
    }
};

// Класс для представления блюда "Суп"
class Soup : public MenuItem {
private:
    std::string type;

public:
    Soup(const std::string& _name, double _price, const std::string& _type) : MenuItem(_name, _price), type(_type) {}

    void printInfo() const override {
        std::cout << "Название: " << name << ", Цена: " << price << ", Тип: " << type << std::endl;
    }

    std::string getInfo() const override {
        return "Название: " + name + ", Цена: " + std::to_string(price) + ", Тип: " + type;
    }
};

// Функция для сортировки блюд по цене
bool sortByPrice(const MenuItem* menuItem1, const MenuItem* menuItem2) {
    return menuItem1->getPrice() < menuItem2->getPrice();
}

int main() {
    std::vector<MenuItem*> menu;
    menu.push_back(new Pizza("Пепперони", 9.99, "Сыр, колбаса, перец"));
    menu.push_back(new Soup("Борщ", 4.99, "Вегетарианский"));

    // Сортировка блюд по цене
    std::sort(menu.begin(), menu.end(), sortByPrice);

    // Вывод информации о блюдах
    for (const auto& item : menu) {
        item->printInfo();
    }

    // Сохранение информации о блюдах в файл "output.txt"
    std::ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (const auto& item : menu) {
            outputFile << item->getInfo() << std::endl;
        }
        outputFile.close();
        std::cout << "Результаты сохранены в файле 'output.txt'" << std::endl;
    } else {
        std::cout << "Ошибка при открытии файла 'output.txt'" << std::endl;
    }

    // Очистка памяти
    for (const auto& item : menu) {
        delete item;
    }
    menu.clear();

    return 0;
}
