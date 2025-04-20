#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

// Enum для типа склада
enum class WarehouseType {
    CENTER,
    WEST,
    EAST
};

// Класс Product
class Product {
private: 
    string barcode; // штрих-код
    string description; // описание
    float price; // стоимость
    int quantity; // количество
    float transportLongitude; // позиционная долгота посадки
    float transportLatitude; // позиционная широта посадки

public:
    // Конструкторы
    Product() : barcode(""), description(""), price(0.0), quantity(0), transportLongitude(0.0), transportLatitude(0.0) {}

    Product(string desc, float p, int q, float tLong, float tLat)
        : description(desc), price(p), quantity(q), transportLongitude(tLong), transportLatitude(tLat) {
        generateBarcode();
    }

    // Конструктор копирования
    Product(const Product& other) {
        barcode = other.barcode;
        description = other.description;
        price = other.price;
        quantity = other.quantity;
        transportLongitude = other.transportLongitude;
        transportLatitude = other.transportLatitude;
    }

    // Генерация штрих-кода
    void generateBarcode() {
        barcode = "460"; 

        int part = (rand() % 9 + 1) * 1000;
        barcode += to_string(part);

        for (int i = 0; i < 6; ++i) {
            barcode += to_string(rand() % 10);
        }
    }

    // Setters
    void setBarcode(string bc)
    {
        barcode = bc; 
    }
    void setDescription(string desc)
    {
        description = desc; 
    }
    void setPrice(float p)
    {
        price = p; 
    }
    void setQuantity(int q)
    { 
        quantity = q; 
    }
    void setTransportLong(float tLong)
    {
        transportLongitude = tLong;
    }
    void setTransportLat(float tLat) 
    {
        transportLatitude = tLat;
    }

    // Getters
    string getBarcode() const 
    {
        return barcode; 
    }
    string getDescription() const 
    {
        return description; 
    }
    float getPrice() const 
    {
        return price; 
    }
    int getQuantity() const 
    {
        return quantity; 
    }
    float getTransportLong() const
    {
        return transportLongitude;
    }
    float getTransportLat() const
    {
        return transportLatitude;
    }

    // Печать информации о продукте
    void print() const {
        cout << "Штрих-код: " << barcode << endl;
        cout << "Описание: " << description << endl;
        cout << "Цена: " << fixed << setprecision(2) << price << " руб." << endl;
        cout << "Количество: " << quantity << endl;
        cout << "Позиция транспортировки: (" << transportLongitude << ", " << transportLatitude << ")" << endl;
    }
};

// Класс Warehouse
class Warehouse {
private:
    string id; // идентификатор
    WarehouseType type; // тип
    float longitude; // долгота
    float latitude; // широта
    int maxCapacity; // максимальная вместимость
    int totalStock; // общий запас
    vector<Product> products; // список продуктов
    static int warehouseCounter; 

public:
    // Конструкторы
    Warehouse() : id(""), type(WarehouseType::CENTER), longitude(0.0), latitude(0.0), maxCapacity(0), totalStock(0) {}

    Warehouse(WarehouseType t, float lon, float lat, int maxCap)
        : type(t), longitude(lon), latitude(lat), maxCapacity(maxCap), totalStock(0) {
        generateId();
    }

    // Конструктор копирования
    Warehouse(const Warehouse& other) {
        id = other.id;
        type = other.type;
        longitude = other.longitude;
        latitude = other.latitude;
        maxCapacity = other.maxCapacity;
        totalStock = other.totalStock;
        products = other.products;
    }

    // Деструктор
    ~Warehouse() {
        products.clear();
    }

    // Генерация ID склада
    void generateId() {
        int code = 100 + warehouseCounter++;
        id = "W" + to_string(code);
    }

    // Добавление продукта
    bool addProduct(const Product& product) {
        if (totalStock + product.getQuantity() <= maxCapacity) {
            products.push_back(product);
            totalStock += product.getQuantity();
            return true;
        }
        return false;
    }

    // Удаление продукта по штрих-коду
    bool removeProduct(string barcode) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getBarcode() == barcode) {
                totalStock -= it->getQuantity();
                products.erase(it);
                return true;
            }
        }
        return false;
    }

    // Поиск продукта по описанию
    vector<Product> findProduct(string desc) const {
        vector<Product> result;
        for (const auto& product : products) {
            if (product.getDescription().find(desc) != string::npos) {
                result.push_back(product);
            }
        }
        return result;
    }

    // Вычисление расстояния Манхэттена
    float calculateDistance(float productLong, float productLat) const {
        return abs(latitude - productLat) + abs(longitude - productLong);
    }

    // Обновление общего запаса
    void updateStock(int delta) {
        totalStock += delta;
    }

    // Печать информации о складе
    void print() const {
        cout << "ID склада: " << id << endl;
        cout << "Тип: ";
        switch (type) {
        case WarehouseType::CENTER:
            cout << "центр";
            break;
        case WarehouseType::WEST:
            cout << "запад";
            break;
        case WarehouseType::EAST:
            cout << "восток";
            break;
        }
        cout << endl;
        cout << "Координаты: (" << longitude << ", " << latitude << ")" << endl;
        cout << "Макс. вместимость: " << maxCapacity << endl;
        cout << "Текущий запас: " << totalStock << endl;
        cout << "Количество продуктов: " << products.size() << endl;
    }

    // Список продуктов
    void listProducts() const {
        if (products.empty()) {
            cout << "Склад пуст." << endl;
            return;
        }
        for (const auto& product : products) {
            product.print();
            cout << "-------------------" << endl;
        }
    }

    // Getters
    string getId() const 
    {
        return id; 
    }
    WarehouseType getType() const 
    {
        return type; 
    }
    pair<float, float> getCoordinates() const 
    {
        return { longitude, latitude }; 
    }
    int getMaxCapacity() const 
    {
        return maxCapacity; 
    }
    int getTotalStock() const 
    {
        return totalStock; 
    }
    vector<Product> getProducts() const 
    {
        return products; 
    }
};

