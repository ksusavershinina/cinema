#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//структура фильма
typedef struct film{
    char name[100];
    char year[5];
    char country[35];
    char genre[25];
    char IMDb[4];
} film;

//структура каталога
typedef struct catalog{
    film *card;
    struct catalog *next;
    struct catalog *prev;
} catalog;

//инициализация фильма из файла
film *createFilmFromFile(FILE* fin){
    film *card;
    card = (film *)malloc(sizeof(film));
    fgets(card -> name, 100, fin);
    fgets(card -> year, 6, fin);
    card -> year[4] = '\0';
    fgets(card -> country, 35, fin);
    fgets(card -> genre, 25, fin);
    fgets(card -> IMDb, 5, fin);
    card -> IMDb[3] = '\0';
    return card;
}
//инициализация фильма из консоли
film *createAdminFilm(void){
    film *card;
    card = (film *)malloc(sizeof(film));
    printf("Enter film name: ");
    while (getchar() == '\n'){
      fgets(card -> name, 100, stdin);
      break;
    }
    printf("\nEnter year of release: ");
    //while (getchar() == '\n'){
    fgets(card -> year, 6, stdin);
    //check_len(card -> year, 5, 1);
      //break;
    //}
    printf("\nEnter produsing country: ");
    //while (getchar() == '\n'){
      fgets(card -> country, 35, stdin);
      //break;
    //}
    printf("\nEnter rate of film: ");
    //while (getchar() == '\n'){
    fgets(card -> IMDb, 5, stdin);
    card -> year[3] = '\0';
      //break;
    //}
    printf("\nEnter film genre: ");
    //while (getchar() == '\n'){
      fgets(card -> genre, 25, stdin);
      //break;
    //}
  return card;
}

//инициализация каталога, головы
catalog* createCatalog(FILE* fin){
    catalog *newList;
    newList = (catalog*)malloc(sizeof(catalog));
    newList -> card = createFilmFromFile(fin);
    newList -> next = newList;
    newList -> prev = newList;
    return newList;
}

//пуш из файла
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

//пуш из консоли
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

//поп по идеи должна удалятьиз инициализиорванного каталога карточку с фильмом
catalog* pop(catalog *newList){
    catalog *next, *prev;
    prev = newList -> prev;
    next = newList -> next;
    prev -> next = newList -> next;
    next -> prev = newList -> prev;
    free(newList);
    return prev;
}

//печать в консоль
void printCurrent(film *pFilm){
   printf("\033[35m┌───────────────────────────────────────────────────┐\n");
  printf("│                                                   │ \n");
  printf("│ %s", pFilm->name);
  printf("│ IMDb: %s                                         │\n", pFilm->IMDb);
  printf("│                                                   │ \n");
  printf("└───────────────────────────────────────────────────┘\n");
}

void printLeftRight(film *pFilm){
   printf("\033[34m┌───────────────────────────────────────────────────┐\n");
  printf("│                                                   │ \n");
  printf("│ %s", pFilm->name);
  printf("│ IMDb: %s                                         │\n", pFilm->IMDb);
  printf("│                                                   │ \n");
  printf("└───────────────────────────────────────────────────┘\n");
}

void printDitailedCurrent(film *pFilm){
  printf("\033[35m┌───────────────────────────────────────────────────┐\n");
  printf("│                                                   │ \n");
  printf("│ %s", pFilm->name);
  printf("│                                                   │ \n");
  printf("│ Year: %s                                        │\n", pFilm->year);
  printf("│                                                   │ \n");
  printf("│ Country: %s", pFilm->country);
  printf("│                                                   │ \n");
  printf("│ Genre: %s", pFilm->genre);
  printf("│                                                   │ \n");
  printf("│ IMDb: %s                                         │\n", pFilm->IMDb);
  printf("│                                                   │ \n");
  printf("└───────────────────────────────────────────────────┘\n");
}

//печать в файл
void printfCardInFile(film *pFilm, FILE *fin){
  fprintf(fin, "\n%s", pFilm->name);
  fprintf(fin, "%s", pFilm->year);
  fprintf(fin, "%s", pFilm->country);
  fprintf(fin, "%s", pFilm->genre);
  fprintf(fin, "%s", pFilm->IMDb);
}

int main() {
  FILE *fin, *f;
  fin = fopen("filmList.txt", "a+");
  catalog *new;
  new = createCatalog(fin);
  for (int i = 0; i < 29; i++) {
    new = pushFromFile(fin, new);
  }
//     
  while (1){
    char action;
    printLeftRight(new -> prev -> card);
    printCurrent(new -> card);
    printLeftRight(new -> next -> card);
    printf("If you you wanna see another movies press a-d\n");
    printf("If you you wanna see more information press w\n");
    printf("If you you wanna get in admin mode press c\n");
    printf("If you you wanna leave press l\n");
    scanf("%c", &action);
    if (action == 'a'){
      new = new -> prev;
    }
    if (action == 'd'){
      new = new -> next;
    }
    if (action == 'w'){
      while (1){
        char actionInfoMode;
        system("clear");
        printLeftRight(new -> prev -> card);
        printDitailedCurrent(new -> card);
        printLeftRight(new -> next -> card);
        printf("If you wanna exit info mode press s\n");
        scanf("%c", &actionInfoMode);
        if (actionInfoMode == 's'){
          system("clear");
          break;
        }
      }
    }
    system("clear");
    if (action == 'l'){
      printf("Bye)))");
      break;
    }
  }
  return 0;
}
  
