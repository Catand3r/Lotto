#pragma once
#include <iostream>
#include <array>
#include <vector>

using UserNumbers = std::array<int, 6>;
using RandomNumbers = std::array<int, 6>;
using SameNumbers = std::vector<int>;

class IRandomEngine
{
public:
    virtual ~IRandomEngine() = default;

    virtual RandomNumbers GenerateNumbers() = 0;
};

class RandomEngine : public IRandomEngine
{
public:
    ~RandomEngine() override = default;
    RandomNumbers GenerateNumbers() override;
};

class Lotto
{
public:
    Lotto(std::array<int, 6>, IRandomEngine *randomEngine);
    void Run();
    void GenerateRandomNumbers();
    void CompareNumbers();
    const UserNumbers &GetUserNumbers() const;
    const RandomNumbers &GetRandomNumbers() const;
    const SameNumbers &GetSameNumbers() const;

private:
    IRandomEngine *randomEngine_;

    template <typename T>
    void CheckIfNumbersAreUnique(const T &numbers)
    {
        for (int i = 0; i < numbers.size(); i++)
        {
            for (int j = i; j < numbers.size() - 1; j++)
            {
                if (numbers.at(i) == numbers.at(j + 1))
                {
                    throw std::invalid_argument("Same numbers");
                }
            }
        }
    }
    UserNumbers userNumbers_;
    RandomNumbers randomNumbers_;
    SameNumbers sameNumbers_;
};