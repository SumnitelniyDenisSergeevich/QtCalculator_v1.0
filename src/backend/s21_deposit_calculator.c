#include <math.h>

#include "s21_calculator.h"

void Capitalization(deposit_calc_output_t* result,
                    const deposit_calc_input_t* input,
                    double* temp_accrued_interest, int* month, int* year);
void AddList(const deposit_calc_input_t* input, deposit_calc_output_t* result,
             int day);
void SubList(const deposit_calc_input_t* input, deposit_calc_output_t* result,
             int day);

deposit_calc_output_t deposit_calculator(const deposit_calc_input_t* input) {
  deposit_calc_output_t result;
  result.deposit_amount_end = input->deposit_amount;
  result.tax_amount = 0.;
  result.accrued_interest = 0.;
  double tax_min_amount = 1000000. * input->tax_rate / 100.;
  double year_sum = 0.;
  int k = 1;
  int month = 1;
  int year = 1;
  double temp_accrued_interest = 0.;
  for (int i = 1; i <= input->term * 30; ++i, ++k, ++month, ++year) {
    if (k == 365) {
      if (year_sum > tax_min_amount)
        result.tax_amount += round((year_sum - tax_min_amount) * 13.) / 100.;
      k = 0;
      year_sum = 0.;
    }
    double accrued_interest =
        round(result.deposit_amount_end * input->interest_rate / 365.) / 100.;
    result.accrued_interest += accrued_interest;
    year_sum += accrued_interest;
    AddList(input, &result, i);
    SubList(input, &result, i);
    if (input->capitalization_of_interest) {
      Capitalization(&result, input, &temp_accrued_interest, &month, &year);
    }
  }
  if (input->capitalization_of_interest) {
    result.deposit_amount_end +=
        result.accrued_interest - temp_accrued_interest;
  }
  if (year_sum > tax_min_amount) {
    result.tax_amount +=
        round((year_sum - tax_min_amount) * 13. / 365. * k) / 100.;
  }
  return result;
}

void Capitalization(deposit_calc_output_t* result,
                    const deposit_calc_input_t* input,
                    double* temp_accrued_interest, int* month, int* year) {
  switch (input->periodicity_of_payments) {
    case 0:
      result->deposit_amount_end +=
          result->accrued_interest - *temp_accrued_interest;
      *temp_accrued_interest = result->accrued_interest;
      break;
    case 1:
      if (*month == 30) {
        result->deposit_amount_end +=
            result->accrued_interest - *temp_accrued_interest;
        *temp_accrued_interest = result->accrued_interest;
        *month = 0;
      }
      break;
    case 2:
      if (*year == 365) {
        result->deposit_amount_end +=
            result->accrued_interest - *temp_accrued_interest;
        *temp_accrued_interest = result->accrued_interest;
        *year = 0;
      }
      break;
  }
}

void AddList(const deposit_calc_input_t* input, deposit_calc_output_t* result,
             int day) {
  for (int i = 0; i < input->rep_list_size; ++i) {
    if (input->replenishments_list[i].period == (day / 30 + 1) &&
        ((day % 30) == 1)) {
      result->deposit_amount_end += input->replenishments_list[i].sum;
    }
  }
}

void SubList(const deposit_calc_input_t* input, deposit_calc_output_t* result,
             int day) {
  for (int i = 0; i < input->par_list_size; ++i) {
    if (input->partial_withdrawals_list[i].period == (day / 30 + 1) &&
        ((day % 30) == 1)) {
      result->deposit_amount_end -= input->partial_withdrawals_list[i].sum;
    }
  }
}
