#include "queue.h"
#include <stdio.h>

int main(){
    queue *fronteira = createQueue();

    state *ori = createState('O',3,3,0,0,0);
    
    enqueue_normal(fronteira, ori, NULL);
    state *aux = dequeue(fronteira);
    while(!is_final(aux)){
        generate_new_states(fronteira,aux);
        aux = dequeue(fronteira);
    }
    generate_path(aux);
}