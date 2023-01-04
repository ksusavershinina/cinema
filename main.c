#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user{
    char *login;
    char *password;
    char *card;
    int favourites;
    int is_admin;
} user;

void check_len(char *string, int min_len, int max_len) {
    if (strlen(string)-1 < min_len || strlen(string)-1 > max_len) {
        while (strlen(string)-1 < min_len || strlen(string)-1 > max_len) {
            printf("wrong length, try again:\n");
            fgets(string, 1000, stdin);
        }
    }
}

void check_dig(char *string) {
    if (strcspn(string, "0123456789") == strlen(string)) {
        while (strcspn(string, "0123456789") == strlen(string)) {
            printf("don't include numbers, try again:\n");
            fgets(string, 1000, stdin);
            check_len(string, 3, 20);
        }
    }
}

void check_lower(char *string) {
    if (strcspn(string, "qwertyuiopasdfghjklzxcvbnm") == strlen(string)) {
        while (strcspn(string, "qwertyuiopasdfghjklzxcvbnm") == strlen(string)) {
            printf("don't include lowercase, try again:\n");
            fgets(string, 1000, stdin);
            check_len(string, 3, 20);
        }
    }
}

int luhn(const char * card_number) {  // принимаем в аргументы номер карты
    int len = strlen(card_number);    // узнаем длину номера карты
    int digit = 0;                    // текущая цифра в цикле (см. ниже)
    int check_digit = 0;              // переменная, которая будет хранить проверочную цифру
    int i;
    for (i = len - 1; i >= 0; --i) {    // главный цикл, в процессе него вычисляется проверочная цифра
        digit = card_number[i] - '0'; // переводим цифру из char в int
        if (i % 2 == 0) {              // если позиция цифры чётная, то:
            digit *= 2;               // умножаем цифру на 2
            if (digit > 9)            // согласно алгоритму, ни одно число не должно быть больше 9
                digit -= 9;           // второй вариант сведения к единичному разряду
        }
        check_digit += digit;         // прибавляем к check_digit номера согласно алгоритму
    }
    return check_digit % 10;    // возвращаем проверочное число, вычисленное согласно алгоритму
}

char* login(user *user) {
    char *login;
    login = (char*)malloc(sizeof(char)*1000);
    printf("enter you login. must include:\n");
    printf("1. lengh: 3-20 symbols\n");
    printf("2. at least one digit\n\n");
    fgets(login, 1000, stdin);
    check_lower(login);
    check_len(login, 3, 20);
    check_dig(login);
    login[strlen(login) - 1] = '\0';
    return login;
}

char* password(user *user) {
    printf("\nenter you password. must include:\n");
    printf("1. lengh: 6-20 symbols\n");
    printf("2. uppercase and lowercase\n");
    printf("3. at least one digit\n\n");
    char *password;
    password = (char*)malloc(sizeof(char)*1000);
    fgets(password, 1000, stdin);
    check_len(password, 6, 20);
    check_dig(password);
    if (strcspn(password, "QWERTYUIOPASDFGHJKLZXCVBNM") == strlen(password)) {
        while (strcspn(password, "QWERTYUIOPASDFGHJKLZXCVBNM") == strlen(password)) {
            printf("don't include uppercase, try again:\n");
            fgets(password, 1000, stdin);
            check_len(password, 6, 20);
        }
    }
    check_lower(password);
    password[strlen(password) - 1] = '\0';
    return password;
}

char* card (user *user) {
    printf("\nenter number of you credint card:\n");
    char *card;
    card = (char*)malloc(sizeof(char)*1000);
    fgets(card, 1000, stdin);
    while (strcspn(card, "qwertyuiopasdfghjklzxcvbnm") != strlen(card)) {
        printf("wrong card number. try again\n");
        fgets(card, 1000, stdin);
    }
    while (strlen(card) != 17) {
        printf("wrong card number. try again\n");
        fgets(card, 1000, stdin);
    }
    card[strlen(card) - 1] = '\0';
    return card;
}

void registrate_user(user *user) {
    printf("hello!\n");
    user->login = login(user);
    user->password = password(user);
    user->card = card(user);
    system("clear");
    printf("\nregistration complete!\nwelcome!\n");
}

void init_user (user *user) {
    user->login = (char*)malloc(sizeof(char));
    user->password = (char*)malloc(sizeof(char));
    user->card = (char*)malloc(sizeof(char));
}

int main() {
    user alise;
    init_user(&alise);
    registrate_user(&alise);
    printf("you have such information:\n\n");
    printf("login is %s\n", alise.login);
    printf("password is %s\n", alise.password);
    printf("card number is %s\n", alise.card);
    printf("\nif you want to change you informatoin, click 1: ");
    int changes;
    scanf("%d", &changes);
    if (changes == 1) {
        system("clear");
        printf("\nwhat do you want to change?");
        printf("\nif you want change you password, type \"pass\"");
        printf("\nif you want change you login, type \"log\"");
        printf("\nif you want change you card, type \"card\"\n");
        char buf[100];
        scanf("%s", buf);
        int flag = 0;
        while (flag != 1) {
            if (strcmp(buf, "pass") == 0) {
                flag = 1;
                system("clear");
                alise.password = password(&alise);
                system("clear");
                printf("complete!\n");
            } else if (strcmp(buf, "log") == 0) {
                flag = 1;
                system("clear");
                alise.login = login(&alise);
                system("clear");
                printf("complete!\n");
            } else if (strcmp(buf, "card") == 0) {
                flag = 1;
                system("clear");
                alise.card = card(&alise);
                system("clear");
                printf("complete!\n");
            }
            else {
                printf("program don't understand you. try again\n");
                scanf("\n%s", buf);
            }
        }
    } else {
        printf("ok\n");
    }
}