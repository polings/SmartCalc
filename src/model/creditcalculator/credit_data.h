#ifndef CPP3_SMARTCALC_SRC_MODEL_CREDITCALCULATOR_CREDIT_DATA_H
#define CPP3_SMARTCALC_SRC_MODEL_CREDITCALCULATOR_CREDIT_DATA_H

namespace s21 {
enum class PaymentType { kNone, kAnnyity, kDifferentiated };

struct InputParametrs {
  double credit_amount;
  int credit_term;
  double interest_rate;
  PaymentType type_of_payments;
};

struct OutputParametrs {
  double first_payment;
  double last_payment;
  double interest_charges;
  double total_payment;
};

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_CREDITCALCULATOR_CREDIT_DATA_H