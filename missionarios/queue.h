typedef struct NODE state;
typedef struct QUEUE queue;
queue* createQueue();
state* createState(char state_n, short mis1, short can1, short mis2, short can2, short ilha);
short is_final(state *st);
void enqueue_normal(queue *normal_queue, state *new_state, state *predecessor);
state* dequeue(queue *queue);
void generate_new_states(queue *fronteira, state *atual);
void generate_path(state *s);