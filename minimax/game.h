typedef struct STACK stack;
typedef struct STATE state;

void print_state(state *s);
int is_final(state *s);
state* pop(stack *s);
void push(stack *s, state *push_element);
state* create_state(state* prev);
int is_empty(stack *s);
stack* create_stack();
void change_game(state *s, char c, int i, int j);
void generate_next_state(stack *st, state *prev, char c);
void print_stack(stack *s);
void create_game(char player);