#ifndef CPP3_SMARTCALC_SRC_MODEL_CREDITCALCULATOR_CREDIT_CALCULATOR_H
#define CPP3_SMARTCALC_SRC_MODEL_CREDITCALCULATOR_CREDIT_CALCULATOR_H

#include <cmath>

#include "credit_data.h"

namespace s21 {
class CreditCalculator {
 public:
  CreditCalculator() = default;
  ~CreditCalculator() = default;

  void setInputParametrs(InputParametrs parametrs);
  OutputParametrs getOutputParametrs();

  int CalculateCredit();
  int OutputParametrsValidator() const;
  int InputParametrsValidator() const;
  int CalculateTotalPayment();
  double CalculateAnnuityPayment(double monthly_rate);
  double CalculateDifferentiatedLastPayment(double monthly_rate);
  void ClearData();

 private:
  InputParametrs input_parametrs_;
  OutputParametrs output_parametrs_;
};

namespace errorcode::CreditCalculator {
const int kEverythingOk = 0;
const int kInvalidExpression = 1;
}  // namespace errorcode::CreditCalculator

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_CREDITCALCULATOR_CREDIT_CALCULATOR_H