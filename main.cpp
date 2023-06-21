// #include "JDM/JDM.hpp"
// #include "HeaderFiles/Template.hpp"

// using Game = Template;
// class GameWindow : public JDM::Window, public Game {
// private:
// public:
//     GameWindow() : JDM::Window(
//         Game::WindowTitle,
//         {JDM_UNDEFINED_POS, JDM_UNDEFINED_POS, Game::WIDTH, Game::HEIGHT},
//         Game::backGround
//     ) { JDM::SETTER::JDMSetFPS(120); }

// private:
//     const void initAllObjects() { Game::initAllObjects(); }
//     const void update() { Game::update(); }
// };
// int main(int argc, char** argv) {
//     std::make_shared<GameWindow>()->run();
//     return 0;
// }

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <algorithm>
#include <tuple>
#include <windows.h>

using namespace std;

class Store {

public:
    std::string nameOfCustomer;
    std::string ID = "";
    double discount = 10;

    std::vector<std::tuple<std::string, int, float>> allCustomerOrder = {};
    std::vector<std::pair<std::string, float>> allItems = {
        std::make_pair("TESING THE FRAEEk", 50.f),
        std::make_pair("Burger 2", 75.f),
        std::make_pair("Burger 3", 100.f),
        std::make_pair("Burger 4", 150.f)
    };

public:

    Store() {
        this->loginScreen();
    }

private:
    void drawLine() {
        for (int i = 0; i < 99; i++)
            std::cout << '-';
        std::cout << std::endl;
    }
    void drawLogo() {
        this->drawLine();
        int length = (float)16/2;
        std::cout
            << std::setfill(' ')
            << std::setw(50+length-2)
            << "Lagalag Burger Hub"
            << '\n';
        this->drawLine();
    }
    void loginScreen() {
        std::system("cls");
        this->drawLogo();
        std::cout << " -> Name: ";
        std::cin >> this->nameOfCustomer;
        std::cout << " -> ID (PWD / Senior / None): ";
        std::cin >> this->ID;

        this->lowerString(this->ID);

        this->drawLine();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        this->displayShop();
    }

