#include <math.h>
#include <stdlib.h>

#include "s21_calculator.h"
#include "s21_list.h"
#include "s21_stack.h"

#define BUF_SIZE 512

#define F_CORRECT 1
#define F_PREV_N_DIG 2

typedef struct parse_err_s {
  char err_flags;
  int brackets_count;
} parse_err_t;

int parse_str_to_tokens(const char* str, s21_list_t** result);  // err 1

int check_tokens_list(s21_list_t* tokens);  // err = 2

void inf_to_rev(const s21_list_t* inf_tokens, s21_list_t** rev_tokens);

double calc(const s21_list_t* rev_tokens, const double x);

int infix_notation(const char* inf, const double x, double* result) {
  int err = 0;
  s21_list_t* inf_tokens = NULL;
  s21_list_t* rev_tokens = NULL;
  err = parse_str_to_tokens(inf, &inf_tokens);
  if (!err) {
    err = check_tokens_list(inf_tokens);
    if (!err) {
      inf_to_rev(inf_tokens, &rev_tokens);
      *result = calc(rev_tokens, x);
    }
  }
  l_clear(&inf_tokens);
  l_clear(&rev_tokens);
  return err;
}

int graphic(const char* inf, double x_l, double x_r, point_t result[]) {
  int err = 0;
  s21_list_t* inf_tokens = NULL;
  s21_list_t* rev_tokens = NULL;
  err = parse_str_to_tokens(inf, &inf_tokens);
  if (!err) {
    err = check_tokens_list(inf_tokens);
    if (!err) {
      inf_to_rev(inf_tokens, &rev_tokens);
      double step = fabs(x_r - x_l) / POINTS_SIZE;
      for (int i = 0; i < POINTS_SIZE; ++i) {
        result[i].x = x_l;
        result[i].y = calc(rev_tokens, x_l);
        x_l += step;
      }
    }
  }
  l_clear(&inf_tokens);
  l_clear(&rev_tokens);
  return err;
}

//++PARSE
int parse_num(const char** str, s21_list_t** result) {
  int find = 1;
  if (**str >= '0' && **str <= '9') {
    double num = 0.;
    while (**str >= '0' && **str <= '9') {
      num = num * 10. + (**str - '0');
      ++(*str);
    }
    if (**str == '.') {
      ++(*str);
      double pow = 10.;
      while (**str >= '0' && **str <= '9') {
        num += (**str - '0') / pow;
        pow *= 10.;
        ++(*str);
      }
    }
    l_push_back_val(result, num);
  } else {
    find = 0;
  }
  return find;
}

int parse_num_brackets(const char** str, s21_list_t** result) {
  int find = 1;
  switch (**str) {
    case 'x':
      l_push_back_sym(result, 'x');
      ++(*str);
      break;
    case '(':
      l_push_back_sym(result, '(');
      ++(*str);
      break;
    case ')':
      l_push_back_sym(result, ')');
      ++(*str);
      break;
    default:
      find = parse_num(str, result);
      break;
  }
  return find;
}

int parse_tan_cos_mod(const char** str, s21_list_t** result,
                      parse_err_t* errors) {
  int find = 1;
  switch (**str) {
    case 't':
      if (*(*str + 1) == 'a' && *(*str + 2) == 'n' && *(*str + 3) == '(') {
        l_push_back_sym(result, 't');
        (*str) += 3;
      } else {
        errors->err_flags &= ~F_CORRECT;
      }
      break;
    case 'c':
      if (*(*str + 1) == 'o' && *(*str + 2) == 's' && *(*str + 3) == '(') {
        l_push_back_sym(result, 'c');
        (*str) += 3;
      } else {
        errors->err_flags &= ~F_CORRECT;
      }
      break;
    case 'm':
      if (*(*str + 1) == 'o' && *(*str + 2) == 'd') {
        l_push_back_sym(result, 'm');
        (*str) += 3;
      } else {
        errors->err_flags &= ~F_CORRECT;
      }
      break;
    default:
      find = 0;
      break;
  }
  return find;
}

int parse_sin_sqrt(const char** str, s21_list_t** result, parse_err_t* errors) {
  int find = 0;
  if (**str == 's') {
    find = 1;
    if (*(*str + 1) == 'i' && *(*str + 2) == 'n' && *(*str + 3) == '(') {
      l_push_back_sym(result, 's');
      (*str) += 3;
    } else if (*(*str + 1) == 'q' && *(*str + 2) == 'r' && *(*str + 3) == 't' &&
               *(*str + 4) == '(') {
      l_push_back_sym(result, 'q');
      (*str) += 4;
    } else {
      errors->err_flags &= ~F_CORRECT;
    }
  }
  return find;
}

