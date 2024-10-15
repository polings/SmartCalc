#include "calcwindow.h"

#include "ui_calcwindow.h"

CalcWindow::CalcWindow(QWidget *parent, s21::CalcController *controller)
    : QMainWindow(parent), controller_(controller), ui(new Ui::CalcWindow) {
  ui->setupUi(this);
  QRegularExpressionValidator *graphValidator = new QRegularExpressionValidator(
      QRegularExpression("^-?(1000000|[0-9]{1,6}(\\.[0-9]{1,7})?$)"));
  ui->x_min->setValidator(graphValidator);
  ui->y_min->setValidator(graphValidator);
  ui->x_max->setValidator(graphValidator);
  ui->y_max->setValidator(graphValidator);

  QRegularExpressionValidator *argXValidator = new QRegularExpressionValidator(
      QRegularExpression("^-?(1000000|[0-9]{1,14}(\\.[0-9]{1,7})?$)"));
  ui->lineEdit_x->setValidator(argXValidator);

  QRegularExpressionValidator *amountValidator =
      new QRegularExpressionValidator(
          QRegularExpression("^(100000000000|[0-9]{1,11})(\\.[0-9]{1,2})?$"));
  ui->amount_credit->setValidator(amountValidator);

  QRegularExpressionValidator *termValidator = new QRegularExpressionValidator(
      QRegularExpression("([0-5]?[0-9]{1,2}|600)"));
  ui->credit_term->setValidator(termValidator);

  QRegularExpressionValidator *rateValidator = new QRegularExpressionValidator(
      QRegularExpression("^(999|[0-9]{1,3})(\\.[0-9]{1,3})?$"));
  ui->interest_rate->setValidator(rateValidator);

  for (auto button : ui->numbersButtonGroup->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(num_clicked()));
  }
  for (auto button : ui->functionButtonGroup->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(trig_clicked()));
  }
  for (auto button : ui->signButtonGroup->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(sign_clicked()));
  }
}

CalcWindow::~CalcWindow() { delete ui; }

std::string CalcWindow::getInputExpression() const {
  return ui->expressionDisplay->text().toStdString();
}

std::string CalcWindow::getArgX() const {
  return ui->lineEdit_x->text().toStdString();
}

void CalcWindow::setResult(double result) {
  ui->expressionDisplay->setText(QString::number(result, 'g', 16));
}

void CalcWindow::setAnnyityCreditResult(s21::OutputParametrs result) {
  ui->mon_payment->setText(QString::number(result.first_payment, 'f', 2));
  ui->over_payment->setText(QString::number(result.interest_charges, 'f', 2));
  ui->total_payment->setText(QString::number(result.total_payment, 'f', 2));
}

void CalcWindow::setDifferentiatedCreditResult(s21::OutputParametrs result) {
  ui->mon_payment->setText(QString::number(result.first_payment, 'f', 2) +
                           " ... " +
                           QString::number(result.last_payment, 'f', 2));
  ui->over_payment->setText(QString::number(result.interest_charges, 'f', 2));
  ui->total_payment->setText(QString::number(result.total_payment, 'f', 2));
}

void CalcWindow::on_ac_clicked() {
  ui->expressionDisplay->clear();
  view_triggers_.dot = false;
  view_triggers_.clear_display = false;
  view_triggers_.open_breaket = 0;
  view_triggers_.close_breaket = 0;
  view_triggers_.num = false;
  view_triggers_.x_val = false;
}

void CalcWindow::num_clicked() {
  ClearDisplay();
  QPushButton *num = (QPushButton *)sender();
  ui->expressionDisplay->setText(ui->expressionDisplay->text() + num->text());
  if (num->text() == "x") view_triggers_.x_val = true;
  view_triggers_.num = true;
}

void CalcWindow::sign_clicked() {
  QPushButton *sign = (QPushButton *)sender();
  QString sign_string = sign->text();
  HandleSignButtonClick(sign_string);
}

void CalcWindow::trig_clicked() {
  ClearDisplay();
  QPushButton *num = (QPushButton *)sender();
  QString result;
  result = ui->expressionDisplay->text() + num->text() + "(";
  ui->expressionDisplay->setText(result);
  view_triggers_.open_breaket++;
  view_triggers_.dot = false;
  view_triggers_.num = false;
}

void CalcWindow::on_equal_clicked() {
  if (ui->expressionDisplay->text().length() != 0) {
    if (view_triggers_.num || view_triggers_.dot) {
      if (view_triggers_.x_val && ui->lineEdit_x->text().length() != 0) {
        int error_code = controller_->CalculateValue(this);
        if (error_code == s21::errorcode::kEverythingOk) {
          double result = controller_->getResult();
          if (result == INFINITY || result == -INFINITY || std::isnan(result)) {
            ui->expressionDisplay->setText("Calculation Error");
          } else {
            setResult(result);
          }
        } else if (error_code == s21::errorcode::kInvalidExpression) {
          ui->expressionDisplay->setText("Error");
        }
        view_triggers_.clear_display = true;
      }
    }
  }
}

void CalcWindow::on_sqrt_clicked() {
  ClearDisplay();
  ui->expressionDisplay->setText(ui->expressionDisplay->text() + "sqrt(");
  view_triggers_.open_breaket++;
  view_triggers_.dot = false;
  view_triggers_.num = false;
}

void CalcWindow::on_dot_clicked() {
  ClearDisplay();
  if (view_triggers_.dot == false) {
    ui->expressionDisplay->setText(ui->expressionDisplay->text() + ".");
    view_triggers_.dot = true;
  }
  view_triggers_.num = false;
}

