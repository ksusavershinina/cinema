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

film *createFilm(FILE* fin){
    film *card;
    card = (film *)malloc(sizeof(film));
    fgets(card -> name, 100, fin);
    fscanf(fin, "%d\n", &card -> year);
    fgets(card -> country, 60, fin);
    fgets(card -> genre, 50, fin);
    fscanf(fin, "%f\n", &card -> IMDb);
    return card;
}

catalog* createCatalog(FILE* fin){
    catalog *newList;
    newList = (catalog*)malloc(sizeof(catalog));
    newList -> card = createFilm(fin);
    newList -> next = newList;
    newList -> prev = newList;
    return newList;
}

catalog* push(FILE* fin, catalog *newList){
    catalog *cur, *earlier;
    cur = (catalog*) malloc(sizeof (catalog));
    earlier = newList -> next;
    newList -> next = cur;
    cur -> card = createFilm(fin);
    cur -> prev = newList;
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

void printCatalog(catalog *nLst){
    printf("%s %d\n %s %s %.1f\n", nLst->card->name, nLst->card->year, nLst->card->country, nLst->card->genre, nLst->card->IMDb);
}

void main() {
    FILE * fin;
    fin = fopen("list.txt", "r");
    catalog *new;
    new = createCatalog(fin);
    printCatalog(new);
    for (int i = 0; i < 29; i++){
        new = push(fin, new);
        printCatalog(new);
    }
}
