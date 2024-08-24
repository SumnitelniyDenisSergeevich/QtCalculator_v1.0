#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_calculator.h"

#define PARSE_ERROR 1
#define LOGIC_ERROR 2
#define OK 0

START_TEST(calculate_simple_1) {
  char inf[20] = "0/0";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_nan(res);
}
END_TEST

START_TEST(calculate_simple_2) {
  char inf[20] = "2+3+4*5";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 25, 1e-7);
}
END_TEST

START_TEST(calculate_simple_3) {
  char inf[20] = "cos((x)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, LOGIC_ERROR);
}
END_TEST

START_TEST(calculate_simple_4) {
  char inf[20] = "sin(+20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, sin(+20), 1e-7);
}
END_TEST

START_TEST(calculate_simple_5) {
  char inf[40] = "2 ** 4";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, LOGIC_ERROR);
}
END_TEST

START_TEST(calculate_simple_6) {
  char inf[40] = "cos(+ * 10)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, LOGIC_ERROR);
}
END_TEST

START_TEST(calculate_simple_7) {
  char inf[40] = "sin() * 2 + 5";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, LOGIC_ERROR);
}
END_TEST

START_TEST(calculate_simple_8) {
  char inf[40] = "cos(x) /";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, LOGIC_ERROR);
}
END_TEST

START_TEST(calculate_simple_9) {
  char inf[40] = "cos(* 10 + 5)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, LOGIC_ERROR);
}
END_TEST

START_TEST(calculate_simple_10) {
  char inf[20] = "cos(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, cos(-20), 1e-7);
}
END_TEST

START_TEST(calculate_parse_1) {
  char inf[20] = "sin!(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_2) {
  char inf[20] = "cox(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_3) {
  char inf[20] = "tang(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_4) {
  char inf[20] = "asix(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_5) {
  char inf[20] = "acox(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_6) {
  char inf[20] = "akan(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_7) {
  char inf[20] = "sqrlt(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_8) {
  char inf[20] = "lg(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_9) {
  char inf[20] = "lon(-20)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_parse_10) {
  char inf[20] = "2 ! 3";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, PARSE_ERROR);
}
END_TEST

START_TEST(calculate_func_1) {
  char inf[20] = "sin(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, sin(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_2) {
  char inf[20] = "cos(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, cos(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_3) {
  char inf[20] = "tan(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, tan(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_4) {
  char inf[20] = "asin(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, asin(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_5) {
  char inf[20] = "acos(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, acos(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_6) {
  char inf[20] = "atan(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, atan(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_7) {
  char inf[20] = "sqrt(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, sqrt(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_8) {
  char inf[20] = "ln(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, log(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_9) {
  char inf[20] = "log(1)";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, log10(1), 1e-7);
}
END_TEST

START_TEST(calculate_func_10) {
  char inf[20] = "3.14 * 5.3";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 3.14 * 5.3, 1e-7);
}
END_TEST

START_TEST(calculate_func_11) {
  char inf[20] = "3.14 + 5.3";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 3.14 + 5.3, 1e-7);
}
END_TEST

START_TEST(calculate_func_12) {
  char inf[20] = "3.14 - 5.3";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 3.14 - 5.3, 1e-7);
}
END_TEST

START_TEST(calculate_func_13) {
  char inf[20] = "3.14 / 5.3";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 3.14 / 5.3, 1e-7);
}
END_TEST

START_TEST(calculate_random_1) {
  char inf[20] = "2 + 3 * 5";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 2 + 3 * 5, 1e-7);
}
END_TEST

START_TEST(calculate_random_2) {
  char inf[20] = "(2 + 3) * 5";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, (2 + 3) * 5, 1e-7);
}
END_TEST

START_TEST(calculate_random_3) {
  char inf[20] = "2 + -3 * 5";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 2 + -3 * 5, 1e-7);
}
END_TEST

