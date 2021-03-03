
typedef struct __node {
  int value;
  struct __node *next;
} node_t;

typedef struct __snode {
  node_t *value;
  struct __snode *next;
} snode_t;

static void stack_push(snode_t **top, node_t *list);

static node_t *stack_pop(snode_t **top);

static inline void list_add_node_t(node_t **list, node_t *node_t); 

static inline void list_concat(node_t **left, node_t *right);

void optquicksort(node_t **list);

void quicksort(node_t **list);

static bool list_is_ordered(node_t *list); 

static void list_display(node_t *list);

static node_t *list_make_node_t(node_t *list, int val); 

static void list_free(node_t **p);
