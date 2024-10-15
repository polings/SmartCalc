#ifndef CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_RPNCALCULATION_RPN_CALCULATION_H
#define CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_RPNCALCULATION_RPN_CALCULATION_H

#include <cmath>
#include <deque>
#include <string>

#include "../common/error_code.h"
#include "../common/token_data.h"

namespace s21 {
class Calculation {
  using DataDeque = std::deque<Token>;

 public:
  Calculation() = default;
  ~Calculation() = default;
  void setPostfixExpression(const DataDeque& postfix_expression);
  double getResult();
  int CalculatePostfixExpression();
  void MoveNumberToken(DataDeque& destination);
  int HandleOperator(DataDeque& result);
  int HandleFunction(DataDeque& result);
  void ClearData();

 private:
  double result_;
  DataDeque postfix_expression_;
};

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_RPNCALCULATION_RPN_CALCULATION_H