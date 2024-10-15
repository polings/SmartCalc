#include "model.h"

namespace s21 {
int Model::CalculateExpression(const std::string& input_expression,
                               const std::string& arg_x) {
  int error_code = errorcode::kEverythingOk;
  error_code = expression_calculator_->Calculate(input_expression, arg_x);
  return error_code;
}

double Model::getExpressionResult() const {
  return expression_calculator_->getResult();
}

int Model::CalculateCredit(InputParametrs parametrs) {
  int error_code = errorcode::kEverythingOk;
  credit_calculator_->setInputParametrs(parametrs);
  error_code = credit_calculator_->CalculateCredit();
  return error_code;
}

OutputParametrs Model::getCreditResult() {
  return credit_calculator_->getOutputParametrs();
}
}  // namespace s21