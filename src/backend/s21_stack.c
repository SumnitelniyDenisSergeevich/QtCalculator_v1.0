#include "s21_stack.h"

#include <stdlib.h>

char s_top_sym(const s21_stack_t* stack) { return stack->sym; }

double s_top_val(const s21_stack_t* stack) { return stack->val; }

void s_push_sym(s21_stack_t** stack, const char sym) {
  s21_stack_t* new_node = (s21_stack_t*)malloc(sizeof(s21_stack_t));
  new_node->sym = sym;
  new_node->prev = *stack;
  *stack = new_node;
}

void s_push_val(s21_stack_t** stack, const double val) {
  s21_stack_t* new_node = (s21_stack_t*)malloc(sizeof(s21_stack_t));
  new_node->val = val;
  new_node->prev = *stack;
  *stack = new_node;
}

void s_pop(s21_stack_t** stack) {
  s21_stack_t* temp = *stack;
  *stack = (*stack)->prev;
  free(temp);
  temp = NULL;
}

void s_clear(s21_stack_t** stack) {
  while (*stack) {
    s21_stack_t* temp = *stack;
    *stack = (*stack)->prev;
    free(temp);
    temp = NULL;
  }
}