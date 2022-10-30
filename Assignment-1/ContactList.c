#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 64
#define MAX_EMAIL_LEN 256
typedef struct Node {
    char name[MAX_NAME_LEN];
    char surname[MAX_NAME_LEN];
    char number[15];
    char email[MAX_EMAIL_LEN];
    struct Node *next;
} Node;


Node *user_1 = NULL;
Node *make_new_node(char[], char[], char[], char[]);
void add_contact();
void display();
void delete_contact();
void search_contact();
void clrscr();

int main(){
    char t_name[MAX_NAME_LEN],t_surname[MAX_NAME_LEN], t_number[15], t_email[MAX_EMAIL_LEN], save_order[4], selection[3], inline_selection[3];
    int  count = 0, total_contact = 1, in_sel;
    float person, f_selection;

    decision:
    clrscr();           //https://iq.opengenus.org/detect-operating-system-in-c/
    printf("|----------------------------------------------------------|\n");
    printf("|  Lütfen İşlem Seçiminizi Bir Rakam Belirterek Yapınız !  |\n");
    printf("|----------------------------------------------------------|\n");
    printf("\t1)Rehbere Kişi Ekle\n\t2)Rehberde Kişi Ara\n\t3)Rehberden Kişi Sil\n\t4)Kayıtlı Kişileri Görüntüle\n\t5)Uygulamayı Kapat\nSeçiminiz: ");
    fgets(selection,3,stdin);
    f_selection = strtof(selection,NULL);
    switch ((int)f_selection)
    {
        case 1:
            printf("\nKaç Kişi Kaydedilecek: ");
            fgets(save_order,4,stdin);
            person = strtof(save_order,NULL);
            while(count < person){
                printf("\n[%d. Kişi Kaydediliyor.]\n", total_contact);
                printf("Ad Giriniz: ");
                fgets(t_name, MAX_NAME_LEN, stdin);
                printf("Soyad Giriniz: ");
                fgets(t_surname, MAX_NAME_LEN, stdin);
                printf("Telefon Numarasını Ülke ve Alan Kodu İle Giriniz (Örnek: +905555555555): ");
                fgets(t_number,15, stdin);
                printf("Mail Adresi Giriniz: ");
                fgets(t_email, MAX_EMAIL_LEN, stdin);
                if(!strchr(t_email,'@')){
                    printf("Bu Geçerli Bir Mail Adresi Değil !\n");
                printf("Ana Menüye Dönmek İçin Enter'e Basınız.\n");
                getchar();
                count = 0;
                goto decision;
                }
                add_contact(t_name, t_surname, t_number, t_email);
                count++;
                total_contact++;
                clrscr();
                
            }
            count = 0;
            goto decision;
            break;
        case 2:
            char s_name[MAX_NAME_LEN];
            printf("Hangi Değere Göre Arama Yapılsın\n1)Ad İle Arama Yap\n2)Soyadı İle Arama Yap\nSeçiminiz: ");
            fgets(inline_selection,3,stdin);
            in_sel = atoi(inline_selection);
            switch (in_sel)
            {
            case 1:
                printf("Aranacak Kişinin İsmini Harflere Dikkat Ederek Yazınız: ");
                fgets(s_name, MAX_NAME_LEN, stdin);
                search_contact(&user_1,s_name,in_sel);
                break;
            case 2:
                printf("Aranacak Kişinin Soyismini Harflere Dikkat Ederek Yazınız: ");
                fgets(s_name, MAX_NAME_LEN, stdin);
                search_contact(&user_1, s_name,in_sel);
                break;
            default:
                printf("Hatalı Seçim Yapıldı.");
                break;
            }

            printf("\nEkranı Temizleyip Ana Sayfaya Dönmek İçin Enter Tuşuna Basınız !\n");
            getchar();
            goto decision;
            break;
        case 3:
            char del_name[MAX_NAME_LEN];
            printf("Hangi Değere Göre Silinsin\n1)Ad İle Sil\n2)Soyad İle Sil\nSeçiminiz: ");
            fgets(inline_selection,3,stdin);
            in_sel = atoi(inline_selection);
            switch (in_sel)
            {
            case 1:
                printf("Silinecek Kişinin Adını Giriniz: ");
                fgets(del_name, MAX_NAME_LEN,stdin);
                delete_contact(&user_1, del_name, in_sel);
                break;
            case 2:
                printf("Silinecek Kişinin Soyadını Giriniz: ");
                fgets(del_name, MAX_NAME_LEN, stdin);
                delete_contact(&user_1, del_name, in_sel);
                break;
            
            default:
                printf("Hatalı Seçim Yaptınız !");
                break;
            }

            total_contact--;
            printf("\nEkranı Temizleyip Ana Sayfaya Dönmek İçin Enter Tuşuna Basınız !\n");
            getchar();
            goto decision;
            break;

        case 4: 
        display();
        printf("\nEkranı Temizleyip Ana Sayfaya Dönmek İçin Enter Tuşuna Basınız !\n");
        getchar();
        goto decision;
        break;

        case 5:
            clrscr();
            return -1;
    default:
        printf("Yanlış Seçim Yaptınız.\n");
        printf("\nEkranı Temizleyip Ana Sayfaya Dönmek İçin Enter Tuşuna Basınız !\n");
        getchar();
        goto decision;
        break;
    }

}

