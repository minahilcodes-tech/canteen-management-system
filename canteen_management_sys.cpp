/*project by minahil, azka, eman, habiba
----------------------------------
Canteen Managemenat System
__________________________________*/

#include <iostream>
#include <vector>
#include <iomanip>
#include<string>
using namespace std;

// Represents one item in the menu
class MenuItem {
public:
    string name;
    double price;

     MenuItem(string n, double p) {       //constructor
        name = n;
        price = p;
    }
};

// Represents one item in the user's order
class OrderedItem {
public:
    MenuItem item;             //composition
    int quantity;

    OrderedItem(MenuItem i, int q) : item(i), quantity(q) {}
    
};

// Handles user's full order
class Order {
private:
    vector<OrderedItem> orderedItems;     //syntax of vector
    double total;

public:
    Order() {
        total = 0.0;
    }

    void addItem(MenuItem item, int quantity) {
        orderedItems.push_back(OrderedItem(item, quantity));  //push_back fun of vector
        total += item.price * quantity;
    }

    void offerFamilyDeal(char choice) {
        if (choice == 'y' || choice == 'Y') {
            cout << "\n? Family Deal Added: 2 Burgers + 2 Fries + 2 Drinks for Rs. 999\n";
            total += 999;
        }
    }

    void displayBill() {
        cout << "\n========== FINAL BILL ==========\n";
        cout << left << setw(15) << "Item" << setw(10) << "Qty" << setw(10) << "Price" << "Total\n";
        cout << "----------------------------------\n";

        for (const auto& ordered : orderedItems) {
            double itemTotal = ordered.item.price * ordered.quantity;
            cout << left << setw(15) << ordered.item.name
                << setw(10) << ordered.quantity
                << setw(10) << ordered.item.price
                << itemTotal << endl;
        }

        cout << "----------------------------------\n";
        cout << left << setw(35) << "Total Bill:" << total << endl;
        cout << "==================================\n";
        cout << " Thank you "; 
    }
};

// Stores menu items
class Canteen {
private:
    vector<MenuItem> menu;

public:
    Canteen() {
        menu.push_back(MenuItem("Burger", 250));
        menu.push_back(MenuItem("Pizza", 500));
        menu.push_back(MenuItem("Fries", 150));
        menu.push_back(MenuItem("Drink", 100));
        menu.push_back(MenuItem("Sandwich", 200));
    }

    void displayMenu() {
        cout << "\n========= Canteen Menu =========\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". " << left << setw(15) << menu[i].name << "Rs. " << menu[i].price << endl;
        }
        cout << "================================\n";
    }

    MenuItem getItem(int index) {
        if (index >= 1 && index <= menu.size()) {
            return menu[index - 1];
        }
        else {
            return MenuItem("Invalid", 0);
        } 
    }
};

// Main function
int main() {
    Canteen canteen;
    Order order;

    cout << "?? Welcome to the AI Canteen!\n";
    char more;

    do {
        canteen.displayMenu();

        int choice, quantity;
        cout << "\nEnter item number to order: ";
        cin >> choice;
        MenuItem selected = canteen.getItem(choice);

        if (selected.name != "Invalid") {
            cout << "Enter quantity for " << selected.name << ": ";
            cin >> quantity;
            order.addItem(selected, quantity);
            cout << "? " << selected.name << " x" << quantity << " added.\n";
        }
        else {
            cout << "? Invalid choice, try again.\n";
        }

        cout << "Do you want to order more items? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    char dealChoice;
    cout << "\nWould you like to add the Family Deal (Rs. 999)? (y/n): ";
    cin >> dealChoice;
    order.offerFamilyDeal(dealChoice);

    order.displayBill();

    return 0;
}