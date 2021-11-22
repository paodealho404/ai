typedef struct GRAPH graph;
typedef struct VERTEX vertex;
typedef struct QUEUE pqueue;
typedef struct STATE state;
void add_undirected_edge(graph *graph, char line, int source, int destination, float time);
vertex* create_vertex(int station, char line);
graph* create_graph();
void print_distances_between_cities(graph *paris);
void print_lines_between_cities(graph *paris);
float calculate_cost_to_station(graph *paris, int s, int d);
float calculate_heuristics(graph *paris, int s, int d);
vertex* get_vertex(graph *paris, int i);
vertex* get_sucessor_vertex(graph *paris, int i);
int get_station(vertex *v);
void iterate_and_enqueue(graph *paris, pqueue *pq, state *source, int destination);
char get_line(graph *paris, int prev_station, int next_station);

