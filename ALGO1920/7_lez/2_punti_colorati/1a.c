#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
    int rgb;
} Point;

int color_cmp(const void *a, const void *b);

void mem_err();

int main(){
    /*LEGGI N & M*/
    int N, M;

    scanf("%d%*[ ]%d", &N, &M);

    
    /*ACQUISISCI N PUNTI COLORATI*/
    Point* arr_of_points = calloc(N, sizeof(Point));
    if(arr_of_points == NULL)
        mem_err();

    int i;
    for(i = 0; i < N; i++){
        scanf("%d%*[ ]%d%*[ ]%d", &arr_of_points[i].x, &arr_of_points[i].y, &arr_of_points[i].rgb);
        scanf("%*[^\n]");
        scanf("%*c");
    }


    /*ORDINA PER COLORE*/
    qsort(arr_of_points, N, sizeof(Point), color_cmp);

    /*LEGGI M INTERROGAZIONI*/
    int x1, x2, y1, y2;
    int prec_color; 
    int result;
    int j;

    for(i = 0; i < M; i++){
            
            prec_color = -1; 
            result = 0;
            
        
            scanf("%d%*[ ]%d%*[ ]%d%*[ ]%d", &x1, &y1, &x2, &y2);
            scanf("%*c");
            

            /*PER OGNI INTERROGAZIONE*/
            /*SCORRI TUTTI I PUNTI*/
            /*SE IL PUNTO E' NEL RETTANGOLO, GUARDA IL COLORE, SE L'HO GIA' ESAMINATO NON INCREMENTARE result, ALTRIMENTI INCREMENTA  result*/
            
            for(j = 0; j < N; j++){
                if( (arr_of_points[j].x >= x1 && arr_of_points[j].x <= x2) && (arr_of_points[j].y >= y1 && arr_of_points[j].y <= y2)){
                    if(arr_of_points[j].rgb != prec_color){
                        result++;
                        prec_color = arr_of_points[j].rgb;
                    }
                }
            }

            printf("%d\n", result);

    }    
    /*FREE DELLA MEMORIA ALLOCATA*/
    free(arr_of_points);
    arr_of_points = NULL;
}


int color_cmp(const void *a, const void *b){
    
    Point** first =  (Point**)(&a);
    Point** second = (Point**)(&b);

    return (*first)->rgb - (*second)->rgb;
}

void mem_err(){
    
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}