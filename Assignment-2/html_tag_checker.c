#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 999

typedef struct Stack {
    char data[MAX_LEN];
    struct Stack *next;

} Stack;
Stack *top = NULL;

void push();
void pop();
void check_top();
int is_empty();
void display();
int capacity();
int menu();
void push_tags();
void pop_wnc();
void clrscr();
void check_opened_tags();
void check_closed_tags();

int main(int argc, char const *argv[])
{
    char file_name[50], save[MAX_LEN], opened[25], closed[25];
    FILE *file;

    menu:
    int menu_s = menu();
    switch (menu_s)
    {
    case 1:
    retry:
        printf("Dosya Adını Giriniz (Dosya Mevcut Olmalıdır): ");
        scanf("%s",file_name);
        file = fopen(file_name, "r");
        if(file == NULL){
            printf("Dosya Çalışma Dizininde Mevcut Değil!\n"); 
            goto retry;
        }
        while(fgets(save,MAX_LEN, file) != NULL){
            check_opened_tags(save);
            check_closed_tags(save);
        }
        fclose(file);
        //clrscr();
        printf("Ana Menüye Dönmek İçin Enter'e Basınız\n");
        getchar();
        getchar();
        goto menu;
        break;
        case 2:
            check_top();
            printf("Ana Menüye Dönmek İçin Enter'e Basınız\n");
            getchar();
            goto menu;

            break;
        case 3:
            display();
            printf("Ana Menüye Dönmek İçin Enter'e Basınız\n");
            getchar();
            goto menu;
            break;
        case 4:
            printf("Hata Sayısı: %d\n", capacity());
            printf("Ana Menüye Dönmek İçin Enter'e Basınız\n");
            getchar();
            goto menu;

            break;
        case 5:
            if(top == NULL)
                printf("Hata Yok!\n");
            else 
                printf("Bazı Hatalar Mevcut!\n");

            printf("Ana Menüye Dönmek İçin Enter'e Basınız\n");
            getchar();
            goto menu;

        case 6:    
        while(top->data !=NULL)
            pop();
            printf("Ana Menüye Dönmek İçin Enter'e Basınız\n");
            getchar();
            goto menu;
        case 7:
            clrscr();
            exit(-1);
            break;
    default:
        printf("Seçim Değerleri Dışında Değer Seçildi. Tekrar Seçim Yapmak İçin Yönlendiriliyorsunuz !\nOnaylamak İçin Enter'e Basınız");
        getchar();
        goto menu;
        break;
    
    
    }
}
void push(char sent[]){
    Stack *new_stack;
    new_stack = (Stack*)malloc(sizeof(Stack));
    strcpy(new_stack->data, sent);
    if(top == NULL)
        new_stack->next = NULL;
    else
        new_stack->next = top;
    top = new_stack;
}

void pop(){
    if(top == NULL)
        printf("Kaldırılacak Hata Yok !");
    else {
        Stack *tmp = top;
        printf("Yığından Çıkan Hata: %s\n", tmp->data);
        top = tmp->next;
        free(tmp);
    }
}
void pop_wnc(){
    if(top == NULL)
        ;
    else {
        Stack *tmp = top;
        top = tmp->next;
        free(tmp);
    }
}

void display(){
    Stack *tmp = top;
    if(tmp == NULL)
        printf("Hata Yok !\n");
    while(tmp != NULL){
        printf("%s\n", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void check_top(){
    if(top == NULL)
        printf("Hata Yok !\n");
    else
        printf("Son Hata Sebebi: %s\n", top->data);
}

int is_empty(){
    return top == NULL; 
}

int capacity(){
    Stack *temp = top;
    int count = 0;
    while(temp != NULL){
        temp = temp->next;
        count++;
    }

    return count;
}
int menu(){
    int i;
    char c_i[5];
    clrscr();
    printf("--------------------------------------------------------------------\n");
    printf("|Yığın Veri Yapısı İle HTML Dosyası Etiket (Tag) Kontrolü Programı |\n");
    printf("|Yapacağınız İşlemi Sayı İle Belirtiniz.\t\t\t   |\n");
    printf("|1)HTML Dosyasını Kontrol Et\t\t\t\t\t   |\n|2)Son Hatayı Görüntüle\t\t\t\t\t\t   |\n");
    printf("|3)Hataları Görüntüle\t\t\t\t\t\t   |\n|4)Toplam Hata Sayısını Görüntüle\t\t\t\t   |\n|");
    printf("5)Hata Durumunu Kontrol Et\t\t\t\t\t   |\n|6)Hataları Sil\t\t\t\t\t\t\t   |\n|7)Programı Kapat\t\t\t\t\t\t   |\n");
    printf("--------------------------------------------------------------------\n");
    
    printf("Seçiminiz: ");
    fgets(c_i,5,stdin);

    i = atoi(c_i);
    return i;
}

void clrscr(){
    #ifdef _WIN32
        system("cls");      //https://stackoverflow.com/questions/44679195/how-to-send-command-to-linux-command-from-c-program
    #else
        system("clear");
    #endif
}

void check_opened_tags(char string[]){
    FILE *fp;
    char opened[25];
    fp = fopen("open_tag.txt", "r");
    while(fgets(opened, 25, fp)!=NULL)
        if(strstr(string,opened) != NULL)
            push(opened);
    fclose(fp);
}
void check_closed_tags(char string[]){
    FILE *fp;
    char closed[25];
    fp = fopen("close_tag.txt", "r");
    while(fgets(closed, 25, fp)!=NULL)
        if(strstr(string,closed) != NULL)
            pop_wnc();
    fclose(fp);
}

//Pseudo Code
    // dosyayı aç, açılan dosyadaki stringi bir yere kaydet. 
    // dizi listesinde gezerken <'dan başlayıp >'a kadar olan kısmı kaydet
    // (html için istisna var unutma). <name>'leri topa at ve </name> ile rast gelirse popla'
//Ownership
//<head>
 //  <meta name="author" content="Alper Karaca">
 //</head>