#include "converter_to_rpn.h"

namespace s21 {
int ConverterToRPN::InfixToPostfix() {
  int error_code = errorcode::kEverythingOk;
  DataDeque output_expression;
  DataDeque support_stack;

  while (!infix_expression_.empty()) {
    Priority p = infix_expression_.front().getPriority();
    if (p == Priority::kNumber) {
      MoveFrontToken(infix_expression_, output_expression);
    } else if (p > Priority::kNumber && p <= Priority::kFunction) {
      HandleOperator(infix_expression_, output_expression, support_stack);
    } else if (p == Priority::kOpenBracket) {
      MoveFrontToken(infix_expression_, support_stack);
    } else if (p == Priority::kCloseBracket) {
      HandleCloseBracket(infix_expression_, output_expression, support_stack);
    } else {
      error_code = errorcode::kInvalidExpression;
      break;
    }
  }
  if (error_code == errorcode::kEverythingOk) {
    while (!support_stack.empty()) {
      MoveBackToken(support_stack, output_expression);
    }
    postfix_expression_.swap(output_expression);
  }
  return error_code;
}

void ConverterToRPN::MoveFrontToken(DataDeque& source, DataDeque& destination) {
  if (!source.empty()) {
    Token token = source.front();
    source.pop_front();
    destination.push_back(token);
  }
}

void ConverterToRPN::MoveBackToken(DataDeque& source, DataDeque& destination) {
  if (!source.empty()) {
    Token token = source.back();
    source.pop_back();
    destination.push_back(token);
  }
}

void ConverterToRPN::HandleOperator(DataDeque& input, DataDeque& output,
                                    DataDeque& support) {
  if (!support.empty() && support.back().getTokenType() != "sqrt" &&
      support.back().getTokenType() != "^") {
    while (!support.empty() &&
           support.back().getPriority() >= input.front().getPriority()) {
      MoveBackToken(support, output);
    }
  }
  MoveFrontToken(input, support);
}

void ConverterToRPN::HandleCloseBracket(DataDeque& input, DataDeque& output,
                                        DataDeque& support) {
  while (!support.empty() &&
         support.back().getPriority() != Priority::kOpenBracket) {
    MoveBackToken(support, output);
  }
  input.pop_front();
  support.pop_back();
  if (!support.empty() && support.back().getPriority() == Priority::kFunction) {
    MoveBackToken(support, output);
  }
}

void ConverterToRPN::setInfixExpression(const DataDeque& deque) {
  infix_expression_ = deque;
}

ConverterToRPN::DataDeque ConverterToRPN::getPostfixExpression() {
  return postfix_expression_;
}

void ConverterToRPN::ClearData() {
  while (!infix_expression_.empty()) {
    infix_expression_.pop_back();
  }
  while (!postfix_expression_.empty()) {
    postfix_expression_.pop_back();
  }
}

}  // namespace s21