START_TEST(calculate_random_4) {
  char inf[20] = "2.13 mod 1.1";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, fmod(2.13, 1.1), 1e-7);
}
END_TEST

START_TEST(calculate_random_5) {
  char inf[20] = "2.13 ^ 1.1";
  double res;
  int err = infix_notation(inf, 0, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, pow(2.13, 1.1), 1e-7);
}
END_TEST

START_TEST(calculate_random_6) {
  char inf[20] = "2.13 ^ x";
  double res;
  int err = infix_notation(inf, 1.1, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, pow(2.13, 1.1), 1e-7);
}
END_TEST

START_TEST(calculate_random_7) {
  char inf[20] = "(-2) + (+3) * (-5)";
  double res;
  int err = infix_notation(inf, 1.1, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, (-2) + (+3) * (-5), 1e-7);
}
END_TEST

START_TEST(calculate_random_8) {
  char inf[20] = "-2 + (+3) * (-5)";
  double res;
  int err = infix_notation(inf, 1.1, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, -2 + (+3) * (-5), 1e-7);
}
END_TEST

START_TEST(calculate_random_9) {
  char inf[20] = "2 sin(x)";
  double res;
  int err = infix_notation(inf, 1.1, &res);
  ck_assert_int_eq(err, OK);
  ck_assert_double_eq_tol(res, 2 * sin(1.1), 1e-7);
}
END_TEST

START_TEST(calculate_credit_1) {
  credit_calc_input_t input;
  input.interest_rate = 9.6;
  input.term = 18;
  input.total_amount = 16000000;
  input.type = 0;
  credit_calc_output_t output = {0};

  credit_calculator(&input, &output);
  ck_assert_double_eq_tol(output.overpayment, 1243443.62, 1e-1);
  ck_assert_double_eq_tol(output.total_paymen, 17243443.62, 1);
  ck_assert_double_eq_tol(*output.monthly_payment, 957969.09, 1e-2);
  free(output.monthly_payment);
}
END_TEST

START_TEST(calculate_credit_2) {
  credit_calc_input_t input;
  input.interest_rate = 9.6;
  input.term = 18;
  input.total_amount = 16000000;
  input.type = 1;
  credit_calc_output_t output = {0};

  credit_calculator(&input, &output);
  ck_assert_double_eq_tol(output.overpayment, 1216000, 1);
  ck_assert_double_eq_tol(output.total_paymen, 17216000, 10);
  double origin[18];
  origin[0] = 1016888.89;
  origin[1] = 1009777.78;
  origin[2] = 1002666.67;
  origin[3] = 995555.56;
  origin[4] = 988444.44;
  origin[5] = 981333.33;
  origin[6] = 974222.22;
  origin[7] = 967111.11;
  origin[8] = 960000.00;
  origin[9] = 952888.89;
  origin[10] = 945777.78;
  origin[11] = 938666.67;
  origin[12] = 931555.56;
  origin[13] = 924444.44;
  origin[14] = 917333.33;
  origin[15] = 910222.22;
  origin[16] = 903111.11;
  origin[17] = 896000.00;
  for (int i = 0; i < 18; ++i) {
    ck_assert_double_eq_tol(output.monthly_payment[i], origin[i], 1e-1);
  }
  free(output.monthly_payment);
}
END_TEST

