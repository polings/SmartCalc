#ifndef CPP3_SMARTCALC_SRC_CONTROLLER_CONTROLLER_H
#define CPP3_SMARTCALC_SRC_CONTROLLER_CONTROLLER_H

#include <iostream>

#include "../model/model.h"

class CalcWindow;

namespace s21 {
class CalcController {
 public:
  CalcController(Model *m) : model_(m){};
  ~CalcController() = default;
  int CalculateValue(CalcWindow *calc_window);
  double getResult() const;
  int CalculateGraphValue(const std::string &input_expression,
                          const std::string &arg_x);
  int CalculateCredit(InputParametrs parametrs);
  OutputParametrs getCreditResult() const;

 private:
  Model *model_;
};

};      // namespace s21
#endif  // CPP3_SMARTCALC_SRC_CONTROLLER_CONTROLLER_H
