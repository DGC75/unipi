#include <stdio.h>
#include <stdlib.h>

typedef enum bool{
	FALSE = 0,
	TRUE  = 1
}Bool;


void salva_intero(int *p);
void input_non_corretto(void);
void salva_array(int array[], int dim);
void alloca_e_salva_voti_partecipanti(int *array[], int dim, int dim_arr_allocati);
void conta_elementi_distinti_array(int array[], int dim, int *elementi_distinti);
void stampa_vincitori_categorie(int nomi_categorie[], int numero_prove, int **voti_prove_partecipanti, int numero_partecipanti);
void stampa_vincitore_globale(int **voti_prove_partecipanti, int numero_partecipanti, int numero_prove);
void dealloca_voti_partecipanti(int *voti_prove_partecipanti[], int numero_partecipanti);
void init_array_to_0(float array[], int dim);		
int max_array(float array[], int dim);


int main (void){

	/*ACQUISIZIONE INPUT*/
	int numero_prove = 0, numero_partecipanti = 0;
	salva_intero(&numero_prove);

	int nomi_categorie[numero_prove];
	salva_array(nomi_categorie, numero_prove);

	salva_intero(&numero_partecipanti);

	int* voti_prove_partecipanti[numero_partecipanti];
	alloca_e_salva_voti_partecipanti(voti_prove_partecipanti, numero_partecipanti, numero_prove); 
	/*FINE ACQUISIZIONE INPUT*/

	/*CALCOLO E STAMPA OUTPUT*/
	stampa_vincitori_categorie(nomi_categorie, numero_prove, voti_prove_partecipanti, numero_partecipanti);
	stampa_vincitore_globale(voti_prove_partecipanti, numero_partecipanti, numero_prove);

	dealloca_voti_partecipanti(voti_prove_partecipanti, numero_partecipanti);
}


void stampa_vincitori_categorie(int nomi_categorie[], int numero_prove, int** voti_prove_partecipanti, int numero_partecipanti){

	int numero_prove_distinte, i,j,k,h;

	conta_elementi_distinti_array(nomi_categorie, numero_prove, &numero_prove_distinte);

	for (i = 0; i < numero_prove; ++i){
		static Bool is_there = FALSE;

		for(j=0; j < i; j++){
			if (nomi_categorie[i] == nomi_categorie[j]){
				is_there = TRUE;
			}
		}
		if (is_there == FALSE){

			float voto_candidato_per_categoria[numero_prove_distinte];
			init_array_to_0(voto_candidato_per_categoria, numero_prove_distinte);

			for (k = 0; k < numero_partecipanti; ++k){

				int* voti_candidato = voti_prove_partecipanti[k];
				int count_divisore = 0;

				for (h = 0; h < numero_prove; ++h){
					if (nomi_categorie[h] == nomi_categorie[i] ){
						voto_candidato_per_categoria[k] += voti_candidato[h];
						count_divisore++;
					}
				}
					voto_candidato_per_categoria[k] /= count_divisore;
					count_divisore = 0;				
			}

			printf("Categoria %d:  vince candidato %d.\n", nomi_categorie[i], max_array(voto_candidato_per_categoria, numero_prove_distinte));
		}
		is_there = FALSE;
	}		
}

void stampa_vincitore_globale(int *voti_prove_partecipanti[], int numero_partecipanti, int numero_prove){

	float voto_candidato_globale[numero_partecipanti];
	int i, j;
	init_array_to_0( (float*) voto_candidato_globale, numero_partecipanti);

	for (i = 0; i < numero_partecipanti; ++i){
		int* voti_candidato = voti_prove_partecipanti[i];
		for (j = 0; j < numero_prove; ++j){
			voto_candidato_globale[i] += (float)voti_candidato[j];
		}
	}
	printf("Vincitore globale:  candidato %d.\n", max_array(voto_candidato_globale, numero_partecipanti));
}

void dealloca_voti_partecipanti(int *voti_prove_partecipanti[], int numero_partecipanti){
	int i;
	for (i = 0; i < numero_partecipanti; ++i){
		free(voti_prove_partecipanti[i]);
		voti_prove_partecipanti[i] = NULL;
	}
}

void alloca_e_salva_voti_partecipanti(int* array[], int dim, int dim_arr_allocati){
	int i;
	/*PER OGNI PARTECIPANTE*/
	for (i = 0; i < dim; ++i){
		int* temp_array = calloc(dim_arr_allocati, sizeof(int));
		if (temp_array != NULL){
			salva_array(temp_array, dim_arr_allocati);
			array[i]=temp_array;

		}else{
			puts("memoria esaurita");
			exit(EXIT_FAILURE);
		}
	}
}

void conta_elementi_distinti_array(int array[], int dim, int *elementi_distinti){
	(*elementi_distinti) = 0;
	int i,j;
	Bool is_there = FALSE;
	/*PER OGNI ELEMENTO DELLA LISTA, GUARDA NEI PRECEDENTI*/
	for (i = 0; i < dim; ++i){
		for (j = 0; j < i; ++j){
			if (array[i] == array[j]){
				is_there = TRUE;
			}
		}
		if (is_there == FALSE){
			++(*elementi_distinti);	
		}
		is_there = FALSE;	
	}
}

int max_array(float array[], int dim){
	int i, temp = array[0], result = 1;

	for (i = 1; i < dim; ++i){
		if (array[i] > temp ){
			temp = array[i];
			result = i+1;
		}
	}
	return result;
}

void init_array_to_0(float array[], int dim){
	int i;
	for (i = 0; i < dim; ++i){
		array[i] = 0;
	}
}

void salva_array(int array[], int dim){
	int i; 
	int temp = 0;
	for (i = 0; i < dim; ++i){
		salva_intero(&temp);
		array[i] = temp;
	}
}

void salva_intero(int *p){
	if (scanf("%d ", (int*) p)!= 1 || *p < 1){
		input_non_corretto();
	}	
}

void input_non_corretto(){
	puts("input non corretto.");
	exit(EXIT_FAILURE);
}