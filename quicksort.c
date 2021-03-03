#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quicksort.h"


static void stack_push(snode_t **top, node_t *list) {
  snode_t *new = malloc(sizeof(snode_t));
  if (!new)
    return;
  new->value = list;
  new->next = *top;
  *top = new;
}

static node_t *stack_pop(snode_t **top) {
  snode_t *curr = *top;
  if (curr) {
    node_t *list = curr->value;
    *top = curr->next;
    free(curr);
    return list;
  }
  return NULL;
}

static inline void list_add_node_t(node_t **list, node_t *node_t) {
  node_t->next = *list;
  *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
  while (*left)
    left = &((*left)->next);
  *left = right;
}

/*
 * optimized quicksort
 * */

void optquicksort(node_t **list) {
  snode_t *stack = NULL;
  node_t *result = NULL;
  stack_push(&stack, *list);
  while (stack) {
    node_t *pivot = stack_pop(&stack);
    int value = pivot->value;
    node_t *p = pivot->next;
    if (!p) {
      list_add_node_t(&result, pivot);
    } else {

      pivot->next = NULL;
      node_t *left = NULL, *right = NULL;
      while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
      }
      if(left) stack_push(&stack, left);
      stack_push(&stack, pivot);
      if(right) stack_push(&stack, right);
    }
  }
  *list = result;
}

void quicksort(node_t **list) {
  if (!*list)
    return;

  node_t *pivot = *list;
  int value = pivot->value;
  node_t *p = pivot->next;
  pivot->next = NULL;

  node_t *left = NULL, *right = NULL;
  while (p) {
    node_t *n = p;
    p = p->next;
    list_add_node_t(n->value > value ? &right : &left, n);
  }

  quicksort(&left);
  quicksort(&right);

  node_t *result = NULL;
  list_concat(&result, left);
  list_concat(&result, pivot);
  list_concat(&result, right);
  *list = result;
}

static bool list_is_ordered(node_t *list) {
  bool first = true;
  int value;
  while (list) {
    if (first) {
      value = list->value;
      first = false;
    } else {
      if (list->value < value)
        return false;
      value = list->value;
    }
    list = list->next;
  }
  return true;
}

static void list_display(node_t *list) {
  printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
  while (list) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("\n");
}

static node_t *list_make_node_t(node_t *list, int val) {
  node_t *new = malloc(sizeof(node_t));
  if (!new)
    return list;
  new->value = val;
  new->next = list;
  return new;
}

static void list_free(node_t **p) {
  while (*p) {
    node_t *curr = *p;
    *p = curr->next;
    free(curr);
  }
}

int main(int argc, char **argv) {
  size_t count = 20;
  srand(time(NULL));
  node_t *list = NULL;
  while (count--)
    list = list_make_node_t(list, random() % 1024);

  list_display(list);
  optquicksort(&list);
  list_display(list);

  if (!list_is_ordered(list))
    return EXIT_FAILURE;

  list_free(&list);
  return EXIT_SUCCESS;
}
