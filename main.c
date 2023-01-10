#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//структура фильма
typedef struct film{
    char name[100];
    int year;
    char country[60];
    char genre[50];
    float IMDb;
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
    fscanf(fin, "%d\n", &card -> year);
    fgets(card -> country, 60, fin);
    fgets(card -> genre, 50, fin);
    fscanf(fin, "%f\n", &card -> IMDb);
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
    scanf("%d", &card -> year);
    
    printf("\nEnter produsing country: ");
    while (getchar() == '\n'){
      fgets(card -> country, 60, stdin);
      break;
    }
    printf("\nEnter rating of film: ");
    scanf("%f", &card -> IMDb);
    printf("\nEnter film genre: ");
    while (getchar() == '\n'){
      fgets(card -> genre, 50, stdin);
      break;
    }
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
   printf("\033[31m┌───────────────────────────────────────────────────┐\n");
  printf("│                                                   │ \n");
  printf("│ %s", pFilm->name);
  printf("│ IMDb: %.1f                                         │\n", pFilm->IMDb);
  printf("│                                                   │ \n");
  printf("└───────────────────────────────────────────────────┘\n");
}

void printLeftRight(film *pFilm){
   printf("\033[34m┌───────────────────────────────────────────────────┐\n");
  printf("│                                                   │ \n");
  printf("│ %s", pFilm->name);
  printf("│ IMDb: %.1f                                         │\n", pFilm->IMDb);
  printf("│                                                   │ \n");
  printf("└───────────────────────────────────────────────────┘\n");
}

void printDetailedCurrent(film *pFilm){
  printf("\033[31m┌───────────────────────────────────────────────────┐\n");
  printf("│                                                   │ \n");
  printf("│ %s", pFilm->name);
  printf("│                                                   │ \n");
  printf("│ Year: %d                                        │\n", pFilm->year);
  printf("│                                                   │ \n");
  printf("│ Country: %s", pFilm->country);
  printf("│                                                   │ \n");
  printf("│ Genre: %s", pFilm->genre);
  printf("│                                                   │ \n");
  printf("│ IMDb: %.1f                                         │\n", pFilm->IMDb);
  printf("│                                                   │ \n");
  printf("└───────────────────────────────────────────────────┘\n");
}

//печать в файл
void fprintfCard(film *pFilm, FILE *fin){
  fprintf(fin, "\n%s", pFilm->name);
  fprintf(fin, "%d\n", pFilm->year);
  fprintf(fin, "%s", pFilm->country);
  fprintf(fin, "%s", pFilm->genre);
  fprintf(fin, "%.1f\n", pFilm->IMDb);
}

int main() {
  FILE *fin, *f;
  fin = fopen("filmList.txt", "a+");
  catalog *new;
  new = createCatalog(fin);
  for (int i = 0; i < 29; i++) {
    new = pushFromFile(fin, new);
  }
//     int is_admin = 0;
// //    if (alise.is_admin == 1){ пока не подкручена твоя структура
//     while (is_admin == 1) {
//       char action;
//       char A[2] = {'A', '\0'};
//       char D[2] = {'D', '\0'};
//       char E[2] = {'E', '\0'};
//       printf("Admin mode\n");
//       printf("If you wanna add new film press A\n");
//       printf("If you wanna exit admin mode press E\n");
//       scanf("%c", &action);
//       if (action == 'A') {
//         system("clear");
//         printf("Adding mode\n");
//         pushAdminFilm(new);
//         fprintfCard(new -> next -> card, fin);
//         printf("If you wanna add new film press A\n");
//         printf("If you wanna adding mode press E\n");
//         scanf("%c", &action);
//         if (action == 'E'){
//           break;
//         }
//         system("clear");
//       }
//       else if (action == 'E') {
//         printf("Goodbye, admin)))");
//         break;
//       }
//     }
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
        printf("If you you wanna exit info mode press e\n");
        scanf("%c", &actionInfoMode);
        if (actionInfoMode == 'e'){
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
  
