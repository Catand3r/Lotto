#include "../src/Lotto.h"
#include <iostream>
#include "gtest/gtest.h"
#include <gmock/gmock.h>

using ::testing::Return;

class MockRandomEngine : public IRandomEngine
{
public:
    MOCK_METHOD(RandomNumbers, GenerateNumbers, (), (override));
};

TEST(LottoTests, ShouldThrowExceptionWhenUserNumberAreNotUniqueAtBegin)
{
    UserNumbers numbers{1, 1, 2, 3, 4, 5};
    IRandomEngine *randomEngine = new RandomEngine();
    EXPECT_ANY_THROW(Lotto(numbers, randomEngine));
    delete randomEngine;
}

TEST(LottoTests, ShouldThrowExceptionWhenUserNumberAreNotUnique)
{
    UserNumbers numbers{1, 6, 2, 4, 4, 5};
    IRandomEngine *randomEngine = new RandomEngine();
    EXPECT_ANY_THROW(Lotto(numbers, randomEngine));
    delete randomEngine;
}

TEST(LottoTests, ShouldThrowExceptionWhenUserNumberAreNotUniqueAtEnd)
{
    UserNumbers numbers{1, 6, 2, 4, 8, 8};
    IRandomEngine *randomEngine = new RandomEngine();
    EXPECT_ANY_THROW(Lotto(numbers, randomEngine));
    delete randomEngine;
}

TEST(LottoTests, ShouldDontThrowExceptionWhenUserNumbersAreUnique)
{
    UserNumbers numbers{1, 6, 2, 4, 8, 9};
    IRandomEngine *randomEngine = new RandomEngine();
    EXPECT_NO_THROW(Lotto(numbers, randomEngine));
    delete randomEngine;
}

TEST(LottoTests, ShouldThrowExceptionWhenRandomNumbersAreNotUnique)
{
    UserNumbers numbers{1, 6, 2, 4, 8, 9};
    RandomNumbers randomNumbers{2, 5, 6, 8, 8, 10};
    MockRandomEngine *randomEngine = new MockRandomEngine();

    EXPECT_CALL(*randomEngine, GenerateNumbers()).WillOnce(Return(randomNumbers));

    Lotto lotto(numbers, randomEngine);
    EXPECT_ANY_THROW(lotto.GenerateRandomNumbers());
    delete randomEngine;
}

TEST(LottoTests, ShouldNotThrowExceptionWhenRandomNumbersAreUnique)
{
    UserNumbers numbers{1, 6, 2, 4, 8, 9};
    RandomNumbers randomNumbers{2, 5, 6, 11, 8, 10};
    MockRandomEngine *randomEngine = new MockRandomEngine();

    EXPECT_CALL(*randomEngine, GenerateNumbers()).WillOnce(Return(randomNumbers));

    Lotto lotto(numbers, randomEngine);
    EXPECT_NO_THROW(lotto.GenerateRandomNumbers());
    delete randomEngine;
}

TEST(LottoTests, GivenUserNumbersAndRandomNumbersWithSameNumbersWhenRunIsCalledReturnNonEmptySameNumbers)
{
    UserNumbers numbers{1, 6, 2, 4, 8, 9};
    RandomNumbers randomNumbers{2, 5, 6, 11, 8, 10};
    MockRandomEngine *randomEngine = new MockRandomEngine();
    EXPECT_CALL(*randomEngine, GenerateNumbers()).WillOnce(Return(randomNumbers));
    Lotto lotto(numbers, randomEngine);
    SameNumbers expectedNumbers = {6, 2, 8};
    lotto.Run();
    EXPECT_EQ(lotto.GetSameNumbers(), expectedNumbers);
    delete randomEngine;
}