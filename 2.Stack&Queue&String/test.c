#include <iostream>

using namespace std;

int fac(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    return fac(n - 1) + fac(n - 2);
}
int main()
{
    cout << fac(5) << endl;

    return 0;
}