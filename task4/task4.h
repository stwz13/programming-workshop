struct List *create_new_list();
void app_to_top(struct List *list, int new_element);
void app_to_end(struct List *list, int new_element);
int count(struct List *list);
void app(struct List *list, int new_element, int number);
void remove_node(struct List *list, int number);
int find_element(struct List *list, int number);
void delete_list(struct List *list);
