#include <iostream>
#include <regex>

void main_menu();
int get_user_input();
void select_menu_item(int input);
void print_main_menu();
void go_back_to_main_menu();
bool is_integer(std::string num);
void Spring();
void Pendulum();
void Collision();

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
            Spring();
            break;
        case 2:
            Pendulum();
            break;
        case 3:
            Colision();
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

void Spring() {
    go_back_to_main_menu();
}

void Pendulum() {
    go_back_to_main_menu();
}

void Collision() {
    go_back_to_main_menu();
}
