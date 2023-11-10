#include <iostream>

extern "C" { double h (); };
extern "C" { double g (double, double); };

double g(double x, double y) {
  return 3*x+5*y*y;
}

int main() {
   std::cout << "h() = " << h() << std::endl;
   return 1;
};
