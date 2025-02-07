#include "quadratic_solver.hpp"
#include <gtest/gtest.h>
#include <math.h>

using std::isnan;

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}