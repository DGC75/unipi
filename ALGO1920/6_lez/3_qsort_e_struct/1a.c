#include <stdio.h>
#include <stdlib.h>

#define IN_STREAM stdin

typedef struct{
    int x;
    int y;   
} Point;

int     get_int         (FILE *fPtr);
Point  *get_point_arr   (FILE *fptr, int size);
Point   get_point       (FILE *fPtr);

int     point_cmp       (const void *pt1, const void *pt2);
void    print_point_arr (Point *arr, int size);

void    mem_err         ();

int main(){

    int size = get_int(IN_STREAM);
    Point* point_arr = get_point_arr(IN_STREAM, size);
    qsort(point_arr, size, sizeof(Point), point_cmp);
    print_point_arr(point_arr, size);

}

int get_int (FILE *fPtr){
    
    int tmp;
    fscanf(fPtr,"%d", &tmp);
    /*CLEAN BUFFER*/
    fscanf(fPtr,"%*c");

    return tmp;
}
Point *get_point_arr (FILE *fPtr, int size){
    
    Point *tmp_arr = calloc(size, sizeof(Point));
    if(tmp_arr == NULL)
        mem_err();
    
    int i;
    for(i = 0; i < size; i++)
        tmp_arr[i] = get_point(fPtr);

    return tmp_arr;
}
Point get_point (FILE *fPtr){
    
    Point tmp_point;
    fscanf(fPtr, "%d %d", &tmp_point.x, &tmp_point.y);
    /*CLEAN BUFFER*/
    fscanf(fPtr, "%*c");

    return tmp_point;
}

int point_cmp (const void *pt1, const void *pt2){

    Point *p1 = (Point *) pt1;
    Point *p2 = (Point *) pt2;

    if(p2->x - p1->x > 0)
        return -1;
    else if(p2->x - p1->x == 0){

        if(p2->y - p1->y > 0)
            return 1;
        else if(p2->y - p1->y == 0)
            return 0;
        
        return -1;
    }    
    
    return 1;
}
void print_point_arr (Point *arr, int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%d %d\n", arr[i].x, arr[i].y);
}

void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}