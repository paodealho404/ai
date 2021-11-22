typedef struct QUEUE pqueue;
typedef struct STATE state;
typedef struct GRAPH graph;
typedef struct VERTEX vertex;
pqueue* create_queue();
state* create_state(graph *paris, state *source_station, int adjacent_station, char line);
int is_empty(pqueue *pqueue);
void enqueue(graph *paris, pqueue *pqueue, state *new_state, int destination);
void print_queue(pqueue *pq);
state* peak(pqueue *pq);
state* get_next(state* s);
state* dequeue(pqueue *pq);
int get_station_number(state *state);
void generate_new_states(graph *paris, pqueue* pq, state *predecessor, int destination);
float get_g_cost(state *st);
int is_final(state *terminal, int destination);
void print_path(state *final);