START_TEST(calculate_deposit_1) {
  deposit_calc_input_t input;

  input.capitalization_of_interest = 0;  // 0 - без кап 1 - с кап

  input.deposit_amount = 5000000;
  input.interest_rate = 10.;
  input.periodicity_of_payments =
      0;  // 0 - ежедневно 1 - ежемесячно 2 - ежегодно
  input.tax_rate = 7.5;
  input.term = 24;  // количество месяцев

  input.replenishments_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.rep_list_size = 4;
  input.replenishments_list[0].period = 1;
  input.replenishments_list[0].sum = 1000000;

  input.replenishments_list[1].period = 3;
  input.replenishments_list[1].sum = 2000000;

  input.replenishments_list[2].period = 5;
  input.replenishments_list[2].sum = 30000000;

  input.replenishments_list[3].period = 7;
  input.replenishments_list[3].sum = 40000000;

  input.partial_withdrawals_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.par_list_size = 4;

  input.partial_withdrawals_list[0].period = 2;
  input.partial_withdrawals_list[0].sum = 1500000;

  input.partial_withdrawals_list[1].period = 4;
  input.partial_withdrawals_list[1].sum = 2500000;

  input.partial_withdrawals_list[2].period = 6;
  input.partial_withdrawals_list[2].sum = 3500000;

  input.partial_withdrawals_list[3].period = 8;
  input.partial_withdrawals_list[3].sum = 4500000;

  deposit_calc_output_t output = deposit_calculator(&input);
  free(input.partial_withdrawals_list);
  free(input.replenishments_list);
  ck_assert_double_eq_tol(output.accrued_interest, 10487396.47, 1);
  ck_assert_double_eq_tol(output.deposit_amount_end, 66000000.00, 1);
  ck_assert_double_eq_tol(output.tax_amount, 1323467.45, 1e-1);
}
END_TEST

START_TEST(calculate_deposit_2) {
  deposit_calc_input_t input;

  input.capitalization_of_interest = 1;  // 0 - без кап 1 - с кап

  input.deposit_amount = 5000000;
  input.interest_rate = 10.;
  input.periodicity_of_payments =
      0;  // 0 - ежедневно 1 - ежемесячно 2 - ежегодно
  input.tax_rate = 7.5;
  input.term = 24;  // количество месяцев

  input.replenishments_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.rep_list_size = 4;
  input.replenishments_list[0].period = 1;
  input.replenishments_list[0].sum = 1000000;

  input.replenishments_list[1].period = 3;
  input.replenishments_list[1].sum = 2000000;

  input.replenishments_list[2].period = 5;
  input.replenishments_list[2].sum = 3000000;

  input.replenishments_list[3].period = 7;
  input.replenishments_list[3].sum = 4000000;

  input.partial_withdrawals_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.par_list_size = 4;

  input.partial_withdrawals_list[0].period = 2;
  input.partial_withdrawals_list[0].sum = 1500000;

  input.partial_withdrawals_list[1].period = 4;
  input.partial_withdrawals_list[1].sum = 2500000;

  input.partial_withdrawals_list[2].period = 6;
  input.partial_withdrawals_list[2].sum = 3500000;

  input.partial_withdrawals_list[3].period = 8;
  input.partial_withdrawals_list[3].sum = 4500000;

  deposit_calc_output_t output = deposit_calculator(&input);
  free(input.partial_withdrawals_list);
  free(input.replenishments_list);
  ck_assert_double_eq_tol(output.accrued_interest, 829559.68, 1e-1);
  ck_assert_double_eq_tol(output.deposit_amount_end, 3829559.68, 1e-1);
  ck_assert_double_eq_tol(output.tax_amount, 87442.56, 1e-1);
}
END_TEST