int Warehouse::warehouseCounter = 0;

// Функция для создания продукта
Product createProduct() {
    string desc;
    float price;
    int quantity;
    float tLong, tLat;

    cout << "Введите описание продукта (до 50 символов): ";
    cin.ignore();
    getline(cin, desc);
    if (desc.length() > 50) desc = desc.substr(0, 50);

    cout << "Введите цену продукта: ";
    cin >> price;

    cout << "Введите количество: ";
    cin >> quantity;

    cout << "Введите долготу транспортировки (19-169): ";
    cin >> tLong;
    tLong = max(19.0f, min(169.0f, tLong));

    cout << "Введите широту транспортировки (41-82): ";
    cin >> tLat;
    tLat = max(41.0f, min(82.0f, tLat));

    return Product(desc, price, quantity, tLong, tLat);
}

// Главное меню
void menu() {
    vector<Warehouse> warehouses = {
        Warehouse(WarehouseType::CENTER, 55.75, 37.62, 1000),  
        Warehouse(WarehouseType::WEST, 59.94, 30.31, 800),     
        Warehouse(WarehouseType::EAST, 56.83, 60.60, 1200)      
    };

    while (true) {
        cout << "\n=== Меню управления складами ===" << endl;
        cout << "1. Добавить продукт на склад" << endl;
        cout << "2. Просмотреть продукты на складе" << endl;
        cout << "3. Поиск продукта по описанию" << endl;
        cout << "4. Удалить продукт" << endl;
        cout << "5. Информация о складах" << endl;
        cout << "0. Выход" << endl;
        cout << endl << "Выберите действие: ";

        int choice;
        cin >> choice;

        cout << endl;

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            Product p = createProduct();

            float tLong = p.getTransportLong();
            float tLat = p.getTransportLat();

            // Находим склад с минимальным расстоянием
            int bestWarehouse = 0;
            float minDist = warehouses[0].calculateDistance(tLong, tLat);

            for (int i = 1; i < warehouses.size(); ++i) {
                float dist = warehouses[i].calculateDistance(tLong, tLat);
                if (dist < minDist) {
                    minDist = dist;
                    bestWarehouse = i;
                }
            }

            if (warehouses[bestWarehouse].addProduct(p)) {
                cout << "Продукт добавлен на склад " << warehouses[bestWarehouse].getId() << endl;
            }
            else {
                cout << "Склад переполнен!" << endl;
            }
            break;
        }
        case 2: {
            cout << "Выберите склад (1-Центр, 2-Запад, 3-Восток): ";
            int wh;
            cin >> wh;
            if (wh >= 1 && wh <= 3) {
                warehouses[wh - 1].listProducts();
            }
            else {
                cout << "Неверный выбор!" << endl;
            }
            break;
        }
        case 3: {
            string desc;
            cout << "Введите часть описания для поиска: ";
            cin.ignore();
            getline(cin, desc);

            for (int i = 0; i < warehouses.size(); ++i) {
                vector<Product> found = warehouses[i].findProduct(desc);
                if (!found.empty()) {
                    cout << "\nНайдено на складе " << warehouses[i].getId() << ":" << endl;
                    for (const auto& p : found) {
                        p.print();
                        cout << "-------------------" << endl;
                    }
                }
            }
            break;
        }
        case 4: {
            cout << "Выберите склад (1-Центр, 2-Запад, 3-Восток): ";
            int wh;
            cin >> wh;
            if (wh < 1 || wh > 3) {
                cout << "Неверный выбор!" << endl;
                break;
            }

            string barcode;
            cout << "Введите штрих-код продукта для удаления: ";
            cin >> barcode;

            if (warehouses[wh - 1].removeProduct(barcode)) {
                cout << "Продукт удален." << endl;
            }
            else {
                cout << "Продукт не найден!" << endl;
            }
            break;
        }
        case 5: {
            for (const auto& wh : warehouses) {
                wh.print();
                cout << "===================" << endl;
            }
            break;
        }
        default:
            cout << "Неверный выбор!" << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0)); // Инициализация генератора случайных чисел
    menu();
    return 0;
}
