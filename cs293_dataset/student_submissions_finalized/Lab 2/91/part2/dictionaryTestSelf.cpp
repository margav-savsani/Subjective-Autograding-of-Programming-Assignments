#include "dictionary.tpp.hpp"
#include <string>

int main(int argc, char* argv[])
{
    Dictionary<float> d(5);
    while (true) {
        std::cout << ">> ";
        std::string op;
        char key[100];
        bool success;
        std::cin >> op;
        if (op == "INS") {
            float f;
            std::cin >> key >> f;
            try {
                if (!d.put(key, f)) {
                    std::cout << "Could not insert, dictionary full\n";
                }
                else {
                    std::cout << "Insertion successful\n";
                }
            }
            catch (int _) {
                std::cout << "Key too large\n";
            }
        }
        else if (op == "FIND") {
            std::cin >> key;
            try {
                float* f_ptr = d.get(key);
                if (f_ptr == nullptr) {
                    std::cout << "Key not found\n";
                }
                else {
                    std::cout << "Value for " << key << ": " << *f_ptr << '\n';
                }
            }
            catch (int _) {
                std::cout << "Key too large\n";
            }
        }
        else if (op == "DEL") {
            std::cin >> key;
            try {
                if (!d.remove(key)) {
                    std::cout << "Key not found\n";
                }
                else {
                    std::cout << key << " removed\n";
                }
            }
            catch (int _) {
                std::cout << "Key too large\n";
            }
        }
        else if (op == "QUIT") {
            break;
        }
        else {
            continue;
        }
    }
}
