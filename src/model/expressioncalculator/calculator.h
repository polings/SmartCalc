#ifndef CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_CALCULATOR_H
#define CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_CALCULATOR_H

#include "convertertorpn/converter_to_rpn.h"
#include "rpncalculation/rpn_calculation.h"
#include "stringparser/string_parser.h"

namespace s21 {
class ExpressionCalculator {
 public:
  ExpressionCalculator() = default;
  ~ExpressionCalculator() = default;
  int Calculate(const std::string& input_expression, const std::string& arg_x);
  double getResult();

 private:
  StringParser string_parser_{};
  ConverterToRPN rpn_converter_{};
  Calculation rpn_calculation_{};
};

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_CALCULATOR_H