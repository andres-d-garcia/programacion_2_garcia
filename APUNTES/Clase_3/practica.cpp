#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    string nombre = "Ana virginia";
    string* apellido = new string("García");
    cin >> *apellido; //  
    cout << &nombrePtr << endl; 
    return 0;
}