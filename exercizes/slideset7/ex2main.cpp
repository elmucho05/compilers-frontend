#include <iostream>

extern "C" { double f (double); };

int main() {
   double x;
   std::cout << "Inserisci il valore di x: ";
   std::cin >> x;
   std::cout << "f(x) = " << f(x) << std::endl;
   return 1;
};
