#include <gtest/gtest.h>

#include "../model/model.h"
#define LIMIT 1e-7

TEST(Model, test_1) {
  long double result = 2 + 3;
  std::string main = "2+3";
  std::string x = "0";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_2) {
  long double result = 2 + 3 - (-231);
  std::string main = "2+3-(-231)";
  std::string x = "0";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_3) {
  long double result = 2 + 3 + (-(-(-(231))));
  std::string main = "2+3+(-(-(-(231))))";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_4) {
  long double result = 2 * 3 + (-231 * 123);
  std::string main = "2*3+(-231*123)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_5) {
  long double result = 1 + (2 * 3 + (-231 * 123)) / 3;
  std::string main = "1+(2*3+(-231*123))/3";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_6) {
  long double result = sin(1) + cos(1);
  std::string main = "sin(1)+cos(1)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_7) {
  long double result = 2 + sin(cos(1) + 2) - 4;
  std::string main = "2+sin(cos(1)+2)-4";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_8) {
  long double result = tan(3);
  std::string main = "tan(3)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_9) {
  long double result = log(3);
  std::string main = "ln(3)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_10) {
  long double result = log10(25);
  std::string main = "log(25)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_11) {
  long double result = sqrt(4124);
  std::string main = "sqrt(4124)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_12) {
  std::string main = "sqrt(-4124)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_TRUE(std::isnan(model.getExpressionResult()));
}

TEST(Model, test_13) {
  long double result = asin(0.5);
  std::string main = "asin(0.5)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_14) {
  long double result = acos(0.5);
  std::string main = "acos(0.5)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_15) {
  long double result = atan(0.5);
  std::string main = "atan(0.5)";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_NEAR(model.getExpressionResult(), result, LIMIT);
}

TEST(Model, test_16) {
  long double result = pow(2, 8);
  std::string main = "2^2^3";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_17) {
  long double x_val = 464;
  long double result = 2 + x_val;
  std::string main = "2+x";
  std::string x = "464";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_18) {
  long double result = 3 % 2;
  std::string main = "3mod2";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_19) {
  std::string main = "3mok2";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  EXPECT_EQ(model.CalculateExpression(main, x),
            s21::errorcode::kInvalidExpression);
}

TEST(Model, test_20) {
  long double result = 3e-11 + 3e-11;
  std::string main = "3e-11+3e-11";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_21) {
  long double result = .0 + .0;
  std::string main = ".+.";
  std::string x = "";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}

TEST(Model, test_22) {
  long double result = 2 * sin(5 * 5) * cos(4 * (1 + 5));
  std::string main = "2sin(5x)cos(4(1+x))";
  std::string x = "5";
  s21::ExpressionCalculator calculator;
  s21::Model model(&calculator);
  model.CalculateExpression(main, x);
  EXPECT_EQ(model.getExpressionResult(), result);
}