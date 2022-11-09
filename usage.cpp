#include "ezyio.hpp"
using namespace std;
int main()
{
    var v = input<int>("Enter Integer: ");
    print("Binary of",v,"is",int2bin(v));
    print("Hex of",v,"is",int2hex(v));
    return 0;
}