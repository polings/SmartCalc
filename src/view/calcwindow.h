#ifndef CPP3_SMARTCALC_SRC_VIEW_CALCWINDOW_H
#define CPP3_SMARTCALC_SRC_VIEW_CALCWINDOW_H

#include <QMainWindow>

#include "../controller/controller.h"

namespace s21 {
class CalcController;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcWindow;
}
QT_END_NAMESPACE

struct TriggersChecks {
  bool dot = false;
  bool clear_display = false;
  int open_breaket = 0;
  int close_breaket = 0;
  bool num = false;
  bool x_val = false;
};

class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  CalcWindow(QWidget *parent = nullptr,
             s21::CalcController *controller = nullptr);
  ~CalcWindow();
  std::string getInputExpression() const;
  std::string getArgX() const;
  void setResult(double res);
  void setAnnyityCreditResult(s21::OutputParametrs result);
  void setDifferentiatedCreditResult(s21::OutputParametrs result);
  void ClearDisplay();
  void CheckConstraintsAndConcat(QString string, QString concat_string);
  void HandleSignButtonClick(QString sign);
  void HandleCreditButtonClicked(s21::PaymentType credit_type);

 private slots:
  void num_clicked();
  void sign_clicked();
  void trig_clicked();
  void on_ac_clicked();
  void on_equal_clicked();
  void on_sqrt_clicked();
  void on_dot_clicked();
  void on_div_clicked();
  void on_mul_clicked();
  void on_mod_clicked();
  void on_pow_clicked();
  void on_exp_notation_clicked();
  void on_breackets_clicked();
  void on_drawButton_clicked();
  void on_annuity_clicked();
  void on_differentiated_clicked();

 private:
  TriggersChecks view_triggers_;
  Ui::CalcWindow *ui;
  s21::CalcController *controller_;
  int xMinDefault = -5, yMinDefault = -5, xMaxDefault = 5, yMaxDefault = 5;
};
#endif  // CPP3_SMARTCALC_SRC_VIEW_CALCWINDOW_H
