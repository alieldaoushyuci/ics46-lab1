// Tests for Introduction Lab (C++) mirroring the provided Java autograder

#include <gtest/gtest.h>

// Access Bag::contents for deterministic setup like the Java tests
#define private public
#include "Bag.hpp"
#undef private
#include "Token.hpp"

#include <string>
#include <vector>

namespace {

// Helper to set up a Bag with deterministic contents and compute expectations
struct BagSetupResult {
    int sum{};
    int num_high{};
    int first_green{-1};
};

BagSetupResult setupBagWithKnownContents(Bag& bag) {
    static const int NUM_TOKENS = 16;
    static const std::vector<std::string> colors = {
        "Red", "Yellow", "Green", "Cyan", "Green",
        "Blue", "Violet", "Green"
    };

    BagSetupResult r;
    // The bag was constructed with NUM_TOKENS size; fill deterministically
    for (int i = 0; i < NUM_TOKENS; ++i) {
        int value = i % Token::MAX_VALUE; // MAX_VALUE is 10
        const std::string& color = colors[static_cast<size_t>(i) % colors.size()];

        bag.contents[static_cast<size_t>(i)].setValue(value);
        bag.contents[static_cast<size_t>(i)].setColor(color);

        r.sum += value;
        if (value > Token::MAX_VALUE / 2)
            r.num_high++;
        if (color == "Green" && r.first_green < 0)
            r.first_green = i;
    }
    return r;
}

} // namespace

// --- Token tests ---

TEST(TokenTests, GetValueReturnsAsConstructed) {
    Token t1{"None", 1};
    Token t10{"None", 10};
    EXPECT_EQ(1, t1.getValue());
    EXPECT_EQ(10, t10.getValue());
}

TEST(TokenTests, SetValueChangesValue) {
    Token t{"None", 1};
    t.setValue(6);
    EXPECT_EQ(6, t.getValue());
}

TEST(TokenTests, GetColorReturnsAsConstructed) {
    Token t{"Red", 5};
    EXPECT_EQ("Red", t.getColor());
}

TEST(TokenTests, SetColorChangesColor) {
    Token t{"Red", 5};
    t.setColor("Blue");
    EXPECT_EQ("Blue", t.getColor());
}

TEST(TokenTests, IsMaxReturnsTrueForMaxValue) {
    Token t{"Red", Token::MAX_VALUE};
    EXPECT_TRUE(t.isMax());
}

TEST(TokenTests, IsMaxReturnsFalseForNonMaxValue) {
    Token t{"Red", Token::MAX_VALUE - 1};
    EXPECT_FALSE(t.isMax());
}

TEST(TokenTests, IsHighValueReturnsTrueWhenValueGreaterThanHalf) {
    Token t{"Red", Token::MAX_VALUE / 2 + 1};
    EXPECT_TRUE(t.isHighValue());
}

TEST(TokenTests, IsHighValueReturnsFalseWhenValueNotGreaterThanHalf) {
    Token t{"Red", Token::MAX_VALUE / 2};
    EXPECT_FALSE(t.isHighValue());
}

// --- Bag tests ---
TEST(BagTests, AddTokensReturnsCorrectSum) {
    Bag bag(16);
    BagSetupResult expected = setupBagWithKnownContents(bag);
    EXPECT_EQ(expected.sum, bag.addTokens());
}

TEST(BagTests, HighValueTokensReturnsCorrectCount) {
    Bag bag(16);
    BagSetupResult expected = setupBagWithKnownContents(bag);
    EXPECT_EQ(expected.num_high, bag.highValueTokens());
}

TEST(BagTests, FirstGreenReturnsCorrectIndex) {
    Bag bag(16);
    BagSetupResult expected = setupBagWithKnownContents(bag);
    EXPECT_EQ(expected.first_green, bag.firstGreen());
}

TEST(BagTests, FirstGreenReturnsNegativeOneWhenNoGreen) {
    Bag bag(5);
    for (size_t i = 0; i < bag.contents.size(); ++i) {
        bag.contents[i].setColor("Red");
        bag.contents[i].setValue(5);
    }
    EXPECT_EQ(-1, bag.firstGreen());
}

