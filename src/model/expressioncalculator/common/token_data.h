#ifndef CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_COMMON_TOKEN_DATA_H
#define CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_COMMON_TOKEN_DATA_H

#include <string>

namespace s21 {
enum class Priority {
  kOpenBracket,
  kCloseBracket,
  kNumber,
  kAddSub,
  kDivMultMod,
  kPower,
  kFunction
};

class Token {
 public:
  Token(double value)
      : value_(value),
        type_("number"),
        priority_(Priority::kNumber),
        unary_sign_(false) {}
  Token(std::string type, Priority priority)
      : value_(0), type_(type), priority_(priority), unary_sign_(false) {}

  double getTokenValue() { return value_; }
  std::string getTokenType() { return type_; }
  bool getUnarySign() const { return unary_sign_; }
  void setUnarySign(bool isUnary) { unary_sign_ = isUnary; }
  Priority getPriority() const { return priority_; }

 private:
  double value_;
  std::string type_;
  Priority priority_;
  bool unary_sign_;
};

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_MODEL_EXPRESSIONCALCULATOR_COMMON_TOKEN_DATA_H