int parse_ln_log(const char** str, s21_list_t** result, parse_err_t* errors) {
  int find = 0;
  if (**str == 'l') {
    find = 1;
    if (*(*str + 1) == 'o' && *(*str + 2) == 'g' && *(*str + 3) == '(') {
      l_push_back_sym(result, 'L');
      (*str) += 3;
    } else if (*(*str + 1) == 'n' && *(*str + 2) == '(') {
      l_push_back_sym(result, 'l');
      (*str) += 2;
    } else {
      errors->err_flags &= ~F_CORRECT;
    }
  }
  return find;
}

int parse_acos_asin_atan(const char** str, s21_list_t** result,
                         parse_err_t* errors) {
  int find = 0;
  if (**str == 'a') {
    find = 1;
    ++(*str);
    switch (**str) {
      case 'c':
        if (*(*str + 1) == 'o' && *(*str + 2) == 's' && *(*str + 3) == '(') {
          l_push_back_sym(result, 'C');
          (*str) += 3;
        } else {
          errors->err_flags &= ~F_CORRECT;
        }
        break;
      case 's':
        if (*(*str + 1) == 'i' && *(*str + 2) == 'n' && *(*str + 3) == '(') {
          l_push_back_sym(result, 'S');
          (*str) += 3;
        } else {
          errors->err_flags &= ~F_CORRECT;
        }
        break;
      case 't':
        if (*(*str + 1) == 'a' && *(*str + 2) == 'n' && *(*str + 3) == '(') {
          l_push_back_sym(result, 'T');
          (*str) += 3;
        } else {
          errors->err_flags &= ~F_CORRECT;
        }
        break;
      default:
        errors->err_flags &= ~F_CORRECT;
        break;
    }
  }
  return find;
}

int parse_operators(const char** str, s21_list_t** result) {
  int find = 1;
  switch (**str) {
    case '+':
      l_push_back_sym(result, *((*str)++));
      break;
    case '-':
      l_push_back_sym(result, *((*str)++));
      break;
    case '*':
      l_push_back_sym(result, *((*str)++));
      break;
    case '/':
      l_push_back_sym(result, *((*str)++));
      break;
    case '^':
      l_push_back_sym(result, *((*str)++));
      break;
    default:
      find = 0;
      break;
  }
  return find;
}

int parse_str_to_tokens(const char* str, s21_list_t** result) {
  int err = 0;
  parse_err_t errors = {0};
  errors.err_flags |= F_CORRECT;
  errors.err_flags |= F_PREV_N_DIG;
  while (*str && (errors.err_flags & F_CORRECT)) {
    while (*str == ' ') {
      ++str;
    }
    if (!(parse_operators(&str, result) || parse_num_brackets(&str, result) ||
          parse_tan_cos_mod(&str, result, &errors) ||
          parse_sin_sqrt(&str, result, &errors) ||
          parse_ln_log(&str, result, &errors) ||
          parse_acos_asin_atan(&str, result, &errors))) {
      errors.err_flags &= ~F_CORRECT;
    }
  }
  if (!(errors.err_flags & F_CORRECT) || errors.brackets_count) {
    l_clear(result);
    err = 1;
  }
  return err;
}
//--PARSE
//++CHECK
int check_bracket(s21_list_t* tokens) {
  int err = 0;
  int bucket_count = 0;
  while (tokens) {
    if (!l_get_type(tokens) && tokens->sym == '(') {
      ++bucket_count;
    } else if (!l_get_type(tokens) && tokens->sym == ')') {
      --bucket_count;
    }
    if (bucket_count < 0) {
      err = 1;
      break;
    }
    tokens = tokens->next;
  }
  if (bucket_count) {
    err = 1;
  }
  return err;
}

int is_sign_p_m(const char c) { return c == '+' || c == '-'; }

int is_not_first_sign(const char c) {
  return c == '*' || c == '/' || c == '^' || c == ')';
}

int is_next_unary_sign(const char c) {
  return c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||
         c == 'm';
}

int check_prev_unary_sign(const char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm' ||
         c == ')';
}

