/*
Stein��r Emil Svavarsson
Annarpr�f 3
Li�ur 1
*/
#include <iostream>

class Bananaklasi {
private:
    int numer;              //Fj�ldi banana � klasanum
    double MedalLengd;      //Me�allengd banana � cm
    int stada;              //Sta�a klasans (1-10)

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
            return 0;   //Skila�u 0 fyrir �rangursr�ka bananat�ku 
        }
        else {
            return -1;  //Skila�u -1 ef �� reynir a� taka banana �egar enginn er eftir
        }
    }
    void displayBananas() {
        std::cout << "Fj�ldi banana: " << numer << std::endl;
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
        std::cout << "\n�� ert kominn inn � bananab��, hva� vildu gera?";
        std::cout << "\n1: Stela banana";
        std::cout << "\n2: Selja banana";
        std::cout << "\n3. Sko�a bananab��";
        std::cout << "\n4. H�tta";
        std::cout << "\nVali� �itt er: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            if (cluster.takeBanana() == 0) {
                std::cout << "\n�� n��ir a� stela banananum";
            }
            else {
                std::cout << "\nAllir bananar eru b�nir";
            }
            break;
        case 2:
            cluster.giveBanana();
            std::cout << "\n�� n��ir a� selja bananann";
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