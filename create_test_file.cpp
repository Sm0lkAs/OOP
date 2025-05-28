#include <cstdint>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

struct Hero {
    char name[32];      // Фиксированный размер имени
    uint32_t hp;        // Здоровье
    uint32_t strength;  // Сила
};

int main() {
    Hero test_heroes[] = {{"Arthur", 150, 80},
                          {"Lancelot", 200, 95},
                          {"Merlin", 80, 120},
                          {"Gawain", 180, 115},
                          {"Ghost", 1, 0}};

    ofstream file("input.bin", ios::binary);

    int count = sizeof(test_heroes) / sizeof(Hero);
    file.write(reinterpret_cast<char*>(&count), sizeof(int));

    for (const Hero& h : test_heroes) {
        char padded_name[32] = {};
        strncpy(padded_name, h.name, 31);

        file.write(padded_name, sizeof(padded_name));
        file.write(reinterpret_cast<const char*>(&h.hp), sizeof(h.hp));
        file.write(reinterpret_cast<const char*>(&h.strength), sizeof(h.strength));
    }

    return 0;
}