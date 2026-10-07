#include <iostream>
#include <string>
using namespace std;

class Order {
public:
    string name;
    int amount, day, month;
};

class Bakery {
public:
    Order* orders;
    int size;

    Bakery() {
        cout << "Enter size: ";
        cin >> size;
        orders = new Order[size];
    }

    void addOrders() {
        for (int i = 0; i < size; i++) {
            cout << "Enter name, amount, day, month for order " << i + 1 << ": ";
            cin >> orders[i].name >> orders[i].amount >> orders[i].day >> orders[i].month;
        }
    }

    bool before(const Order& a, const Order& b) {
        if (a.month != b.month) return a.month < b.month;
        if (a.day != b.day) return a.day < b.day;
        return a.amount > b.amount;
    }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            Order x = orders[i];
            int j = i - 1;
            while (j >= 0 && before(x, orders[j])) {
                orders[j + 1] = orders[j];
                j--;
            }
            orders[j + 1] = x;
        }
    }

    int findToken(int day, int month) {
        int l = 0, h = size - 1, ans = -1;
        while (l <= h) {
            int mid = (l + h) / 2;
            if (orders[mid].day == day && orders[mid].month == month) {
                ans = mid;
                h = mid - 1;
            } else if (month < orders[mid].month ||
                      (month == orders[mid].month && day < orders[mid].day)) {
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans == -1 ? -1 : ans + 1;
    }

    void display() {
        for (int i = 0; i < size; i++)
            cout << orders[i].name << " (token " << i + 1 << ")\n";
    }

    ~Bakery() { delete[] orders; }
};

int main() {
    Bakery b;
    b.addOrders();
    b.insertionSort();
    b.display();

    int d, m;
    cout << "Enter day and month to search: ";
    cin >> d >> m;
    cout << "Token: " << b.findToken(d, m) << endl;
    return 0;
}
