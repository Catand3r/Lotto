#include <iostream>
#include "Lotto.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <exception>

Lotto::Lotto(std::array<int, 6> usernumbers, IRandomEngine *randomEngine) : randomEngine_(randomEngine), userNumbers_(usernumbers)
{
    CheckIfNumbersAreUnique(userNumbers_);
}

void Lotto::Run()
{
    GenerateRandomNumbers();
    for (int i = 0; i < userNumbers_.size(); i++)
    {
        for (int j = 0; j < randomNumbers_.size(); j++)
        {
            if (userNumbers_.at(i) == randomNumbers_.at(j))
            {
                sameNumbers_.push_back(userNumbers_[i]);
            }
        }
    }

    std::cout << "Pokrywa się " << sameNumbers_.size() << " liczb \n";
    std::cout << "Pokrywają się liczby: ";
    for (int i = 0; i < sameNumbers_.size(); i++)
    {
        std::cout << sameNumbers_[i] << ", ";
    }
    std::cout << "\nWylosowano liczby: ";
    for (int i = 0; i < randomNumbers_.size(); i++)
    {
        std::cout << randomNumbers_[i] << ", ";
    }
    std::cout << " a uzytkownik wypisal liczby: ";
    for (int i = 0; i < userNumbers_.size(); i++)
    {
        std::cout << userNumbers_[i] << ", ";
    }
    std::cout << "\n";
}

void Lotto::GenerateRandomNumbers()
{
    randomNumbers_ = randomEngine_->GenerateNumbers();
    CheckIfNumbersAreUnique(randomNumbers_);
}

const UserNumbers &Lotto::GetUserNumbers() const
{
    return userNumbers_;
}

const RandomNumbers &Lotto::GetRandomNumbers() const
{
    return randomNumbers_;
}

const SameNumbers &Lotto::GetSameNumbers() const
{
    return sameNumbers_;
}

RandomNumbers RandomEngine::GenerateNumbers()
{
    std::srand(std::time(nullptr));
    RandomNumbers result;
    for (int i = 0; i < result.size(); i++)
    {
        int randomnumber = std::rand() % 49 + 1;
        result[i] = randomnumber;
    }
    return result;
}
