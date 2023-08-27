#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string hex = "1Ah";
    int n;

    n = stoi(hex, nullptr, 16);

    cout << n << endl; // 输出26

    return 0;
}
