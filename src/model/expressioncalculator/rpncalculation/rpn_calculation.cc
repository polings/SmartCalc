#include "rpn_calculation.h"

namespace s21 {

int Calculation::CalculatePostfixExpression() {
  int error_code = errorcode::kEverythingOk;
  DataDeque result_stack;

  while (!postfix_expression_.empty() &&
         error_code == errorcode::kEverythingOk) {
    Priority p = postfix_expression_.front().getPriority();
    if (p == Priority::kNumber) {
      MoveNumberToken(result_stack);
    } else if (p > Priority::kNumber && p <= Priority::kPower) {
      error_code = HandleOperator(result_stack);
    } else if (p == Priority::kFunction) {
      error_code = HandleFunction(result_stack);
    } else {
      error_code = errorcode::kInvalidExpression;
      break;
    }
  }
  if (error_code == errorcode::kEverythingOk) {
    result_ = result_stack.back().getTokenValue();
  }
  return error_code;
}

void Calculation::MoveNumberToken(DataDeque &destination) {
  if (!postfix_expression_.empty()) {
    Token token = postfix_expression_.front();
    postfix_expression_.pop_front();
    destination.push_back(token);
  }
}

int Calculation::HandleOperator(DataDeque &numbers_deque) {
  int error_code = errorcode::kEverythingOk;
  double result;
  double second_operand = numbers_deque.back().getTokenValue();
  numbers_deque.pop_back();
  double first_operand = numbers_deque.back().getTokenValue();
  numbers_deque.pop_back();
  std::string sign = postfix_expression_.front().getTokenType();
  postfix_expression_.pop_front();

  if (sign == "+") {
    result = first_operand + second_operand;
  } else if (sign == "-") {
    result = first_operand - second_operand;
  } else if (sign == "/") {
    result = first_operand / second_operand;
  } else if (sign == "*") {
    result = first_operand * second_operand;
  } else if (sign == "mod") {
    result = fmod(first_operand, second_operand);
  } else if (sign == "^") {
    result = pow(first_operand, second_operand);
  } else {
    error_code = errorcode::kInvalidExpression;
  }
  if (error_code == errorcode::kEverythingOk) {
    numbers_deque.push_back(Token(result));
  }
  return error_code;
}

int Calculation::HandleFunction(DataDeque &numbers_deque) {
  int error_code = errorcode::kEverythingOk;
  double result;
  double argument = numbers_deque.back().getTokenValue();
  numbers_deque.pop_back();
  std::string function = postfix_expression_.front().getTokenType();
  postfix_expression_.pop_front();

  if (function == "sin") {
    result = sinl(argument);
  } else if (function == "cos") {
    result = cosl(argument);
  } else if (function == "tan") {
    result = tanl(argument);
  } else if (function == "asin") {
    result = asinl(argument);
  } else if (function == "acos") {
    result = acosl(argument);
  } else if (function == "atan") {
    result = atanl(argument);
  } else if (function == "sqrt") {
    result = sqrtl(argument);
  } else if (function == "ln") {
    result = logl(argument);
  } else if (function == "log") {
    result = log10l(argument);
  } else {
    error_code = errorcode::kInvalidExpression;
  }
  if (error_code == errorcode::kEverythingOk) {
    numbers_deque.push_back(Token(result));
  }
  return error_code;
}

void Calculation::setPostfixExpression(const DataDeque &postfix_expression) {
  postfix_expression_ = postfix_expression;
}

double Calculation::getResult() { return result_; }

void Calculation::ClearData() {
  result_ = 0;
  while (!postfix_expression_.empty()) {
    postfix_expression_.pop_back();
  }
}

}  // namespace s21
