#include <iostream>
#include <complex>
#include <vector>

#include "clooptools.h"

using namespace std;

int main() 
{
    ltini();
    cout << B0(1000., 50., 80.) << endl;
    ltexi();
};