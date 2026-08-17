#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// Maximum number of menu items and customers
const int MAX_ITEMS = 10;
const int MAX_CUSTOMERS = 100;

class MenuItem {
public:
    string name;
    double price;
    MenuItem* next;  // Pointer for linked list

    // Default constructor
    MenuItem() : name(" "), price(0.0), next(nullptr) {}

    // Constructor with arguments
    MenuItem(string Name, double Price) : name(Name), price(Price), next(nullptr) {}
};

class Order {
public:
    MenuItem* items[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount;

    Order() : itemCount(0) {}

    void addItem(MenuItem* item, int quantity) {
        if (itemCount < MAX_ITEMS) {
            items[itemCount] = item;
            quantities[itemCount] = quantity;
            itemCount++;
        } else {
            cout << "Order is full. Cannot add more items.\n";
        }
    }

    void display() const {
        cout << "Order Details:\n";
        cout << setw(19) << left << "Item" << "Quantity" << endl;
        cout << "-------------------------\n";
        for (int i = 0; i < itemCount; i++) {
            cout << setw(15) << left << items[i]->name << quantities[i] << endl;
        }
    }

    double calculateTotal() const {
        double total = 0.0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i]->price * quantities[i];
        }
        return total;
    }
};

class Customer {
private:
    string name;
    string address;
    string phoneNumber;

public:
    void setInfo() {
        cout << "Enter customer name: ";
        getline(cin, name);

        cout << "Enter customer address: ";
        getline(cin, address);

        cout << "Enter customer phone number: ";
        getline(cin, phoneNumber);
    }

    void displayInfo() const {
        cout << "Customer Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phoneNumber << endl;
    }
};

class PizzaShop {
public:
    MenuItem* menuHead;  // Head of linked list for menu
    int menuItemCount;
    Customer customers[MAX_CUSTOMERS];
    int customerCount;

    // Linked list for orders
    struct OrderNode {
        Order order;
        OrderNode* next;
    };
    OrderNode* front;
    OrderNode* rear;

public:
    PizzaShop() : menuHead(nullptr), menuItemCount(0), customerCount(0), front(nullptr), rear(nullptr) {
        // Populate the initial menu with a linked list
        addMenuItem("1.  Fajita", 8.99);
        addMenuItem("2.  Pepperoni", 9.99);
        addMenuItem("3.  Vegetarian", 10.99);
        addMenuItem("4.  Hawaiian", 11.99);
        addMenuItem("5.  BBQ Chicken", 12.99);
        addMenuItem("6.  Meat Lovers", 13.99);
        addMenuItem("7.  Supreme", 14.99);
        addMenuItem("8.  Mushroom", 15.99);
        addMenuItem("9.  Cheese", 16.99);
        addMenuItem("10. Vegan", 17.99);
    }

    void displayMenu() const {
        cout << "Menu:\n";
        cout << setw(19) << left << "Item" << "Price" << endl;
        cout << "-------------------------\n";

        MenuItem* current = menuHead;
        while (current != nullptr) {
            cout << setw(15) << left << current->name << "    " << current->price << " $" << endl;
            current = current->next;
        }
    }

    void takeOrder(Order& order) {
        char choice;
        do {
            int itemNumber;
            int quantity;
            cout << "Enter the item number you want to order: ";
            cin >> itemNumber;
            cout << "Enter the quantity: ";
            cin >> quantity;

            MenuItem* current = menuHead;
            int currentItem = 1;
            while (current != nullptr) {
                if (currentItem == itemNumber) {
                    order.addItem(current, quantity);
                    break;
                }
                current = current->next;
                currentItem++;
            }

            if (current == nullptr) {
                cout << "Invalid item number. Please try again.\n";
                continue;
            }

            cout << "Do you want to add another item to your order? (Y/N): ";
            cin >> choice;
            cin.ignore();
        } while (choice == 'Y' || choice == 'y');
    }

    void takeCustomerInfo(Customer& customer) {
        customer.setInfo();
    }

    void addMenuItem(string name, double price) {
        MenuItem* newItem = new MenuItem(name, price);
        if (menuHead == nullptr) {
            menuHead = newItem;
        } else {
            MenuItem* current = menuHead;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newItem;
        }
        menuItemCount++;
    }

    void editMenuItem() {
        cout << "Enter the index of the item you want to edit: ";
        int index;
        cin >> index;

        MenuItem* current = menuHead;
        int currentItem = 1;
        while (current != nullptr && currentItem < index) {
            current = current->next;
            currentItem++;
        }

        if (current != nullptr) {
            cout << "Enter the new name for the item: ";
            string newName;
            cin >> ws;
            getline(cin, newName);
            current->name = newName;
            cout << "Item updated.\n";
        } else {
            cout << "Invalid index. Please try again.\n";
        }
    }

    void enqueueOrder(const Order& order) {
        OrderNode* newNode = new OrderNode{order, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeueOrder() {
        if (front == nullptr) {
            cout << "No orders to process.\n";
            return;
        }

        OrderNode* temp = front;
        Order order = front->order;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;

        // Process the order
        order.display();
        cout << "Total Cost: $" << order.calculateTotal() << endl;
    }

    void processOrders() {
        while (front != nullptr) {
            dequeueOrder();
        }
    }
};

class PremiumCustomer : public Customer {
private:
    double discountRate;
    int rewardPoints;

public:
    PremiumCustomer() : discountRate(0.0), rewardPoints(0) {}

    void setDiscountRate(double rate) {
        discountRate = rate;
    }

    double getDiscountRate() const {
        return discountRate;
    }

    void earnRewardPoints(int points) {
        rewardPoints += points;
    }

    int getRewardPoints() const {
        return rewardPoints;
    }

    void displayInfo() const {
        Customer::displayInfo();
        cout << "Discount Rate: " << discountRate * 100 << "%" << endl;
        cout << "Reward Points: " << rewardPoints << endl;
    }
};

int main() {
    PizzaShop shop;
    Order order;
    PremiumCustomer premiumCustomer;

    shop.displayMenu();
    shop.takeOrder(order);
    shop.takeCustomerInfo(premiumCustomer);

    premiumCustomer.setDiscountRate(0.1);
    premiumCustomer.earnRewardPoints(50);

    if (order.calculateTotal() > 0) {
        shop.enqueueOrder(order);  // Add order to the queue
        cout << "Order added to the queue.\n";

        ofstream file;
        file.open("order_receipt.txt");
        if (file.is_open()) {
            file << order.calculateTotal() * (1 - premiumCustomer.getDiscountRate()) << endl;
            file << premiumCustomer.getRewardPoints() << endl;
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    } else {
        cout << "No items in the order.\n";
    }

    shop.addMenuItem("New Item", 19.99);
    shop.editMenuItem();
    shop.displayMenu();
    premiumCustomer.displayInfo();

    // Process all orders in FIFO order
    shop.processOrders();

    return 0;
}
