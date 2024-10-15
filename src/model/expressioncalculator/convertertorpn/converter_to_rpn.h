#ifndef CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_CONVERTERTORPN_CONVERTERTORPN_H
#define CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_CONVERTERTORPN_CONVERTERTORPN_H

#include <deque>

#include "../common/error_code.h"
#include "../common/token_data.h"

namespace s21 {
class ConverterToRPN {
  using DataDeque = std::deque<Token>;

 public:
  ConverterToRPN() = default;
  ~ConverterToRPN() = default;
  void setInfixExpression(const DataDeque& deque);
  DataDeque getPostfixExpression();
  int InfixToPostfix();
  void MoveFrontToken(DataDeque& source, DataDeque& destination);
  void MoveBackToken(DataDeque& source, DataDeque& destination);
  void HandleOperator(DataDeque& input, DataDeque& output, DataDeque& support);
  void HandleCloseBracket(DataDeque& input, DataDeque& output,
                          DataDeque& support);
  void ClearData();

 private:
  DataDeque infix_expression_;
  DataDeque postfix_expression_;
};

};  // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_CONVERTERTORPN_CONVERTERTORPN_H