START_TEST(calculate_deposit_3) {
  deposit_calc_input_t input;
  input.capitalization_of_interest = 1;  // 0 - без кап 1 - с кап
  input.deposit_amount = 5000000;
  input.interest_rate = 10.;
  input.periodicity_of_payments =
      0;  // 0 - ежедневно 1 - ежемесячно 2 - ежегодно
  input.tax_rate = 7.5;
  input.term = 24;  // количество месяцев

  input.replenishments_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.rep_list_size = 4;
  input.replenishments_list[0].period = 1;
  input.replenishments_list[0].sum = 1000000;

  input.replenishments_list[1].period = 3;
  input.replenishments_list[1].sum = 2000000;

  input.replenishments_list[2].period = 5;
  input.replenishments_list[2].sum = 3000000;

  input.replenishments_list[3].period = 7;
  input.replenishments_list[3].sum = 4000000;

  input.partial_withdrawals_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.par_list_size = 4;

  input.partial_withdrawals_list[0].period = 2;
  input.partial_withdrawals_list[0].sum = 1500000;

  input.partial_withdrawals_list[1].period = 4;
  input.partial_withdrawals_list[1].sum = 2500000;

  input.partial_withdrawals_list[2].period = 6;
  input.partial_withdrawals_list[2].sum = 3500000;

  input.partial_withdrawals_list[3].period = 8;
  input.partial_withdrawals_list[3].sum = 4500000;

  deposit_calc_output_t output = deposit_calculator(&input);
  free(input.partial_withdrawals_list);
  free(input.replenishments_list);
  ck_assert_double_eq_tol(output.accrued_interest, 829559.68, 1e-2);
  ck_assert_double_eq_tol(output.deposit_amount_end, 3829559.68, 1e-1);
  ck_assert_double_eq_tol(output.tax_amount, 87442.56, 1e-3);
}
END_TEST

START_TEST(calculate_deposit_4) {
  deposit_calc_input_t input;

  input.capitalization_of_interest = 1;  // 0 - без кап 1 - с кап

  input.deposit_amount = 5000000;
  input.interest_rate = 10.;
  input.periodicity_of_payments =
      1;  // 0 - ежедневно 1 - ежемесячно 2 - ежегодно
  input.tax_rate = 7.5;
  input.term = 24;  // количество месяцев

  input.replenishments_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.rep_list_size = 4;
  input.replenishments_list[0].period = 1;
  input.replenishments_list[0].sum = 1000000;

  input.replenishments_list[1].period = 3;
  input.replenishments_list[1].sum = 2000000;

  input.replenishments_list[2].period = 5;
  input.replenishments_list[2].sum = 3000000;

  input.replenishments_list[3].period = 7;
  input.replenishments_list[3].sum = 4000000;

  input.partial_withdrawals_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.par_list_size = 4;

  input.partial_withdrawals_list[0].period = 2;
  input.partial_withdrawals_list[0].sum = 1500000;

  input.partial_withdrawals_list[1].period = 4;
  input.partial_withdrawals_list[1].sum = 2500000;

  input.partial_withdrawals_list[2].period = 6;
  input.partial_withdrawals_list[2].sum = 3500000;

  input.partial_withdrawals_list[3].period = 8;
  input.partial_withdrawals_list[3].sum = 4500000;

  deposit_calc_output_t output = deposit_calculator(&input);
  free(input.partial_withdrawals_list);
  free(input.replenishments_list);
  ck_assert_double_eq_tol(output.accrued_interest, 825902.57, 1e-2);
  ck_assert_double_eq_tol(output.deposit_amount_end, 3825902.57, 1e-1);
  ck_assert_double_eq_tol(output.tax_amount, 86972.56, 1e-3);
}
END_TEST

