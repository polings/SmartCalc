#ifndef CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_STRINGPARSER_STRING_PARSER_H
#define CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_STRINGPARSER_STRING_PARSER_H

#include <deque>
#include <string>

#include "../common/error_code.h"
#include "../common/token_data.h"

namespace s21 {
class StringParser {
  using DataDeque = std::deque<Token>;

 public:
  StringParser() = default;
  ~StringParser() = default;
  DataDeque getExpression();
  void setExpression(std::string expression);
  void setArgX(std::string arg_x);
  int FromStringToInfix();
  bool IsNumeric(const char ch);
  bool IsOperator(const char ch);
  bool IsFunction(const char ch);
  void HandleNumericToken(std::string::const_iterator& it,
                          const std::string::const_iterator& end);
  double ExtractNumber(std::string::const_iterator& it,
                       const std::string::const_iterator& end);
  void HandleXToken(const std::string& arg_x);
  void HandleOperatorToken(std::string::const_iterator& it);
  void HandleFunctionToken(std::string::const_iterator& it,
                           const std::string::const_iterator& end);
  void CheckAndInsertMultiplication();
  void ClearData();

 private:
  std::string expression_;
  std::string arg_x_;
  DataDeque deque_expression_;
  bool insert_multiplication_;
};

};  // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_STRINGPARSER_STRING_PARSER_H