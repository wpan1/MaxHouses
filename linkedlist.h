typedef struct node {
    Set *set;
    node_t next;
} node_t;

node_t LLCreate();

node_t LLpush(node_t *head, Set *set);