typedef struct node {
  int element;
  struct node *link;
} node;
typedef struct {
  node *head;
} list;
list *create_new_list();
int count(list *list);
void app_to_top(list *list, int new_element);
void app_to_end(list *list, int new_element);
void app(list *list, int new_element, int number, int *completion);
void remove_node(list *list, int number, int *completion);
int find_element(list *list, int number, int *completion);
void delete_list(list *list);
