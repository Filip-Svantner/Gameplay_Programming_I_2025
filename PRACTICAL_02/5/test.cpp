#include <iostream>
using namespace std;

int main() {
int x = 5;
int *px = &x;
cout << "Adress of x: " << px << endl;
cout << "Value of x: " << *px << endl;
}
