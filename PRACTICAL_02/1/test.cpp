# include <stdio.h>
# include <iostream>

int main () 
{

int a = 10;
int *p = &a;

std::cout << "Value of a: " << a << "\n";
std::cout << "Address of a: " << &a << "\n";
std::cout << "Pointer p points to: " << p << "\n";
std::cout << "Value of p: " << *p << "\n";

}

