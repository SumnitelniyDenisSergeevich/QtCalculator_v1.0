#include "s21_list.h"

#include <stdlib.h>

int l_get_type(const s21_list_t* list) { return list->type; }

double l_front_val(const s21_list_t* list) { return list->val; }

char l_front_sym(const s21_list_t* list) { return list->sym; }

void l_push_back_val(s21_list_t** list, const double val) {
  s21_list_t* new_node = (s21_list_t*)malloc(sizeof(s21_list_t));
  new_node->next = NULL;
  new_node->val = val;
  new_node->type = 1;
  if (!(*list)) {
    (*list) = new_node;
  } else {
    s21_list_t* temp = (*list);
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_node;
    temp = NULL;
  }
  new_node = NULL;
}

void l_push_back_sym(s21_list_t** list, const char sym) {
  s21_list_t* new_node = (s21_list_t*)malloc(sizeof(s21_list_t));
  new_node->next = NULL;
  new_node->sym = sym;
  new_node->type = 0;
  if (!(*list)) {
    (*list) = new_node;
  } else {
    s21_list_t* temp = (*list);
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_node;
    temp = NULL;
  }
  new_node = NULL;
}

void l_clear(s21_list_t** list) {
  if (*list) {
    l_clear(&(*list)->next);
    free(*list);
  }
  *list = NULL;
}