#include "quadratic_solver.hpp"
#include "parser.hpp"
#include <gtest/gtest.h>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

/*
    ==== ТЕСТЫ ДЛЯ quadratic_solver.cpp ====
*/

TEST(SampleTests, sample) {
    double x1, x2;
    double const a = 1;
    double const b = -5;
    double const c = 4;
    solveQuadraticEquation(a, b, c, &x1, &x2);
    ASSERT_TRUE(x1 = 4);
    ASSERT_TRUE(x2 = 1);
}

TEST(SampleTest, linearEquation) {
    double x1, x2;
    double const a = 0;
    double const b = -5;
    double const c = 10;
    solveQuadraticEquation(a, b, c, &x1, &x2);
    ASSERT_TRUE(x1 = 2);
    ASSERT_TRUE(x2 = 2);
}

TEST(NoSolutionTest, allZeroes) {
    double x1, x2;
    double const a = 0;
    double const b = 0;
    double const c = 0;
    solveQuadraticEquation(a, b, c, &x1, &x2);
    ASSERT_TRUE(isnan(x1));
    ASSERT_TRUE(isnan(x2));
}

TEST(NoSolutionTest, divisionByZero) {
    double x1, x2;
    double const a = 0;
    double const b = 0;
    double const c = 100;
    solveQuadraticEquation(a, b, c, &x1, &x2);
    ASSERT_TRUE(isnan(x1));
    ASSERT_TRUE(isnan(x2));
}

TEST(NoSolutionTest, negativeDiscriminant) {
    double x1, x2;
    double const a = 10;
    double const b = 0;
    double const c = 100;
    solveQuadraticEquation(a, b, c, &x1, &x2);
    ASSERT_TRUE(isnan(x1));
    ASSERT_TRUE(isnan(x2));
}

/*
    ===== ТЕСТЫ ДЛЯ parser.cpp ====
*/

std::tuple<double, double, double> testParseCoefficients(string& input) {
    istringstream input_stream(input);
    streambuf* orig_cin = std::cin.rdbuf(input_stream.rdbuf());  // Перенаправляем std::cin

    double a, b, c;
    getEquation(&a, &b, &c);

    std::cin.rdbuf(orig_cin);  // Восстанавливаем стандартный ввод
    return {a, b, c};
}

TEST(ParseCoefficientsTest, ValidInput) {
    string input = "2.5 -3.1 4\n";
    auto [a, b, c] = testParseCoefficients(input);
    EXPECT_DOUBLE_EQ(a, 2.5);
    EXPECT_DOUBLE_EQ(b, -3.1);
    EXPECT_DOUBLE_EQ(c, 4.0);
}

TEST(ParseCoefficientsTest, InvalidThenValidInput) {
    string input = "abc\n1.5 2.3 -4.7\n";
    auto [a, b, c] = testParseCoefficients(input);
    EXPECT_DOUBLE_EQ(a, 1.5);
    EXPECT_DOUBLE_EQ(b, 2.3);
    EXPECT_DOUBLE_EQ(c, -4.7);
}

TEST(ParseCoefficientsTest, ExtraCharacters) {
    string input = "2.5 3.1 4 extra\n5.5 6.6 7.7\n";
    auto [a, b, c] = testParseCoefficients(input);
    EXPECT_DOUBLE_EQ(a, 5.5);
    EXPECT_DOUBLE_EQ(b, 6.6);
    EXPECT_DOUBLE_EQ(c, 7.7);
}
TEST(ParseCoefficientsTest, IncompleteInput) {
    string input = "3.2 1.1\n4.4 -5.5 6.6\n";
    auto [a, b, c] = testParseCoefficients(input);
    EXPECT_DOUBLE_EQ(a, 4.4);
    EXPECT_DOUBLE_EQ(b, -5.5);
    EXPECT_DOUBLE_EQ(c, 6.6);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}