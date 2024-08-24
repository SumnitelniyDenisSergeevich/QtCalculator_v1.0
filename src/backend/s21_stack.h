#ifndef S21_STACK  // S21_STACK
#define S21_STACK  // S21_STACK

typedef struct s21_stack_s {
  struct s21_stack_s* prev;
  char sym;
  double val;
} s21_stack_t;

char s_top_sym(const s21_stack_t* stack);
double s_top_val(const s21_stack_t* stack);

void s_push_sym(s21_stack_t** stack, const char sym);
void s_push_val(s21_stack_t** stack, const double val);

void s_pop(s21_stack_t** stack);

void s_clear(s21_stack_t** stack);
#endif  // S21_STACK