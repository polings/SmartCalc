#include "controller.h"

#include "../view/calcwindow.h"

namespace s21 {
int CalcController::CalculateValue(CalcWindow* calc_window) {
  int error_code = model_->CalculateExpression(
      calc_window->getInputExpression(), calc_window->getArgX());
  return error_code;
}

double CalcController::getResult() const {
  return model_->getExpressionResult();
}

int CalcController::CalculateGraphValue(const std::string& input_expression,
                                        const std::string& arg_x) {
  int error_code = model_->CalculateExpression(input_expression, arg_x);
  return error_code;
}

int CalcController::CalculateCredit(InputParametrs parametrs) {
  int error_code = model_->CalculateCredit(parametrs);
  return error_code;
}

OutputParametrs CalcController::getCreditResult() const {
  return model_->getCreditResult();
}

}  // namespace s21
