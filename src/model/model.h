#ifndef CPP3_SMARTCALC_SRC_MODEL_MODEL_H
#define CPP3_SMARTCALC_SRC_MODEL_MODEL_H

#include "creditcalculator/credit_calculator.h"
#include "expressioncalculator/calculator.h"

namespace s21 {
class Model {
 public:
  Model(ExpressionCalculator* c = nullptr, CreditCalculator* credit_c = nullptr)
      : expression_calculator_(c), credit_calculator_(credit_c){};
  ~Model() = default;
  int CalculateExpression(const std::string& input_expression,
                          const std::string& arg_x);
  double getExpressionResult() const;
  int CalculateCredit(InputParametrs parametrs);
  OutputParametrs getCreditResult();

 private:
  ExpressionCalculator* expression_calculator_;
  CreditCalculator* credit_calculator_;
};

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_MODEL_H
