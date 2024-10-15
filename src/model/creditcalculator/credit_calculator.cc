#include "credit_calculator.h"

namespace s21 {

void CreditCalculator::setInputParametrs(InputParametrs parametrs) {
  input_parametrs_ = parametrs;
}

OutputParametrs CreditCalculator::getOutputParametrs() {
  return output_parametrs_;
}

int CreditCalculator::CalculateCredit() {
  int error_code = errorcode::CreditCalculator::kEverythingOk;
  ClearData();
  error_code = InputParametrsValidator();
  if (error_code == errorcode::CreditCalculator::kEverythingOk) {
    error_code = CalculateTotalPayment();
    if (error_code == errorcode::CreditCalculator::kEverythingOk) {
      error_code = OutputParametrsValidator();
    }
  }
  return error_code;
}

int CreditCalculator::InputParametrsValidator() const {
  int error_code = errorcode::CreditCalculator::kEverythingOk;
  if (input_parametrs_.credit_term == 0 ||
      input_parametrs_.interest_rate == 0 ||
      input_parametrs_.type_of_payments == PaymentType::kNone) {
    error_code = errorcode::CreditCalculator::kInvalidExpression;
  }
  return error_code;
}

int CreditCalculator::OutputParametrsValidator() const {
  int error_code = errorcode::CreditCalculator::kEverythingOk;
  if (std::isinf(output_parametrs_.first_payment) ||
      std::isnan(output_parametrs_.first_payment) ||
      std::isinf(output_parametrs_.first_payment) ||
      std::isnan(output_parametrs_.first_payment) ||
      std::isinf(output_parametrs_.interest_charges) ||
      std::isnan(output_parametrs_.interest_charges) ||
      std::isinf(output_parametrs_.total_payment) ||
      std::isnan(output_parametrs_.total_payment)) {
    error_code = errorcode::CreditCalculator::kInvalidExpression;
  }
  return error_code;
}

int CreditCalculator::CalculateTotalPayment() {
  int error_code = errorcode::CreditCalculator::kEverythingOk;
  double monthly_interest_rate = input_parametrs_.interest_rate / 100 / 12;
  if (input_parametrs_.type_of_payments == PaymentType::kAnnyity) {
    output_parametrs_.first_payment =
        CalculateAnnuityPayment(monthly_interest_rate);
    output_parametrs_.last_payment = output_parametrs_.first_payment;
    output_parametrs_.total_payment =
        output_parametrs_.first_payment * input_parametrs_.credit_term;
  } else if (input_parametrs_.type_of_payments ==
             PaymentType::kDifferentiated) {
    output_parametrs_.first_payment =
        input_parametrs_.credit_amount / input_parametrs_.credit_term +
        input_parametrs_.credit_amount * monthly_interest_rate;
    output_parametrs_.last_payment =
        CalculateDifferentiatedLastPayment(monthly_interest_rate);
  } else {
    error_code = errorcode::CreditCalculator::kInvalidExpression;
  }
  if (error_code == errorcode::CreditCalculator::kEverythingOk) {
    output_parametrs_.interest_charges =
        output_parametrs_.total_payment - input_parametrs_.credit_amount;
  }

  return error_code;
}

double CreditCalculator::CalculateAnnuityPayment(double monthly_rate) {
  double payment = 0;
  double multiplier = pow(1 + monthly_rate, input_parametrs_.credit_term);
  payment = (input_parametrs_.credit_amount * multiplier * monthly_rate) /
            (multiplier - 1);
  return payment;
}

double CreditCalculator::CalculateDifferentiatedLastPayment(
    double monthly_rate) {
  double payment = 0;
  int term = input_parametrs_.credit_term;
  double amount = input_parametrs_.credit_amount;
  double monPayWithRate = 0;
  double monPayWithoutRate = amount / term;
  for (int i = 0; i < term; i++) {
    monPayWithRate =
        monPayWithoutRate + (amount - (monPayWithoutRate * i)) * monthly_rate;
    if (i == (term - 1)) {
      payment = monPayWithRate;
    }
    output_parametrs_.total_payment += monPayWithRate;
  }
  return payment;
}

void CreditCalculator::ClearData() {
  output_parametrs_.first_payment = 0;
  output_parametrs_.interest_charges = 0;
  output_parametrs_.last_payment = 0;
  output_parametrs_.total_payment = 0;
}

}  // namespace s21