#include "string_parser.h"

namespace s21 {

int StringParser::FromStringToInfix() {
  int error_code = errorcode::kEverythingOk;
  for (auto it = expression_.cbegin(); it != expression_.cend(); ++it) {
    if (IsNumeric(*it)) {
      CheckAndInsertMultiplication();
      insert_multiplication_ = true;
      HandleNumericToken(it, expression_.cend());
    } else if (*it == 'x') {
      CheckAndInsertMultiplication();
      insert_multiplication_ = true;
      HandleXToken(arg_x_);
    } else if (IsOperator(*it)) {
      insert_multiplication_ = false;
      HandleOperatorToken(it);
    } else if (IsFunction(*it)) {
      if (*it == 'm') insert_multiplication_ = false;
      CheckAndInsertMultiplication();
      HandleFunctionToken(it, expression_.cend());
    } else if (*it == '(') {
      CheckAndInsertMultiplication();
      deque_expression_.push_back(Token("(", Priority::kOpenBracket));
      deque_expression_.back().setUnarySign(true);
    } else if (*it == ')') {
      insert_multiplication_ = true;
      deque_expression_.push_back(Token(")", Priority::kCloseBracket));
    } else {
      error_code = errorcode::kInvalidExpression;
      break;
    }
  }
  return error_code;
}

void StringParser::CheckAndInsertMultiplication() {
  if (insert_multiplication_) {
    deque_expression_.push_back(Token("*", Priority::kDivMultMod));
    insert_multiplication_ = false;
  }
};

bool StringParser::IsNumeric(const char ch) {
  return (ch >= '0' && ch <= '9') || ch == '.';
}

bool StringParser::IsOperator(const char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
          ch == '^');  // || ch == '(' || ch == ')'
}

bool StringParser::IsFunction(const char ch) {
  return (ch == 'c' || ch == 's' || ch == 't' || ch == 'a' || ch == 'l' ||
          ch == 'm');
}

void StringParser::HandleNumericToken(std::string::const_iterator& it,
                                      const std::string::const_iterator& end) {
  double number = ExtractNumber(it, end);
  deque_expression_.push_back(Token(number));
  deque_expression_.back().setUnarySign(false);
}

double StringParser::ExtractNumber(std::string::const_iterator& it,
                                   const std::string::const_iterator& end) {
  std::string number_str;
  while (it != end && IsNumeric(*it)) {
    number_str += *it;
    ++it;
  }
  if (it != end && (*it == 'e' || *it == 'E')) {
    number_str += *it;
    ++it;
    if (it != end && (*it == '+' || *it == '-')) {
      number_str += *it;
      ++it;
    }
    while (it != end && std::isdigit(*it)) {
      number_str += *it;
      ++it;
    }
  }
  --it;
  if (*it == '.') {
    number_str += "0";
  }
  return std::stod(number_str);
}

void StringParser::HandleXToken(const std::string& arg_x) {
  deque_expression_.push_back(Token(std::stod(arg_x)));
  deque_expression_.back().setUnarySign(false);
}

void StringParser::HandleOperatorToken(std::string::const_iterator& it) {
  if (*it == '+' || *it == '-') {
    if (deque_expression_.empty() ||
        deque_expression_.back().getUnarySign() == true) {
      deque_expression_.push_back(Token(0));
    }
    deque_expression_.push_back(Token(std::string(1, *it), Priority::kAddSub));
  }
  if (*it == '/' || *it == '*' || *it == '^') {
    deque_expression_.push_back(
        Token(std::string(1, *it),
              *it == '^' ? Priority::kPower : Priority::kDivMultMod));
  }
}

void StringParser::HandleFunctionToken(std::string::const_iterator& it,
                                       const std::string::const_iterator& end) {
  std::string function_str;
  while (it != end && !IsNumeric(*it) && !IsOperator(*it) && *it != ')' &&
         *it != '(') {
    function_str += *it;
    ++it;
  }
  deque_expression_.push_back(Token(function_str, function_str == "mod"
                                                      ? Priority::kDivMultMod
                                                      : Priority::kFunction));

  --it;
}

std::deque<Token> StringParser::getExpression() { return deque_expression_; }

void StringParser::setExpression(std::string expression) {
  expression_ = expression;
}

void StringParser::setArgX(std::string arg_x) { arg_x_ = arg_x; }

void StringParser::ClearData() {
  insert_multiplication_ = false;
  while (!deque_expression_.empty()) {
    deque_expression_.pop_back();
  }
}

}  // namespace s21
