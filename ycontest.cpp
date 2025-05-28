#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Hero {
    char name[32];
    uint32_t hp;
    uint32_t strength;
};

int main() {
    ifstream file(("input.bin"), ios::binary);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    uint32_t max_strength = 0;
    string max_name;

    for (int i = 0; i < count; i++) {
        Hero hero;
        file.read(hero.name, sizeof(hero.name));
        file.read(reinterpret_cast<char*>(&hero.hp), sizeof(hero.hp));
        file.read(reinterpret_cast<char*>(&hero.strength), sizeof(hero.strength));

        string name(hero.name, strnlen(hero.name, sizeof(hero.name)));

        if (hero.strength > max_strength) {
            max_strength = hero.strength;
            max_name = name;
        }
    }

    cout << max_name << endl;
    file.close();

    cin.ignore();
    cin.get();
    return 0;
}
