#ifndef S21_CALCULATOR  // S21_CALCULATOR
#define S21_CALCULATOR  // S21_CALCULATOR

#define POINTS_SIZE 1000

typedef struct point_s {
  double x;
  double y;
} point_t;

typedef struct credit_calc_input_s {
  double total_amount;
  int term;
  double interest_rate;
  int type;
} credit_calc_input_t;

typedef struct credit_calc_output_s {
  double* monthly_payment;
  double overpayment;
  double total_paymen;
} credit_calc_output_t;

typedef struct deposit_list_s {
  int period;
  double sum;
} deposit_list_t;

typedef struct deposit_calc_input_s {
  double deposit_amount;
  int term;
  double interest_rate;
  double tax_rate;
  int periodicity_of_payments;
  int capitalization_of_interest;
  deposit_list_t* replenishments_list;
  int rep_list_size;
  deposit_list_t* partial_withdrawals_list;
  int par_list_size;
} deposit_calc_input_t;

typedef struct deposit_calc_output_s {
  double accrued_interest;
  double tax_amount;
  double deposit_amount_end;
} deposit_calc_output_t;

void credit_calculator(const credit_calc_input_t* input,
                       credit_calc_output_t* output);

deposit_calc_output_t deposit_calculator(const deposit_calc_input_t* input);

int infix_notation(const char* inf, const double x, double* result);

int graphic(const char* inf, const double x_l, const double x_r,
            point_t result[]);

#endif  // S21_CALCULATOR