START_TEST(calculate_deposit_5) {
  deposit_calc_input_t input;

  input.capitalization_of_interest = 1;  // 0 - без кап 1 - с кап

  input.deposit_amount = 5000000;
  input.interest_rate = 10.;
  input.periodicity_of_payments =
      2;  // 0 - ежедневно 1 - ежемесячно 2 - ежегодно
  input.tax_rate = 7.5;
  input.term = 24;  // количество месяцев

  input.replenishments_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.rep_list_size = 4;
  input.replenishments_list[0].period = 1;
  input.replenishments_list[0].sum = 1000000;

  input.replenishments_list[1].period = 3;
  input.replenishments_list[1].sum = 2000000;

  input.replenishments_list[2].period = 5;
  input.replenishments_list[2].sum = 3000000;

  input.replenishments_list[3].period = 7;
  input.replenishments_list[3].sum = 4000000;

  input.partial_withdrawals_list =
      (deposit_list_t *)malloc(sizeof(deposit_list_t) * 4);
  input.par_list_size = 4;

  input.partial_withdrawals_list[0].period = 2;
  input.partial_withdrawals_list[0].sum = 1500000;

  input.partial_withdrawals_list[1].period = 4;
  input.partial_withdrawals_list[1].sum = 2500000;

  input.partial_withdrawals_list[2].period = 6;
  input.partial_withdrawals_list[2].sum = 3500000;

  input.partial_withdrawals_list[3].period = 8;
  input.partial_withdrawals_list[3].sum = 4500000;

  deposit_calc_output_t output = deposit_calculator(&input);
  free(input.partial_withdrawals_list);
  free(input.replenishments_list);
  ck_assert_double_eq_tol(output.accrued_interest, 783893.89, 1e-1);
  ck_assert_double_eq_tol(output.deposit_amount_end, 3783893.89, 1);
  ck_assert_double_eq_tol(output.tax_amount, 81568.87, 1e-1);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, calculate_simple_1);
  tcase_add_test(tc_core, calculate_simple_2);
  tcase_add_test(tc_core, calculate_simple_3);
  tcase_add_test(tc_core, calculate_simple_4);
  tcase_add_test(tc_core, calculate_simple_5);
  tcase_add_test(tc_core, calculate_simple_6);
  tcase_add_test(tc_core, calculate_simple_7);
  tcase_add_test(tc_core, calculate_simple_8);
  tcase_add_test(tc_core, calculate_simple_9);
  tcase_add_test(tc_core, calculate_simple_10);

  tcase_add_test(tc_core, calculate_parse_1);
  tcase_add_test(tc_core, calculate_parse_2);
  tcase_add_test(tc_core, calculate_parse_3);
  tcase_add_test(tc_core, calculate_parse_4);
  tcase_add_test(tc_core, calculate_parse_5);
  tcase_add_test(tc_core, calculate_parse_6);
  tcase_add_test(tc_core, calculate_parse_7);
  tcase_add_test(tc_core, calculate_parse_8);
  tcase_add_test(tc_core, calculate_parse_9);
  tcase_add_test(tc_core, calculate_parse_10);

  tcase_add_test(tc_core, calculate_func_1);
  tcase_add_test(tc_core, calculate_func_2);
  tcase_add_test(tc_core, calculate_func_3);
  tcase_add_test(tc_core, calculate_func_4);
  tcase_add_test(tc_core, calculate_func_5);
  tcase_add_test(tc_core, calculate_func_6);
  tcase_add_test(tc_core, calculate_func_7);
  tcase_add_test(tc_core, calculate_func_8);
  tcase_add_test(tc_core, calculate_func_9);
  tcase_add_test(tc_core, calculate_func_10);
  tcase_add_test(tc_core, calculate_func_11);
  tcase_add_test(tc_core, calculate_func_12);
  tcase_add_test(tc_core, calculate_func_13);

  tcase_add_test(tc_core, calculate_random_1);
  tcase_add_test(tc_core, calculate_random_2);
  tcase_add_test(tc_core, calculate_random_3);
  tcase_add_test(tc_core, calculate_random_4);
  tcase_add_test(tc_core, calculate_random_5);
  tcase_add_test(tc_core, calculate_random_6);
  tcase_add_test(tc_core, calculate_random_7);
  tcase_add_test(tc_core, calculate_random_8);
  tcase_add_test(tc_core, calculate_random_9);

  tcase_add_test(tc_core, calculate_credit_1);
  tcase_add_test(tc_core, calculate_credit_2);
  tcase_add_test(tc_core, calculate_deposit_1);
  tcase_add_test(tc_core, calculate_deposit_2);
  tcase_add_test(tc_core, calculate_deposit_3);
  tcase_add_test(tc_core, calculate_deposit_4);
  tcase_add_test(tc_core, calculate_deposit_5);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}
