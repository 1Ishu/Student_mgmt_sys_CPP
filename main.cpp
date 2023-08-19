#include <iostream>
#include <vector>
#include <iomanip>

class MenuItem {
private:
    std::string name;
    double price;

public:
    MenuItem(const std::string& name, double price) : name(name), price(price) {}

    std::string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

class CafeMenu {
private:
    std::vector<MenuItem> menu;

public:
    CafeMenu() {
        menu.push_back(MenuItem("Samosa", 20));
        menu.push_back(MenuItem("Dosa", 30));
        menu.push_back(MenuItem("Tea", 10));
    }

    void displayMenu() const {
        std::cout << "Menu:" << std::endl;
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << " " << menu[i].getName() << " " << menu[i].getPrice() << "/-" << std::endl;
        }
        std::cout << "0 Exit" << std::endl;
    }

    int getMenuSize() const {
        return menu.size();
    }

    MenuItem getMenuItem(int choice) const {
        return menu[choice - 1];
    }
};

class Order {
private:
    MenuItem item;
    int quantity;

public:
    Order(MenuItem item, int quantity) : item(item), quantity(quantity) {}

    double getTotal() const {
        return item.getPrice() * quantity;
    }

    void displayOrder(int srNo) const {
        std::cout << srNo << " | " << item.getName() << " | " << quantity << " | " << item.getPrice() << " | " << getTotal() << "/-" << std::endl;
    }
};

class CafeManager {
private:
    std::vector<Order> orders;
    CafeMenu menu;

public:
    void takeOrder() {
        int choice, quantity;
        do {
            menu.displayMenu();
            std::cout << "Enter your Choice : ";
            std::cin >> choice;
            if (choice == 0) {
                break;
            }

            if (choice < 1 || choice > menu.getMenuSize()) {
                std::cout << "Invalid choice. Please try again." << std::endl;
                continue;
            }

            std::cout << "Enter number of plates : ";
            std::cin >> quantity;

            orders.push_back(Order(menu.getMenuItem(choice), quantity));
        } while (choice != 0);
    }

    double getTotalBill() const {
        double totalBill = 0;
        for (const auto& order : orders) {
            totalBill += order.getTotal();
        }
        return totalBill;
    }

    void displayBill() const {
        std::cout << "::::: Your Bill :::::" << std::endl;
        std::cout << "Sr.No. | Item | Qty | Rate | Sub Total" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        int srNo = 1;
        for (const auto& order : orders) {
            order.displayOrder(srNo);
            srNo++;
        }

        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Grand Total: " << getTotalBill() << "/-" << std::endl;
    }

    void takePayment() {
        double cash;
        do {
            std::cout << "Enter Your Cash: ";
            std::cin >> cash;
            if (cash < getTotalBill()) {
                std::cout << "Please pay " << getTotalBill() - cash << " Rs. more" << std::endl;
            }
        } while (cash < getTotalBill());

        std::cout << "Return Amount: " << cash - getTotalBill() << std::endl;
    }
};

int main() {
    std::cout << "***** Welcome to XYZ Hotel! *****" << std::endl;

    CafeManager manager;
    manager.takeOrder();
    manager.displayBill();
    manager.takePayment();

    std::cout << "----- T H A N K   Y O U ! -------" << std::endl;
    std::cout << "************ VISIT AGAIN ************" << std::endl;

    return 0;
}
