#include <iostream>
#include <regex>
#include <bitset>
#include <iomanip>

void main_menu();
int get_user_input();
void select_menu_item(int input);
void print_main_menu();
void go_back_to_main_menu();
bool is_integer(std::string num);
void binary_converter();
void hexa_converter();
void truth_table_identifier();

int main() {
    main_menu();
    return 0;
}

void main_menu() {
    print_main_menu();
    int input = get_user_input();
    select_menu_item(input);
}

int get_user_input() {
    int input;
    std::string input_string;
    bool valid_input = false;
    int menu_items = 4;

    do {
        std::cout << "\nSelect item: ";
        std::cin >> input_string;
        valid_input = is_integer(input_string);
        if (valid_input) {
            input = std::stoi(input_string);
            if (input >= 1 && input <= menu_items) {
                valid_input = true;
            } else {
                std::cout << "Invalid menu item!\n";
                valid_input = false;
            }
        } else {
            std::cout << "Enter an integer!\n";
        }
    } while (!valid_input);

    return input;
}

void select_menu_item(int input) {
    switch (input) {
        case 1:
            binary_converter();
            break;
        case 2:
            hexa_converter();
            break;
        case 3:
            truth_table_identifier();
            break;
        case 4:
            exit(0);
            break;
        default:
            std::cout << "Invalid menu item!\n";
            break;
    }
}

void print_main_menu() {
    std::cout << "\n----------- Main menu -----------\n";
    std::cout << "|\t1. Spring\t|\n";
    std::cout << "|\t2. Pendulum\t|\n";
    std::cout << "|\t3. Collision\t|\n";
    std::cout << "|\t4. Exit\t\t\t|\n";
    std::cout << "---------------------------------\n";
}

void go_back_to_main_menu() {
    std::string input;
    do {
        std::cout << "\nEnter 'b' or 'B' to go back to main menu: ";
        std::cin >> input;
    } while (input != "b" && input != "B");
    main_menu();
}

bool is_integer(std::string num) {
    return std::regex_match(num, std::regex("[+-]?[0-9]+"));
}

void binary_converter() {
    int number;
    std::cout << "\nEnter an integer to convert to binary: ";
    std::cin >> number;
    std::cout << "\nBinary representation of " << number << " is " << std::bitset<8>(number) << "\n";
    go_back_to_main_menu();
}

void hexa_converter() {
    int number;
    std::cout << "\nEnter an integer to convert to hexadecimal: ";
    std::cin >> number;
    std::cout << std::hex << "\nHexadecimal representation of " << number << " is " << number << "\n";
    std::cout << std::dec; // Reset to decimal output
    go_back_to_main_menu();
}

void truth_table_identifier() {
    std::cout << "\nTruth Table for AND, OR, and NOT operations:\n";
    std::cout << "A B | A AND B | A OR B | NOT A\n";
    for (int a = 0; a < 2; ++a) {
        for (int b = 0; b < 2; ++b) {
            std::cout << a << " " << b << "   |    " << (a && b) << "    |   " << (a || b) << "   |   " << !a << "\n";
        }
    }
    go_back_to_main_menu();
}