    const void displayShop() {
        std::system("cls");
        this->drawLogo();
        std::cout
            << std::right << std::setw(100/4-4) << "PRODUCT" 
            << std::right << std::setw(100/2+3) << "PRICE" << std::endl;
        this->drawLine();
        for (int i = 0; i < this->allItems.size(); i++) {
            std::cout
                << ' ' << i+1 << "  " << std::setfill('0')
                << std::right << std::setw(24) << std::setfill(' ') <<  this->allItems[i].first
                << std::left << std::setw(10) << std::setfill(' ') << " : "
                << std::setfill(' ') << std::left << std::setw(50/2 + 5) << " -> "
                << std::left << std::setw(' ') << std::fixed << std::setprecision(2)
                << std::left << this->allItems[i].second << std::right << "\n\n";
        }
        this->drawLine();
        this->ManageInput();
    }
    const void ManageInput() {
        std::string station;
        std::string order;
        int quantity = 1;

        std::cout << " > INPUT (" << this->nameOfCustomer << "): ";
        std::cin >> station;
        this->lowerString(station);

        if (station.compare("manage") == 0) {
            this->manageUser();
            return;
        }
        else if (station.compare("add") == 0) {
            std::cin >> order >> quantity;
            this->lowerString(order);

            bool found = false;
            int index = 1;
            for (auto merch : this->allItems) {

                std::string copy = merch.first;
                this->lowerString(copy);

                if (std::stoi(order) == index || merch.first.compare(copy) == 0) {
                    found = true;
                    bool found2 = false;
                    for (auto &merch2 : this->allCustomerOrder) {
                        if (std::get<0>(merch2).compare(merch.first) == 0) {
                            found2 = true;
                            std::get<1>(merch2) += quantity;
                            std::cout << "  -> Product Added.\n\n";
                        }
                    }
                    if (!found2) {
                        this->allCustomerOrder.push_back({merch.first, quantity, merch.second});
                        std::cout << "  -> New Product Added!\n\n";
                    }
                    break;
                }
                index++;
            }
            if (!found) std::cout << "  -> Product not found!\n\n";
        }
        else if (station.compare("remove") == 0) {
            std::cin >> order >> quantity;
            this->lowerString(order);

            bool found = false;
            int index = 1;
            for (auto merch : this->allItems) {
                std::string copy = merch.first;

                if (std::stoi(order) == index || merch.first.compare(copy) == 0) {
                    found = true;
                    bool found2 = false;
                    for (auto &merch2 : this->allCustomerOrder) {
                        if (std::get<0>(merch2).compare(merch.first) == 0) {
                            found2 = true;
                            if (std::get<1>(merch2) - quantity <= 0) {
                                allCustomerOrder.erase(
                                    std::remove(allCustomerOrder.begin(),
                                    allCustomerOrder.end(), merch2),
                                    allCustomerOrder.end());

                                std::cout << "  -> Product Deleted in your List!\n\n";
                            } else {
                                std::cout << "  -> Number of Product Decrease.\n\n";
                                std::get<1>(merch2) -= quantity;
                            }
                        }
                    }
                    if (!found2) std::cout << "  -> This Product does not exist on your List!\n\n";
                    break;
                }
                index++;
            }
            if (!found) std::cout << "  -> Product not found!\n\n";
        }
        else if (station.compare("submit") == 0) {
            if (this->allCustomerOrder.size() > 0) {
                this->checkAllOrder();
                return;
            } else {
                std::cout << "  -> You have no order.\n\n";
            }
        }
        else if (station.compare("clear") == 0 || station.compare("cls") == 0) {
            this->clearCin();
            this->displayShop();
            return;
        }
        this->clearCin();
        this->ManageInput();
    }

    const void checkAllOrder() {
        std::system("cls");
        this->drawLogo();
        std::cout << " > Name: " << this->nameOfCustomer << '\n';
        this->drawLine();

        double total = 0;
        for (auto merch : this->allCustomerOrder)
        {
            std::cout << std::setw(3) << std::setfill(' ')
                      << "-> " << std::get<1>(merch) << ' ' << std::get<0>(merch) << " -> " << std::get<2>(merch) * std::get<1>(merch) << '\n';
            total += std::get<2>(merch) * std::get<1>(merch);
        }
        std::cout << "\n > Total: " << total << '\n';
        if (this->ID.compare("pwd") == 0 || this->ID.compare("senior") == 0)
        {
            std::cout << " > But with discount of " << this->discount << "% , the new total: " << total - (total * (this->discount/100)) << '\n';
        }
        this->drawLine();
        if (!(this->ID.compare("pwd") == 0 || this->ID.compare("senior") == 0))
        {
            this->generateAndDecreaseNumber();
            this->drawLine();
        }

        std::cout
            << " > You successfully ordered the items. Thank you for your service!\n"
            << " > Current Budget: Infinite" << '\n';
        this->allCustomerOrder.clear();

        this->standByShop();
    }

    const void manageUser() {
        std::system("cls");
        this->drawLine();
        std::cout << " > Name: " << this->nameOfCustomer << '\n';
        this->drawLine();

        if (this->allCustomerOrder.size() <= 0) {
            std::cout << " -> You have no order...\n";
        } else {
            double total = 0;
            for (auto merch : this->allCustomerOrder) {
                std::cout << std::setw(3) << std::setfill(' ')
                      << "-> " << std::get<1>(merch) << ' ' << std::get<0>(merch) << " -> " << std::get<2>(merch) * std::get<1>(merch) << '\n';
                total += std::get<2>(merch) * std::get<1>(merch);
            }
            this->drawLine();
            std::cout << "\n > Total: " << total << '\n';
            if (this->ID.compare("pwd") == 0 || this->ID.compare("senior") == 0) {
                std::cout << " > But with discount of " << this->discount << "% , the new total: " << total - (total * (this->discount/100))  << '\n';
            }
        }
        this->standByShop();
    }

