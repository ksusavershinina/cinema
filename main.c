#include <stdio.h>
#include <stdlib.h>

typedef struct film{
    char name[100];
    int year;
    char country[60];
    char genre[50];
    float IMDb;
} film;

typedef struct catalog{
    film *card;
    struct film *next;
    struct film *prev;
} catalog;

film *createFilmFromFile(FILE* fin){
    film *card;
    card = (film *)malloc(sizeof(film));
    fgets(card -> name, 100, fin);
    fscanf(fin, "%d\n", &card -> year);
    fgets(card -> country, 60, fin);
    fgets(card -> genre, 50, fin);
    fscanf(fin, "%f\n", &card -> IMDb);
    return card;
}

film *createAdminFilm(void){
    film *card;
    card = (film *)malloc(sizeof(film));
    printf("Enter film name: ");
    gets(card -> name);
    printf("Enter year of release: ");
    scanf("%d\n", &card -> year);
    printf("Enter produsing country: ");
    gets(card -> country);
    printf("Enter film genre: ");
    gets(card -> genre);
    printf("Enter rating of film on IMDb: ");
    scanf("%f\n", &card -> IMDb);
    return card;
}

catalog* createCatalog(FILE* fin){
    catalog *newList;
    newList = (catalog*)malloc(sizeof(catalog));
    newList -> card = createFilmFromFile(fin);
    newList -> next = newList;
    newList -> prev = newList;
    return newList;
}

catalog* pushFromFile(FILE* fin, catalog *newList){
    catalog *cur, *earlier;
    cur = (catalog*) malloc(sizeof (catalog));
    earlier = newList -> next;
    newList -> next = cur;
    cur -> card = createFilmFromFile(fin);
    cur -> prev = newList;
    cur -> next = earlier;
    earlier -> prev = cur;
    return cur;
}

catalog* pushAdminFilm(catalog *nList){
    catalog *cur, *earlier;
    cur = (catalog*) malloc(sizeof (catalog));
    earlier = nList -> next;
    nList -> next = cur;
    cur -> card = createAdminFilm();
    cur -> prev = nList;
    cur -> next = earlier;
    earlier -> prev = cur;
    return cur;
}

catalog* pop(catalog *newList){
    catalog *next, *prev;
    prev = newList -> prev;
    next = newList -> next;
    prev -> next = newList -> next;
    next -> prev = newList -> prev;
    free(newList);
    return prev;
}

void printF(film *pFilm){
    printf("%s", pFilm->name);
    printf("%d\n", pFilm->year);
    printf("%s", pFilm->country);
    printf("%s", pFilm->genre);
    printf("IMDb rating: %.1f\n", pFilm->IMDb);
}

void main() {
    FILE * fin;
    fin = fopen("list.txt", "r");
    catalog *new;
    new = createCatalog(fin);
    //printF(new->card);
    for (int i = 0; i < 29; i++){
        new = pushFromFile(fin, new);
        //printF(new->card); это проверка печает весь список
    }
    int is_admin = 1;
//    if (alise.is_admin == 1){ пока не подкручена твоя структура
    if (is_admin == 1){
        int action;
        printf("If you wanna add new film press 1\n");
        printf("If you wanna delete film from catalog press 0\n");
        scanf("%d", &action);
        if (action == 1){
            pushAdminFilm(new);
            printF(new->card);
        }
    }
}
