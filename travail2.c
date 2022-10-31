# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>


struct circular{
    signed int value;
    struct circular *next;
};

struct circular* mkcircular(){
    struct circular *tmp = malloc(sizeof(struct circular));
    tmp->next = 0;
    return tmp;
};

struct circular* insert(struct circular *cycle, signed int elt){
    if (cycle->next == 0){
        cycle->value = elt;
        cycle->next =  cycle;
    
    } else {
        struct circular *new_ele = malloc(sizeof(struct circular));
        new_ele->value = elt;
        new_ele->next = cycle->next;
        cycle->next = new_ele;
        cycle = new_ele;
    }
    return cycle;
}

signed int extract(struct circular *cycle){
    struct circular *tmp = cycle->next;
    signed int value;
    if (tmp->next == 0){
        printf("You can't extract any element, the list is empty !!");
    } else if (tmp->next = tmp){
        value = tmp->value;
        cycle->next = 0;
        free(tmp);
    } else {
        value = tmp->value;
        cycle->next = tmp->next;
        printf("%p\n", cycle->next);
        free(tmp);
    }
    return value;

    
}

void affichage(struct circular *cycle){
    struct circular *tmp = cycle->next;
    do {
        printf("%d  ", tmp->value);
        tmp = tmp->next;
    } while(tmp != cycle->next);
    printf("\n");
}

struct circular* rotateToEven(struct circular *cycle){
    struct circular *tmp = cycle;
    while(tmp->next != cycle)
    {
        if (tmp->next->value % 2 == 0){
            cycle = tmp;
            return cycle;
        }
        tmp = tmp->next;
    }
}

struct circular* rotateToOdd(struct circular *cycle){
    struct circular *tmp = cycle;
    while(tmp->next != cycle)
    {
        if (tmp->next->value % 2 != 0){
            cycle = tmp;
            return cycle;
        }
        tmp = tmp->next;
    }
}

int main(int argc , char * argv []) {
    struct circular *my_cycle = mkcircular(); 
    my_cycle = insert(my_cycle, 1); 
    my_cycle = insert(my_cycle, 3); 
    my_cycle = insert(my_cycle, 2);
    my_cycle = insert(my_cycle, 1);
    my_cycle = insert(my_cycle, 4);
    my_cycle = insert(my_cycle, 5);
    affichage(my_cycle);

    my_cycle = rotateToEven(my_cycle);
    affichage(my_cycle);

    my_cycle = rotateToOdd(my_cycle);
    affichage(my_cycle);

    return EXIT_SUCCESS;
}