    const void standByShop() {
        this->drawLine();
        std::cout << std::setfill(' ') << " > Press Enter key to continue... ";
        this->clearCin();
        std::cin.get();
        this->displayShop();
    }

    const void clearCin() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    const void lowerString(std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char character)
            { return std::tolower(character); });
    }

    const void generateAndDecreaseNumber() {
        srand(static_cast<unsigned int>(time(nullptr)));
        int number = rand() % 8 + 3;

        std::cout << "Waiting for order..." << std::endl;
        std::cout << "Order in progress... Number in queue: " << number << std::endl;

        while (number > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            number--;
            std::cout << "Order in progress... Number in queue: " << number << std::endl;
        }

        std::cout << "Order ready!" << std::endl;
    }
};

void title(HANDLE h){
	int i;
	SetConsoleTextAttribute(h,14);
	cout<<"\n\n\n\n";
	cout<<"\t\t    ****    *    *   ****    **     ***   **** \n";
 	cout<<"\t\t   /**    *   /*   /**  /**    *  /*    *   /*       /**    ** \n";
 	cout<<"\t\t   /*********  /**   /**  /********  /**   *  /*****   /******** \n";
 	SetConsoleTextAttribute(h,12);
 	cout<<"\t\t   /**     *  /*   /**  /**  /**   /**    *   /*       /**  /**  \n";
 	cout<<"\t\t   /*********  //******   /**  //**  //******    /*******  /**  //** \n";
 	cout<<"\t\t   /////////    //////    //    //    //////     ///////   //    //\n\n\n";
 
	SetConsoleTextAttribute(h,14);
	cout<<"\t\t          ------------       \n";
	cout<<"\t\t        /%%%%%%%%%%%%%%\\      \n";
	cout<<"\t\t       /%%%%%%%%%%%%%%%%\\     ";
	SetConsoleTextAttribute(h,14);
	cout<<"*    *   *    *   ********\n";
	SetConsoleTextAttribute(h,12);
	cout<<"\t\t       \\wwwwwwwwwwwwwwww/    ";
	SetConsoleTextAttribute(h,14);
	cout<<"/**   /**  /**   /**  /**    **          \n";
	SetConsoleTextAttribute(h,10);
	cout<<"\t\t        <%%%%%%%%%%%%%%>     ";
	SetConsoleTextAttribute(h, 14);
	cout<<"/********  /**   /**  /*********      \n";
	SetConsoleTextAttribute(h,4);
	cout<<"\t\t        (%%%%%%%%%%%%%%)     ";
	SetConsoleTextAttribute(h,12);
	cout<<"/**   /**  /**   /**  /**     **          \n";
	SetConsoleTextAttribute(h,14);
	cout<<"\t\t       /%%%%%%%%%%%%%%%%\\    ";
	SetConsoleTextAttribute(h, 12);
	cout<<"/**   /**  //******   /*********    \n";
	SetConsoleTextAttribute(h, 14);
	cout<<"\t\t       \\%%%%%%%%%%%%%%%%/    ";
	SetConsoleTextAttribute(h, 12);
	cout<<"//    //    //////    /////////  \n";
	SetConsoleTextAttribute(h, 14);
	cout<<"\t\t        \\%%%%%% %%%%%%%%/        \n";
	cout<<"\t\t          ------------         \n\n";
	cout<<"\t\t\t\t      ";
}

void clear(){
	cin.clear();
	cin.ignore(100,'\n');
}
void cls(){
	system("cls");
}			

int main() {
    cls();
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    title(h);
	for(int a=1;a<8;a++)
	{
		Sleep(300);
		SetConsoleTextAttribute(h, 10);
		cout << "...";
	}
	Sleep(2000);
	cls();
    SetConsoleTextAttribute(h, 15);
    Store store = Store();
}