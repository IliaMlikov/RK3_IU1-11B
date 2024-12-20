#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int main() {
    string a_bin = "101101";
    string b_bin = "110011";

    int a = stoi(a_bin, nullptr, 2);
    int b = stoi(b_bin, nullptr, 2);

    int and_result = a & b;
    int sum_result = a + b;

    cout << "Результат AND: " << bitset<6>(and_result) << endl;
    cout << "Сумма: " << bitset<6>(sum_result) << endl;

    return 0;
}