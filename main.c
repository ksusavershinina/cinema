#include <stdio.h>
#include <stdlib.h>

typedef struct film{
    char *name;
    int year;
    char *country;
    char *genre;
    float IMDb;
} film;

typedef struct catalog{
    film *card;
    struct film *next;
    struct film *prev;
} catalog;

film *createFilm(char *name, int year, char *country, char *genre, float IMDb){
    film *card;
    card = (film *)malloc(sizeof(film));
    card -> name = name;
//    card -> year = year;
//    card -> country = country;
//    card -> genre = genre;
//    card -> IMDb = IMDb;
    return card;
}

catalog* createCatalog(char *name, int year, char *country, char *genre, float IMDb){
    catalog *newList;
    newList = (catalog*)malloc(sizeof(catalog));
    newList -> card = createFilm(name, year, country, genre, IMDb);
    newList -> next = newList;
    newList -> prev = newList;
    return newList;
}

catalog* push(char *name, int year, char *country, char *genre, float IMDb, catalog *newList){
    catalog *cur, *earlier;
    cur = (catalog*) malloc(sizeof (catalog));
    earlier = newList -> next;
    newList -> next = cur;
    cur -> card = createFilm(name, year, country, genre, IMDb);
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



void main() {

}

