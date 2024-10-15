#include <QApplication>

#include "controller/controller.h"
#include "model/model.h"
#include "view/calcwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::ExpressionCalculator calculator;
  s21::CreditCalculator credit_calculator;
  s21::Model model(&calculator, &credit_calculator);
  s21::CalcController controller(&model);
  CalcWindow view(nullptr, &controller);
  view.show();
  return a.exec();
}
