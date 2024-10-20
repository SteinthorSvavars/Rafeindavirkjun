/*
Steinþór Emil Svavarsson
Annarpróf 3
Liður 1
*/
#include <iostream>

class Bananaklasi {
private:
    int numer;              //Fjöldi banana í klasanum
    double MedalLengd;      //Meðallengd banana í cm
    int stada;              //Staða klasans (1-10)

public:
    Bananaklasi(int count, double avgLength, int clusterState) {
        numer = count;
        MedalLengd = avgLength;
        stada = clusterState;
    }
    int getNumber() {
        return numer;
    }
    double totalLength() {
        return numer * MedalLengd;
    }
    int takeBanana() {
        if (numer > 0) {
            numer--;
            return 0;   //Skilaðu 0 fyrir árangursríka bananatöku 
        }
        else {
            return -1;  //Skilaðu -1 ef þú reynir að taka banana þegar enginn er eftir
        }
    }
    void displayBananas() {
        std::cout << "Fjöldi banana: " << numer << std::endl;
        std::cout << "Heildarlengd banana: " << totalLength() << " cm" << std::endl;
    }
    void giveBanana() {
        numer++;
    }
};
int main() {
    Bananaklasi cluster(10, 15.0, 5);
    int choice;
    do {
        std::cout << "\nÞú ert kominn inn í bananabúð, hvað vildu gera?";
        std::cout << "\n1: Stela banana";
        std::cout << "\n2: Selja banana";
        std::cout << "\n3. Skoða bananabúð";
        std::cout << "\n4. Hætta";
        std::cout << "\nValið þitt er: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            if (cluster.takeBanana() == 0) {
                std::cout << "\nÞú náðir að stela banananum";
            }
            else {
                std::cout << "\nAllir bananar eru búnir";
            }
            break;
        case 2:
            cluster.giveBanana();
            std::cout << "\nÞú náðir að selja bananann";
            break;
        case 3:
            cluster.displayBananas();
            break;
        case 4:
            std::cout << "\nForrit lokar";
            break;
        default:
            std::cout << "\nVilla veldu aftur";
        }
        std::cout << std::endl;
    } while (choice != 4);
    return 0;
}