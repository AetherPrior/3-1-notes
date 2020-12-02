#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> R1(0, 22), R2(0, 22), R3(0, 22);
    for (int i = 0; i < atoi(argv[1]); i++)
    {
        cout << 4 << endl;
        for (int i = 0; i < 4; i++)
        {
            int arr = R1(generator), cpu = R2(generator), priority = R3(generator);
            cout << arr << " " << cpu << " " << priority << endl;
        }
    }
}