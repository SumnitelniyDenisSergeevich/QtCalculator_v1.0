#ifndef S21_LIST  // S21_LIST
#define S21_LIST  // S21_LIST

typedef struct s21_list_s {
  struct s21_list_s* next;
  char sym;
  double val;
  int type;
} s21_list_t;

int l_get_type(const s21_list_t* list);

double l_front_val(const s21_list_t* list);

char l_front_sym(const s21_list_t* list);

void l_push_back_val(s21_list_t** list, const double val);

void l_push_back_sym(s21_list_t** list, const char sym);

void l_clear(s21_list_t** list);

#endif  // S21_LIST