int check_prev_m_sym(const char c) {
  return c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int is_sign(const char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int is_func(const char c) {
  return c == 'c' || c == 's' || c == 't' || c == 'C' || c == 'S' || c == 'T' ||
         c == 'q' || c == 'l' || c == 'L';
}

int check_sign_rules(s21_list_t* tokens) {
  int err = 0;
  if (!l_get_type(tokens) && is_sign_p_m(tokens->sym)) {
    tokens->sym = tokens->sym == '+' ? 'P' : 'M';
    tokens = tokens->next;
  } else if (!l_get_type(tokens) && is_not_first_sign(tokens->sym)) {
    err = 1;
  }
  int prev_sign_left_bracket = 0;
  while (tokens && !err) {
    if (prev_sign_left_bracket) {
      if (!l_get_type(tokens) && is_sign_p_m(tokens->sym)) {
        tokens->sym = tokens->sym == '+' ? 'P' : 'M';
      } else if (!l_get_type(tokens) && is_not_first_sign(tokens->sym)) {
        err = 1;
      }
      prev_sign_left_bracket = 0;
    }
    if (!l_get_type(tokens) && is_next_unary_sign(tokens->sym)) {
      prev_sign_left_bracket = 1;
    }
    tokens = tokens->next;
  }
  if (prev_sign_left_bracket) {
    err = 1;
  }
  return err;
}

int check_unary_signs(s21_list_t* tokens) {
  int err = 0;
  int prev_unary = 0;
  while (tokens) {
    if (prev_unary && !l_get_type(tokens) &&
        check_prev_unary_sign(tokens->sym)) {
      err = 1;
      break;
    } else {
      prev_unary = 0;
    }
    if (!l_get_type(tokens) && (tokens->sym == 'P' || tokens->sym == 'M')) {
      prev_unary = 1;
    }
    tokens = tokens->next;
  }
  if (prev_unary) {
    err = 1;
  }
  return err;
}

int check_mod(s21_list_t* tokens) {
  int err = 0;
  int prev_sign_in_bracket = 0;
  int prev_m = 1;
  while (tokens && !err) {
    if (prev_m && !l_get_type(tokens) && check_prev_unary_sign(tokens->sym)) {
      err = 1;
      break;
    } else {
      prev_m = 0;
    }
    if (!l_get_type(tokens) && tokens->sym == 'm') {
      if (prev_sign_in_bracket) {
        err = 1;
        break;
      } else {
        prev_m = 1;
      }
    }
    prev_sign_in_bracket = 0;
    if (!l_get_type(tokens) && check_prev_m_sym(tokens->sym)) {
      prev_sign_in_bracket = 1;
    }
    tokens = tokens->next;
  }
  if (prev_m) {
    err = 1;
  }
  return err;
}

void add_implicit_multiplication(s21_list_t* tokens) {
  s21_list_t* prev_token = tokens;
  if (tokens) {
    tokens = tokens->next;
    while (tokens) {
      if (l_get_type(tokens) || tokens->sym == 'x' || tokens->sym == '(' ||
          is_func(tokens->sym)) {
        if (l_get_type(prev_token) || prev_token->sym == 'x' ||
            prev_token->sym == ')') {
          s21_list_t* temp = (s21_list_t*)malloc(sizeof(s21_list_t));
          temp->type = 0;
          temp->next = tokens;
          temp->sym = '*';
          prev_token->next = temp;
        }
      }
      prev_token = tokens;
      tokens = tokens->next;
    }
  }
}

int check_tokens_list(s21_list_t* tokens) {
  int err = 0;
  if (tokens && (check_bracket(tokens) || check_sign_rules(tokens) ||
                 check_unary_signs(tokens) || check_mod(tokens))) {
    err = 2;
  }
  if (!err) {
    add_implicit_multiplication(tokens);
  }
  return err;
}
//--CHECK
//++INF_TO_REV
void rev_left_backet(s21_stack_t** st, s21_list_t** rev_tokens) {
  while ((*st)->sym != '(') {
    l_push_back_sym(rev_tokens, s_top_sym(*st));
    s_pop(st);
  }
  s_pop(st);
  if (*st && is_func(s_top_sym(*st))) {
    l_push_back_sym(rev_tokens, s_top_sym(*st));
    s_pop(st);
  }
}

void rev_signs(const s21_list_t* inf_tokens, s21_stack_t** st,
               s21_list_t** rev_tokens) {
  if (inf_tokens->sym == 'P' || inf_tokens->sym == 'M') {
    while (*st && ((*st)->sym == 'P' || (*st)->sym == 'M')) {
      l_push_back_sym(rev_tokens, s_top_sym(*st));
      s_pop(st);
    }
    s_push_sym(st, inf_tokens->sym);
  } else if (inf_tokens->sym == '^') {
    while (*st &&
           ((*st)->sym == 'P' || (*st)->sym == 'M' || (*st)->sym == '^')) {
      l_push_back_sym(rev_tokens, s_top_sym(*st));
      s_pop(st);
    }
    s_push_sym(st, inf_tokens->sym);
  } else if (inf_tokens->sym == '*' || inf_tokens->sym == '/' ||
             inf_tokens->sym == 'm') {
    while (*st &&
           ((*st)->sym == 'P' || (*st)->sym == 'M' || (*st)->sym == '^' ||
            (*st)->sym == '*' || (*st)->sym == '/' || (*st)->sym == 'm')) {
      l_push_back_sym(rev_tokens, s_top_sym(*st));
      s_pop(st);
    }
    s_push_sym(st, inf_tokens->sym);
  } else {
    while (*st &&
           ((*st)->sym == 'P' || (*st)->sym == 'M' || (*st)->sym == '^' ||
            (*st)->sym == 'm' || is_sign((*st)->sym))) {
      l_push_back_sym(rev_tokens, s_top_sym(*st));
      s_pop(st);
    }
    s_push_sym(st, inf_tokens->sym);
  }
}

void inf_to_rev(const s21_list_t* inf_tokens, s21_list_t** rev_tokens) {
  s21_stack_t* st = NULL;
  while (inf_tokens) {
    if (l_get_type(inf_tokens)) {
      l_push_back_val(rev_tokens, l_front_val(inf_tokens));
    } else {
      if (inf_tokens->sym == 'x') {
        l_push_back_sym(rev_tokens, l_front_sym(inf_tokens));
      } else if (inf_tokens->sym == '(' || is_func(inf_tokens->sym)) {
        s_push_sym(&st, inf_tokens->sym);
      } else if (inf_tokens->sym == ')') {
        rev_left_backet(&st, rev_tokens);
      } else {
        rev_signs(inf_tokens, &st, rev_tokens);
      }
    }
    inf_tokens = inf_tokens->next;
  }
  while (st) {
    l_push_back_sym(rev_tokens, s_top_sym(st));
    s_pop(&st);
  }
}
//--INF_TO_REV
//++CALC
void calc_unary(const char c, s21_stack_t** st) {
  double val;
  val = s_top_val(*st);
  s_pop(st);
  switch (c) {
    case 'P':
      s_push_val(st, val);
      break;
    case 'M':
      s_push_val(st, -val);
      break;
    case 'c':
      s_push_val(st, cos(val));
      break;
    case 's':
      s_push_val(st, sin(val));
      break;
    case 't':
      s_push_val(st, tan(val));
      break;
    case 'C':
      s_push_val(st, acos(val));
      break;
    case 'S':
      s_push_val(st, asin(val));
      break;
    case 'T':
      s_push_val(st, atan(val));
      break;
    case 'q':
      s_push_val(st, sqrt(val));
      break;
    case 'l':
      s_push_val(st, log(val));
      break;
    case 'L':
      s_push_val(st, log10(val));
      break;
  }
}

void calc_binary(const char c, s21_stack_t** st) {
  double val2 = s_top_val(*st);
  s_pop(st);
  double val1 = s_top_val(*st);
  s_pop(st);
  switch (c) {
    case 'm':
      s_push_val(st, fmod(val1, val2));
      break;
    case '+':
      s_push_val(st, val1 + val2);
      break;
    case '-':
      s_push_val(st, val1 - val2);
      break;
    case '*':
      s_push_val(st, val1 * val2);
      break;
    case '/':
      s_push_val(st, val1 / val2);
      break;
    case '^':
      s_push_val(st, pow(val1, val2));
      break;
  }
}

double calc(const s21_list_t* rev_tokens, const double x) {
  double result = 0.;
  s21_stack_t* st = NULL;
  while (rev_tokens) {
    if (l_get_type(rev_tokens)) {
      s_push_val(&st, rev_tokens->val);
    } else {
      switch (rev_tokens->sym) {
        case 'x':
          s_push_val(&st, x);
          break;
        case 'P':
        case 'M':
        case 'c':
        case 's':
        case 't':
        case 'C':
        case 'S':
        case 'T':
        case 'q':
        case 'l':
        case 'L':
          calc_unary(rev_tokens->sym, &st);
          break;
        case 'm':
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          calc_binary(rev_tokens->sym, &st);
          break;
      }
    }
    rev_tokens = rev_tokens->next;
  }
  result = s_top_val(st);
  s_clear(&st);
  return result;
}
//--CALC
