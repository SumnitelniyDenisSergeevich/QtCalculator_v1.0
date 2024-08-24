#include <math.h>
#include <stdlib.h>

#include "s21_calculator.h"

void credit_calculator(const credit_calc_input_t* input,
                       credit_calc_output_t* output) {
  double persent_rate = input->interest_rate / 1200.;
  if (input->type == 0) {
    output->monthly_payment = (double*)malloc(sizeof(double));
    if (persent_rate < 1e-7 && input->term == 0) {
      *output->monthly_payment = 0;
    } else if (persent_rate < 1e-7) {
      *output->monthly_payment = input->total_amount / input->term;
    } else {
      *output->monthly_payment =
          input->total_amount *
          (persent_rate +
           persent_rate / (pow(1 + persent_rate, input->term) - 1));
    }
    *output->monthly_payment = round(*output->monthly_payment * 100.) / 100.;
    output->total_paymen = *output->monthly_payment * input->term;
    output->overpayment = output->total_paymen - input->total_amount;
  } else {
    output->monthly_payment = (double*)malloc(sizeof(double) * input->term);
    double monthly_payment_amount = input->total_amount / input->term;
    output->total_paymen = 0.;
    for (int i = 0; i < input->term; ++i) {
      output->monthly_payment[i] =
          (input->total_amount - i * monthly_payment_amount) * persent_rate +
          monthly_payment_amount;
      output->monthly_payment[i] =
          round(output->monthly_payment[i] * 100.) / 100.;
      output->total_paymen += output->monthly_payment[i];
    }
    output->overpayment = output->total_paymen - input->total_amount;
  }
}