void CalcWindow::on_div_clicked() { HandleSignButtonClick("/"); }

void CalcWindow::on_mul_clicked() { HandleSignButtonClick("*"); }

void CalcWindow::on_mod_clicked() { HandleSignButtonClick("mod"); }

void CalcWindow::on_pow_clicked() { HandleSignButtonClick("^"); }

void CalcWindow::on_exp_notation_clicked() { HandleSignButtonClick("e"); }

void CalcWindow::on_breackets_clicked() {
  ClearDisplay();
  QString result;
  result = ui->expressionDisplay->text();
  if (result.length() == 0) {
    ui->expressionDisplay->setText("(");
    view_triggers_.open_breaket++;
  } else if (result.back() == '+' || result.back() == '-' ||
             result.back() == '(' || result.back() == '*' ||
             result.back() == '/' || result.back() == '^') {
    ui->expressionDisplay->setText(ui->expressionDisplay->text() + "(");
    view_triggers_.open_breaket++;
  } else if (((result.back() >= '0' && result.back() <= '9') ||
              result.back() == ')' || result.back() == '.' ||
              result.back() == 'x') &&
             (view_triggers_.open_breaket > view_triggers_.close_breaket)) {
    ui->expressionDisplay->setText(ui->expressionDisplay->text() + ")");
    view_triggers_.close_breaket++;
  } else if (view_triggers_.open_breaket == view_triggers_.close_breaket) {
    ui->expressionDisplay->setText(ui->expressionDisplay->text() + "(");
    view_triggers_.open_breaket++;
  }
}

void CalcWindow::ClearDisplay() {
  if (view_triggers_.clear_display) {
    on_ac_clicked();
  }
}

void CalcWindow::CheckConstraintsAndConcat(QString string,
                                           QString concat_string) {
  if (string.length() != 0) {
    if (string.back() != '+' && string.back() != '-' && string.back() != '*' &&
        string.back() != '/' && string.back() != '^' && string.back() != 'd' &&
        (string.back() != 'e' || concat_string == "+" ||
         concat_string == "-") &&
        (string.back() != '(' || concat_string == "+" ||
         concat_string == "-")) {
      string += concat_string;
    }
  } else if (concat_string == "+" || concat_string == "-") {
    string += concat_string;
  }

  ui->expressionDisplay->setText(string);
}

void CalcWindow::HandleSignButtonClick(QString sign) {
  ClearDisplay();
  QString result_string = ui->expressionDisplay->text();
  CheckConstraintsAndConcat(result_string, sign);
  view_triggers_.dot = false;
  view_triggers_.num = false;
}

void CalcWindow::on_drawButton_clicked() {
  if (ui->expressionDisplay->text().length() != 0) {
    QVector<double> x, y;
    double xMinValue = xMinDefault;
    double xMaxValue = xMaxDefault;
    double yMinValue = yMinDefault;
    double yMaxValue = yMaxDefault;
    QString xMin = ui->x_min->text();
    QString yMin = ui->y_min->text();
    QString xMax = ui->x_max->text();
    QString yMax = ui->y_max->text();
    if (xMin != "") xMinValue = xMin.toDouble();
    if (yMin != "") yMinValue = yMin.toDouble();
    if (xMax != "") xMaxValue = xMax.toDouble();
    if (yMax != "") yMaxValue = yMax.toDouble();

    ui->widget->removeGraph(0);
    double step = 0.1;
    std::string expression = getInputExpression();
    double result = 0;
    for (double i = xMinValue; i <= xMaxValue; i += step) {
      int error_code =
          controller_->CalculateGraphValue(expression, std::to_string(i));
      if (error_code == s21::errorcode::kEverythingOk) {
        result = controller_->getResult();
        x.push_back(i);
        y.push_back(result);
      }
    }
    ui->widget->xAxis->setRange(xMinValue, xMaxValue);
    ui->widget->yAxis->setRange(yMinValue, yMaxValue);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->widget->update();
    x.clear();
    y.clear();
  }
}

void CalcWindow::on_annuity_clicked() {
  HandleCreditButtonClicked(s21::PaymentType::kAnnyity);
}

void CalcWindow::on_differentiated_clicked() {
  HandleCreditButtonClicked(s21::PaymentType::kDifferentiated);
}

void CalcWindow::HandleCreditButtonClicked(s21::PaymentType credit_type) {
  ui->err_label->clear();
  if (ui->amount_credit->text().length() != 0 &&
      ui->credit_term->text().length() != 0 &&
      ui->interest_rate->text().length() != 0) {
    s21::InputParametrs parametrs;
    parametrs.type_of_payments = credit_type;
    parametrs.credit_amount = ui->amount_credit->text().toDouble();
    parametrs.credit_term = ui->credit_term->text().toDouble();
    parametrs.interest_rate = ui->interest_rate->text().toDouble();

    int error_code = controller_->CalculateCredit(parametrs);
    if (error_code == s21::errorcode::kEverythingOk) {
      s21::OutputParametrs result = controller_->getCreditResult();
      if (credit_type == s21::PaymentType::kAnnyity) {
        setAnnyityCreditResult(result);
      } else if (credit_type == s21::PaymentType::kDifferentiated) {
        setDifferentiatedCreditResult(result);
      }

    } else if (error_code == s21::errorcode::kInvalidExpression) {
      ui->err_label->setText("Credit term and interest rate can't be 0");
    }
  } else {
    ui->err_label->setText("Fill all the fields");
  }
}
