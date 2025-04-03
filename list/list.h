typedef struct node node;
struct node {
  int element;
  node *link;
};
typedef struct {
  node *head;
} list;
list *create_new_list();
int count(list *list);
void app_to_top(list *list, int new_element);
void app_to_end(list *list, int new_element);
int app(list *list, int new_element, int number);
int remove_node(list *list, int number);
int find_element(list *list, int number, int *exit_status);
void delete_list(list *list);
