#include <iostream>
#include <array>
#include "Lotto.h"

int main()
{
    std::array<int, 6> usernumbers;
    for (int i = 0; i < usernumbers.size(); i++)
    {
        std::cout << "Podaj liczbę: ";
        int number;
        std::cin >> number;
        usernumbers[i] = number;
    }
    IRandomEngine *randomEngine = new RandomEngine();
    Lotto lotto(usernumbers, randomEngine);
    lotto.Run();
    delete randomEngine;
}