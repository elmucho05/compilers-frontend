#include <iostream>

extern "C" { double fib (double); };

int main() {
   double x;
   std::cout << "Inserisci il valore di x: ";
   std::cin >> x;
   std::cout << "fib(x) = " << fib(x) << std::endl;
   return 1;
};
