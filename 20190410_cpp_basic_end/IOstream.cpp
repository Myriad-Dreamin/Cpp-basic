#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(nullptr));

    int random_price = ((rand() + rand()) % 1000) + 1;
    int input_price = -1;
    while (random_price != input_price) {
        cin >> input_price;
        if (input_price > 1000 || input_price < 0) {
            cout << "the price ranges [1, 1000]" << endl;
            continue;
        }
        else if (input_price > random_price) {
            cout << "too high!" << endl;
        } else if (input_price == random_price) {
            cout << "right!" << endl;
        } else {
            cout << "too low!" << endl;
        }
    }
    return 0;
}
