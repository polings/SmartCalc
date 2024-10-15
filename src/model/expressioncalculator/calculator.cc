#include "calculator.h"

namespace s21 {
int ExpressionCalculator::Calculate(const std::string& input_expression,
                                    const std::string& arg_x) {
  int error_code = errorcode::kEverythingOk;
  std::deque<Token> infix_expression;
  std::deque<Token> postfix_expression;
  string_parser_.setExpression(input_expression);
  string_parser_.setArgX(arg_x);
  string_parser_.ClearData();
  rpn_converter_.ClearData();
  rpn_calculation_.ClearData();
  error_code = string_parser_.FromStringToInfix();
  if (error_code == errorcode::kEverythingOk) {
    infix_expression = string_parser_.getExpression();
    rpn_converter_.setInfixExpression(infix_expression);
    error_code = rpn_converter_.InfixToPostfix();
  }
  if (error_code == errorcode::kEverythingOk) {
    postfix_expression = rpn_converter_.getPostfixExpression();
    rpn_calculation_.setPostfixExpression(postfix_expression);
    error_code = rpn_calculation_.CalculatePostfixExpression();
  }
  return error_code;
}

double ExpressionCalculator::getResult() {
  return rpn_calculation_.getResult();
}

}  // namespace s21