void add_contact(char na[],char su[],char nu[], char em[]){
    Node *new_node = make_new_node(na, su, nu, em);
    if(user_1 == NULL)
        user_1 = new_node;
    else{
        Node *temp = user_1;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}
Node *make_new_node(char na[], char su[], char nu[], char em[]){
	Node *yenidugum = (Node*)malloc(sizeof(Node));
    strcpy(yenidugum->name, na);
    strcpy(yenidugum->surname,su);
    strcpy(yenidugum->number, nu);
    strcpy(yenidugum->email, em);
    yenidugum->next = NULL;
    return yenidugum;
}

void display(){
    Node *traverse = user_1;
    if(traverse == NULL)
        printf("Rehber Boş\n");
    else{
               
    printf("|--------------------|\n|KAYITLI KULLANICILAR|\n|--------------------|\n");
    int i = 1;
    while(traverse != NULL){
        if(i<10) printf("|-------------|\n|  [%d. Kişi]  |\n|-------------|\nAd: %sSoyad: %sTelefon Numarası: %sE-Mail Adresi: %s", i,traverse->name,traverse->surname, traverse->number, traverse->email);
        else printf("|--------------|\n|  [%d. Kişi]  |\n|--------------|\nAd: %s Soyad: %sTelefon Numarası: %sE-Mail Adresi: %s", i,traverse->name, traverse->surname, traverse->number, traverse->email);
        traverse = traverse->next;
        i++;
    printf("\n");

    }
    }
}

void delete_contact(Node** ref, char name_to_delete[],int option){
    Node *tmp = *ref, *previous;
    if(tmp == NULL) {printf("Rehber boş !\n"); return;}
    while(tmp != NULL){
        switch (option)
        {
        case 1:
            if(!(strcmp(tmp->name, name_to_delete))){
                *ref = tmp->next;
                printf(" Silinen Kişi\nAdı: %sSoyadı:%sTelefon Numarası: %sMail Adresi: %s ", tmp->name, tmp->surname, tmp->number, tmp->email);
                free(tmp);
                return;
            }
            if(tmp->next == NULL)
                printf("Aranan Kişi Rehberde Bulunamadı !\n");
                return;    
            break;
        case 2:
            if(!(strcmp(tmp->surname, name_to_delete))){
                *ref = tmp->next;
                printf("Silinen Kişi\nAdı: %sSoyadı: %sTelefon Numarası: %sMail Adresi: %s ", tmp->name, tmp->surname,tmp->number, tmp->email);
                free(tmp);
                return;
            }
            if(tmp->next==NULL)
                printf("Aranan Kişi Rehberde Bulunamadı !\n");
                return;
            break;
            default:
                break;
        }
    previous->next = tmp->next;
    free(tmp);
}
}

void search_contact(Node **ref, char name[], int option){
    Node *crt = *ref;
    if(crt == NULL)
        printf("Rehber Boş !\n");
    while(crt != NULL){
        switch (option)
        {
        case 1:
            if(!(strcmp(crt->name,name))){
                printf("Aranan Kişi Bulundu !\n");
                printf("Ad: %sSoyad: %sTelefon Numarası: %sE-Mail Adresi: %s", crt->name, crt->surname, crt->number, crt->email);
                return;
            }
        
            if(crt->next == NULL)
                printf("Böyle Bir Kontak Yok !");
            crt = crt->next;           
            break;
        case 2:
            if(!strcmp(crt->surname,name)){
                printf("Aranan Kişi Bulundu !\n");
                printf("Ad: %sSoyad: %sTelefon Numarası: %sE-Mail Adresi: %s", crt->name, crt->surname, crt->number, crt->email);
            }
            if(crt->next == NULL)
                printf("Böyle Bir Kontak Yok");
                crt = crt->next;
        default:
            break;
        }
        
    }
    return ;
}

void clrscr(){
    #ifdef _WIN32
        system("cls");      //https://stackoverflow.com/questions/44679195/how-to-send-command-to-linux-command-from-c-program
    #else
        system("clear");
    #endif
}


