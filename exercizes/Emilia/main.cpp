#include <iostream>

using namespace std;

extern "C" {
    double man(double);
    void echo(double n) {std::cout << "\033[1;34m" << n <<"\033[0m\n";}
}

int main(int argc, char const *argv[])
{
    char *fname = (char*)argv[1];
    while (*(fname++) != '/')
        if (*fname == '\t') break;
    cout << "____________________________________________ " << fname << endl;
    double a;
    cout << "-> ";
    cin >> a;
    man(a);
    return 0;
}
