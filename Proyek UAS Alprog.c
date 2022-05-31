#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct UserNode {														
	char username[20];
	char password[20];
	char nama[30];
	int umur;
	int ratarata_jam, ratarata_menit;
	char gender[30];
	struct UserNode *next;
};

typedef struct {
	char name[50];
	int jam_tidur[7], menit_tidur[7], jam_bangun[7], menit_bangun[7], durasi_jam[7], durasi_menit[7], keterangan[3];
} bobosehat;
bobosehat data[100];
typedef struct UserNode User;
typedef User *userptr;

const char *display_hari[] = {"", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
const char *display_keterangan[] = {"", "Kurang", "Cukup", "Berlebihan"};

int i=-1, j, m=-1, n, count = 10, terdaftar = 10;
int rata_jam, rata_menit;
char c, used[100][20];

void mainmenu(userptr *head, userptr *tail);						//Menu untuk memilih user dalam program
void user(userptr *head, userptr *tail);							//Menu sebagai user
void admin(userptr *head, userptr *tail);							//Menu sebagai admin
void signup(userptr *head, userptr *tail);							//Melakukan pendaftaran akun user
void konversigender(int key, char konversi[]);						//Mengubah kode angka menjadi string gender
void login(userptr *head, userptr *tail);							//Melakukan login dengan akun yang sudah terdaftar
void printuser(userptr head);										//Menampilkan seluruh user yang terdaftar
userptr swap(userptr ptr1, userptr ptr2);							//Menukar urutan node pada linkedlist
void submenu(userptr *head, userptr *tail);							//Menampilkan menu sorting dan searching data user
void listdata();													//Menampilkan data yang dapat di sorting
void listsearch();													//Menampilkan data yang dapat di searching
void petunjukuser();												//Menampilkan petunjuk penggunaan sebagai user
void petunjukadmin();												//Menampilkan petunjuk penggunaan sebagai admin
void inisialisasi(userptr *head, userptr *tail);					//Memasukkan beberapa data user yang telah terdaftar
void jam_tidur(userptr head, char username[20]);					//Menginput jam tidur
void data_tidur(userptr head, char username[20]);					//Merekap jam tidur
void keterangan(void);												//Memberikan keterangan kualitas tidur
void durasi_tidur(void);											//Menghitung durasi tidur
void regularity(void);												//Menghitung regularitas tidur
void search_max(void);												//Mencari waktu tidur terlama
void search_min(void);												//Mencari waktu tidur tersingkat
int recursive_mean(int jam[], int N);								//Menghitung rata rata tidur
void ratarata_tidur(userptr *head, userptr *tail, char username[20]);//Memasukkan nilai rata rata tidur pada linkedlist

void SortNamaUP(userptr *head, int count);							//Sorting ascending berdasarkan nama
void SortNamaDOWN(userptr *head, int count);						//Sorting descending berdasarkan nama
void SortUmurUP(userptr *head, int count);							//Sorting ascending berdasarkan umur
void SortUmurDOWN(userptr *head, int count);						//Sorting descending berdasarkan umur
void SortGenderUP(userptr *head, int count);						//Sorting ascending berdasarkan gender
void SortGenderDOWN(userptr *head, int count);						//Sorting descending berdasarkan gender

void writeLinkedList(char filename[], userptr *head);				//Menyimpan data user pada file external

int main(){
	userptr head = NULL;
	userptr tail = NULL;
	inisialisasi(&head, &tail);
	mainmenu(&head, &tail);
	return 0;
}

void mainmenu(userptr *head, userptr *tail){
	int menu = -1;
	while (menu != 0){
		system("cls");
		printf ("================ SELAMAT DATANG DI BOBOSEHAT! ================\n\n");
		printf ("                   ------ MAIN MENU ------\n");
		printf ("                        Siapakah Anda?\n");
		printf ("                         [1] User\n");
		printf ("                         [2] Admin\n");
		printf ("                         [0] Keluar\n");
		printf ("                         Input : ");
		scanf ("%d", &menu);
	
		switch (menu){
			case 1:{
				system("cls");
				user(head, tail);
				break;
			}
			case 2:{
				system("cls");
				admin(head, tail);
				break;
			}
			case 0:{
				printf("\n        Terima Kasih Telah Menggunakan Program Kami!\n");
				exit(0);
			}
			default:{
				printf ("\nInput yang diberikan salah! Silahkan tekan key apapun untuk lanjut...\n");
				getch();
				system("cls");
				break;
			}
		}
	}
}

void user(userptr *head, userptr *tail){

	int menu = -1;
	while (menu != 0){
		system("cls");
		printf ("===================== APLIKASI BOBOSEHAT =====================\n\n");
		printf ("                   ------ MENU USER ------\n");
		printf ("              Silakan Masuk Menggunakan Akun Anda\n");
		printf ("                         [1] Sign Up\n");
		printf ("                         [2] Log In\n");
		printf ("                         [3] Petunjuk\n");
		printf ("                         [0] Main Menu\n");
		printf ("                         Input : ");
		scanf ("%d", &menu);
		
		switch (menu){
			case 1:{
				system("cls");		
				signup(head, tail);
				printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
				getch();
				break;
			}
			case 2:{
				system("cls");
				login(head, tail);
				break;
			}
			case 3:{
				system("cls");
				petunjukuser();
				printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
				getch();
				break;
			}			
			case 0:{
				system("cls");
				mainmenu(head, tail);
				break;
			}
			default:{
				printf ("\nInput yang diberikan salah! Silahkan tekan key apapun untuk lanjut...\n");
				getch();
				system("cls");
				break;
			}
		}
	}	
}

void signup(userptr *head, userptr *tail){
	char username[20], password[20], nama[30], konversi[30], c;
	int umur, gender, i, index = 0;

	userptr newPtr;
	newPtr = malloc(sizeof(User));
	printf ("================== APLIKASI BOBO SEHAT ==================\n\n");
	printf ("                 ------ SIGN UP ------\n\n");	
	printf("Masukkan Username Anda   : ");
	scanf (" %[^\n]s", &username);
	for (i = 0; i < terdaftar+1; i++){
		if (strcmp(username, used[i]) == 0){
			printf("\nUsername tersebut sudah terdaftar!");
			return;
		}
	}
	strcpy(used[terdaftar], username);
	printf("Masukkan Password Anda   : ");
	while ((c = getch()) != 13){
	    if (c == 8){
	    	if (index == 0){
		    	index = 0;
		    	continue;
			}
			else{
				putch('\b');
		        putch(' ');
		        putch('\b');
		        index--;
			}
	    	continue;
	    }
		else{
		    password[index++] = c;
		    putch('*'); 
		}
	}
	password[index] = '\0';
	printf("\n\nMasukkan Nama Anda       : ");
	scanf (" %[^\n]s", &data[i].name);
	strcpy(nama, data[i].name);
	printf("Masukkan Umur Anda       : ");
	scanf ("%d", &umur);				
	printf("\n[1] Perempuan\n[2] Laki-Laki\n\n");
	printf("Masukkan Gender Anda : ");
	scanf ("%d", &gender);
	konversigender(gender, konversi);
	
	if (newPtr != NULL) {
		strcpy(newPtr->username, username);
		strcpy(newPtr->password, password);
		strcpy(newPtr->nama, nama);
		newPtr->umur = umur;
		strcpy(newPtr->gender, konversi);
		newPtr->next = NULL;
		
		if (*head == NULL){
			*head = newPtr;			
		}
		else{
			(*tail)->next = newPtr;
		}
		*tail = newPtr;                        
	}
	else{
		printf("\nError\n");
	}
	terdaftar++;
	writeLinkedList("DataUser.txt", &newPtr);
	printf("\nSign Up Sukses!");
}

void login(userptr *head, userptr *tail){
	int masuk = 0, count = 0;
	int index = 0;
	char c, username[20], password[20];
	userptr temp;
	
	while(masuk == 0){
		int user = -1;
		temp = *head;
		index = 0;
		system("cls");
		printf ("================== APLIKASI BOBOSEHAT ==================\n\n");
		printf ("                  ------ LOG IN ------\n\n");	
		printf("Masukkan Username Anda   : ");
		scanf (" %[^\n]s", &username);
		printf("Masukkan Password Anda   : ");
		while ((c = getch()) != 13){
		    if (c == 8){
		    	if (index == 0){
			    	index = 0;
			    	continue;
				}
				else{
					putch('\b');
			        putch(' ');
			        putch('\b');
			        index--;
				}
		    	continue;
		    }
			else{
			    password[index++] = c;
			    putch('*'); 
			}
		}
		password[index] = '\0';
	
		while (temp != NULL) {
			if(strcmp(temp->username, username) == 0){
				if (strcmp(temp->password, password) == 0){
					masuk = 1;					
				}
				else{
					count++;
					if (count == 3){
						printf ("\n\nAnda terlau banyak melakukan kesalahan, Silahkan tekan key apapun untuk lanjut...\n");
						getch();
						return;				
					}
					printf ("\n\nPassword salah, attempt tersisa : %d\nSilahkan tekan key apapun untuk lanjut...\n", 3-count);
					getch();
				}
				user = 1;
				break;
			}
			else {
				user = 0;
				temp = temp->next;
			}
		}
		if (user == 0){
			printf ("\n\nUsername tidak tersimpan pada database, Silahkan tekan key apapun untuk lanjut...\n");
			getch();
			return;
		}
	}
	printf("\n\nLOGIN SUKSES\n");
	printf("Silahkan tekan key apapun untuk lanjut...\n");
	getch();
	system("cls");
	
	int menu = -1;
		while (menu != 0){
		printf ("================== APLIKASI BOBOSEHAT ==================\n\n");
		printf("                ------ MENU PENGGUNA ------\n");
		printf("                   [1] Bagaimana tidurmu?\n");
		printf("                   [2] Lihat jam tidur!\n");
		printf("                   [0] Keluar\n");
		printf("                   Input : ");
		scanf("%d", &menu);
		
		switch(menu){
			case 1:{
				jam_tidur(*head, username);
				break;
			}
			case 2:{
				data_tidur(*head, username);
				ratarata_tidur(head, tail, username);
				break;
			}
		}
		}
}

void jam_tidur(userptr head, char username[20]){
	i = n;
	system("cls");
	printf("Halo %s!\n", username);
	printf("Yuk! Masukkan jadwal tidur kamu dibawah ini!\n\n");
	printf("Contoh input: 23.59\n");
	printf("Gunakan format waktu 24 jam ya!\n");
	printf("Jangan lupa untuk menggunakan titik diantara jam dan menit!\n");
	for(j = 1; j<=7; j++){
		printf("\n--- %s ---\n", display_hari[j]);
		printf("Jam Tidur\t: ");
		scanf("%d.%d", &data[i].jam_tidur[j], &data[i].menit_tidur[j]);
		printf("Jam Bangun\t: ");
		scanf("%d.%d", &data[i].jam_bangun[j], &data[i].menit_bangun[j]);
	}
	
	printf("\nData telah disimpan!");
	printf("\nTekan tombol apa saja untuk melanjutkan...");
	getch();
	system("cls");
}

void durasi_tidur(void){
	for(j = 1; j<=7; j++){
		if(data[i].jam_bangun[j] >= data[i].jam_tidur[j]){
			if(data[i].menit_bangun[j] >= data[i].menit_tidur[j]){
				data[i].durasi_jam[j] = data[i].jam_bangun[j] - data[i].jam_tidur[j];
				data[i].durasi_menit[j] = data[i].menit_bangun[j] - data[i].menit_tidur[j];
			}
			else if(data[i].menit_bangun[j] < data[i].menit_tidur[j]){
				data[i].durasi_jam[j] = data[i].jam_bangun[j] - data[i].jam_tidur[j] - 1;
				data[i].durasi_menit[j] = data[i].menit_bangun[j] - data[i].menit_tidur[j] + 60;	
			}
		}		
		else if(data[i].jam_bangun[j] < data[i].jam_tidur[j]){
			if(data[i].menit_bangun[j] >= data[i].menit_tidur[j]){
				data[i].durasi_jam[j] = 24 + data[i].jam_bangun[j] - data[i].jam_tidur[j];
				data[i].durasi_menit[j] = data[i].menit_bangun[j] - data[i].menit_tidur[j];
			}
			else if(data[i].menit_bangun[j] < data[i].menit_tidur[j]){
				data[i].durasi_jam[j] = 24 + data[i].jam_bangun[j] - data[i].jam_tidur[j] - 1;
				data[i].durasi_menit[j] = data[i].menit_bangun[j] - data[i].menit_tidur[j] + 60;	
			}
		}
	}
}

void keterangan(void){
	durasi_tidur();
	for(j = 1; j<=7; j++){
			if(data[i].durasi_jam[j] >= 8 && data[i].durasi_jam[j] <= 10){
				data[i].keterangan[j] = 2;
			}
			else if(data[i].durasi_jam[j] > 10){
				data[i].keterangan[j] = 3;
			}
			else {
				data[i].keterangan[j] = 1;
			}
	}
}

void data_tidur(userptr head, char username[20]){
	i = n;
	keterangan();
	system("cls");
	printf("Halo %s! ", username);
	printf("Berikut merupakan data durasi tidur kamu selama seminggu!\n\n");
	printf("+------------+--------------+--------------+---------------------+-------------+\n");
	printf("| %-10s | %-12s | %-12s | %-19s | %-11s |\n", "Hari", "Waktu Tidur", "Waktu Bangun", "Durasi", "Keterangan");
	printf("+------------+--------------+--------------+---------------------+-------------+\n");
	for (j = 1; j<=7 ; j++){	
		printf("| %-10s |    %02d.%02d     |    %02d.%02d     |  %02d Jam %02d Menit %-3s| %-11s |\n", display_hari[j], data[i].jam_tidur[j], data[i].menit_tidur[j], data[i].jam_bangun[j], data[i].menit_bangun[j], data[i].durasi_jam[j], data[i].durasi_menit[j], " ", display_keterangan[data[i].keterangan[j]]);
	}
	printf("+------------+--------------+--------------+---------------------+-------------+\n");
	
	printf("\n=====ANALISA JAM TIDUR=====\n");
	
	regularity();
	search_max();
	search_min();
	
	printf("\n\nTekan tombol apa saja untuk melanjutkan...");
	getch();
	system("cls");
}

int recursive_mean(int jam[], int N){
	if (N==1){
		return (int)jam[N];
	}else {
	return ((int)(recursive_mean(jam, N-1)*(N-1) + jam[N])/N);
	}
}

void regularity(void){
	int k, temp, N=7;
	i = n;
	int temph[7], tempm[7];
	for(j=1; j<=7; j++) {
		temph[j] = data[i].durasi_jam[j];
		tempm[j] = data[i].durasi_menit[j];
		
	}
	
	for (j=1;j<=7; j++){
		for (k = j+1; k<=7; k++){
			if (temph[j] > temph[k]){
				temp = temph[j];
				temph[j] = temph[k];
				temph[k] = temp;
				
				temp = tempm[j];
				tempm[j] = tempm[k];
				tempm[k] = temp;
			}
			else if (temph[j] == temph[k]){	
				if(tempm[j] > tempm[k]){
					temp = temph[j];
					temph[j] = temph[k];
					temph[k] = temp;
					
					temp = tempm[j];
					tempm[j] = tempm[k];
					tempm[k] = temp;		 	
				}
			}
		}		
	}
	
	temp = temph[7] - temph[1];
	printf("\nBerikut adalah distribusi jam tidur-mu! \n");
	for(j=1; j<=7; j++){
		printf("  %02d.%02d  ", temph[j], tempm[j]);
	}
	
	printf("\nKamu tidur dengan durasi rata-rata  %02d jam %02d menit",recursive_mean(temph,N),recursive_mean(tempm,N));
	rata_jam = recursive_mean(temph,N);
	rata_menit = recursive_mean(tempm,N);
	
	printf("\n\nBeda jam tidur-mu sebesar %d jam", temp);
	
	if (temp >= 4){
		printf("\nBeda jam tidur-mu terlalu jauh, coba biasakan tidur di jam tertentu!");
	} else {
		printf("\nRegularitas tidur-mu sudah baik, pertahankan!");
	}
}

void ratarata_tidur(userptr *head, userptr *tail, char username[20]){
	int ratarata_jam, ratarata_menit;
	userptr temp = *head;
	while (temp != NULL) {
		if (strcmp(temp->username, username) == 0){
			temp->ratarata_jam = rata_jam;
			temp->ratarata_menit = rata_menit;
	}
	temp = temp->next;
	}
}

void search_max(void) {
	int  maxh=0, maxm=0, maxd=0; 
	i = n;
	for (j=1;j<=7;j++){
		if (data[i].durasi_jam[j] >= maxh){
			maxh = data[i].durasi_jam[j];
			maxm = data[i].durasi_menit[j];
			maxd = j;
		}
		else if(data[i].durasi_jam[j] == maxh){
			if(data[i].durasi_menit[j] > maxm){
				maxh = data[i].durasi_jam[j];
				maxm = data[i].durasi_menit[j];
				maxd = j;				
			}
		}
	}
	printf ("\n\nKamu paling lama tidur pada hari %s dengan durasi %02d.%02d", display_hari[maxd], maxh, maxm);
}

void search_min(void){
	int minh=24, minm=60, mind=0;
	i = n;
	for (j=1;j<=7;j++){
		if (data[i].durasi_jam[j] < minh){
			minh = data[i].durasi_jam[j];
			minm = data[i].durasi_menit[j];
			mind = j;
		}
		else if(data[i].durasi_jam[j] == minh){
			if(data[i].durasi_menit[j] < minm){
				minh = data[i].durasi_jam[j];
				minm = data[i].durasi_menit[j];
				mind = j;				
			}
		}
	}
	printf ("\n\nKamu paling sedikit tidur pada hari %s dengan durasi %02d.%02d", display_hari[mind], minh, minm);
}


void admin(userptr *head, userptr *tail){
	int menu = -1, masuk = 0, count = 0, login = 0;
	int index = 0;
	char c;
	char password[20], id[20], pass[20] = "password", username[20] = "admin";
	while (menu != 0){
		while(masuk != 1){
			index = 0;
			masuk = 2;
			while(masuk == 2){
				system("cls");
				printf ("================== APLIKASI BOBOSEHAT ==================\n\n");
				printf ("                ------ MENU ADMIN ------\n\n");
				printf("Masukkan Username Admin   : ");
				scanf (" %[^\n]s", &id);		
				if (strcmp(id, username) == 0){
					break;
				}
				else{
					count++;
					if (count == 3){
						printf ("\n\nAnda terlau banyak melakukan kesalahan, Silahkan tekan key apapun untuk lanjut...\n");
						getch();
						return;				
					}					
				printf ("\n\nUsername salah, attempt tersisa : %d, Silahkan tekan key apapun untuk lanjut...\n", 3-count);
				getch();
				}
			}			
			printf("Masukkan Password Admin   : ");
			while ((c = getch()) != 13){
			    if (c == 8){
			    	if (index == 0){
				    	index = 0;
				    	continue;
					}
					else{
					   	putch('\b');
				        putch(' ');
				        putch('\b');
				        index--;
					}
			    	continue;
			    }
				else{
				    password[index++] = c;
				    putch('*'); 
				}
			}
			password[index] = '\0';
			
			if (strcmp(password, pass) == 0){
				masuk = 1;
			}
			else{
				count++;
				if (count == 3){
					printf ("\n\nAnda terlau banyak melakukan kesalahan, Silahkan tekan key apapun untuk lanjut...\n");
					getch();
					mainmenu(head, tail);				
				}
			printf ("\n\nPassword salah, attempt tersisa : %d, Silahkan tekan key apapun untuk lanjut...\n", 3-count);
			getch();
			}	
		}
		system("cls");
		printf ("================== APLIKASI BOBOSEHAT ==================\n\n");
		printf ("                ------ MENU ADMIN ------\n");
		printf ("                     [1] Daftar User\n");
		printf ("                     [2] Petunjuk\n");
		printf ("                     [0] Main Menu\n");
		printf ("                     Input : ");
		scanf ("%d", &menu);
		
		switch (menu){
			case 1:{
				system("cls");
				printuser(*head);
				submenu(head, tail);
				printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
				getch();	
				break;
			}
			case 2:{
				system("cls");
				petunjukadmin();
				printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
				getch();				
				break;
			}
			case 0:{
				system("cls");
				mainmenu(head, tail);
				break;
			}
			default:{
				printf ("\nInput yang diberikan salah! Silahkan tekan key apapun untuk lanjut...\n");
				getch();
				system("cls");
				break;
			}
		}
	}	
}

void printuser(userptr head){
	int i = 1;
	char gender[30];
	if (head == NULL) {
		printf("Kosong\n\n");
	} 
	else {
		printf ("=================== APLIKASI BOBOSEHAT ===================\n\n");
		printf ("                 ------ DAFTAR USER ------\n");
		printf ("\n+----+--------------------------------+---------+--------------+-------------------------+\n");
		printf ("| %2s | %-30s | %-7s | %-12s | %-10s  |\n", "No", "Nama", "Umur", "Gender", "Rata-Rata Durasi Tidur");
		printf ("|----+--------------------------------+---------+--------------+-------------------------|\n");	
		while (head != NULL) {
			printf ("| %-2d | %-30s | %-7d | %-12s |     %02d Jam %02d Menit     |\n", i, head->nama, head->umur, head->gender, head->ratarata_jam, head->ratarata_menit);
			head = head->next;
			i++;
		}
		printf ("+----+--------------------------------+---------+--------------+-------------------------+\n\n");
				
	}	
}

userptr swap(userptr ptr1, userptr ptr2){
    userptr temp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = temp;
    return ptr2;
}

void SortNamaUP(userptr *head, int count){
    userptr *h;
    int i, j, swapped;
  
    for (i = 0; i <= count; i++) {
        h = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++) {
  
            userptr p1 = *h;
            userptr p2 = p1->next;
            if (strcmp(p1->nama, p2->nama) > 0) {
                *h = swap(p1, p2);
                swapped = 1;
            }
  
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void SortNamaDOWN(userptr *head, int count){
    userptr *h;
    int i, j, swapped;
  
    for (i = 0; i <= count; i++) {
        h = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++) {
  
            userptr p1 = *h;
            userptr p2 = p1->next;
            if (strcmp(p1->nama, p2->nama) < 0) {
                *h = swap(p1, p2);
                swapped = 1;
            }
  
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void SortUmurUP(userptr *head, int count){
    userptr *h;
    int i, j, swapped;
  
    for (i = 0; i <= count; i++) {
        h = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++) {
  
            userptr p1 = *h;
            userptr p2 = p1->next;
            if (p1->umur > p2->umur) {
                *h = swap(p1, p2);
                swapped = 1;
            }
  
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void SortUmurDOWN(userptr *head, int count){
    userptr *h;
    int i, j, swapped;
  
    for (i = 0; i <= count; i++) {
        h = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++) {
  
            userptr p1 = *h;
            userptr p2 = p1->next;
            if (p1->umur < p2->umur) {
                *h = swap(p1, p2);
                swapped = 1;
            }
  
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void SortGenderUP(userptr *head, int count){
    userptr *h;
    int i, j, swapped;
  
    for (i = 0; i <= count; i++) {
        h = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++) {
  
            userptr p1 = *h;
            userptr p2 = p1->next;
            if (strcmp(p1->gender, p2->gender) > 0) {
                *h = swap(p1, p2);
                swapped = 1;
            }
  
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void SortGenderDOWN(userptr *head, int count){
    userptr *h;
    int i, j, swapped;
  
    for (i = 0; i <= count; i++) {
        h = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++) {
  
            userptr p1 = *h;
            userptr p2 = p1->next;
            if (strcmp(p1->gender, p2->gender) < 0) {
                *h = swap(p1, p2);
                swapped = 1;
            }
  
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void submenu(userptr *head, userptr *tail){
	int sub, subsub, i = 1, d, j;
	char a[30], b[30], c[30], cari[30];
	userptr h;
	printf ("[1] Sorting Ascending\n");
	printf ("[2] Sorting Descending\n");	
	printf ("[3] Searching\n");
	printf ("[0] Keluar\n");
	printf ("Input : ");
	scanf("%d", &sub);
	switch (sub){
		case 1:{
			listdata();
			scanf("%d", &subsub);
			switch (subsub){
				case 1:{
					SortNamaUP(head, terdaftar);
					break;
				}
				case 2:{
					SortUmurUP(head, terdaftar);
					break;
				}
				case 3:{
					SortGenderUP(head, terdaftar);
					break;
				}
				default:{
					printf ("\nInput yang diberikan salah! Silahkan tekan key apapun untuk lanjut...\n");
					getch();
					system("cls");
					break;
				}				
			}
			break;
		}
		case 2:{
			listdata();
			scanf("%d", &subsub);
			switch (subsub){
				case 1:{
					SortNamaDOWN(head, terdaftar);
					break;
				}
				case 2:{
					SortUmurDOWN(head, terdaftar);
					break;
				}
				case 3:{
					SortGenderDOWN(head, terdaftar);
					break;
				}
				default:{
					printf ("\nInput yang diberikan salah! Silahkan tekan key apapun untuk lanjut...\n");
					getch();
					system("cls");
					break;
				}				
			}
			break;
		}
		case 3:{
			listsearch();
			scanf("%d", &subsub);
			switch (subsub){
				case 1:{
					h = *head;
					printf ("\nMasukan Nama: ");
                    scanf (" %[^\n]s", &c);
                    
                    printf ("\n+----+--------------------------------+---------+--------------+-------------------------+\n");
					printf ("| %2s | %-30s | %-7s | %-12s | %-10s  |\n", "No", "Nama", "Umur", "Gender", "Rata-Rata Durasi Tidur");
					printf ("|----+--------------------------------+---------+--------------+-------------------------|\n");
		
				    while (h != NULL){
				    	for(j = 0; j < 30; j++){
				    		a[j] = tolower(h->nama[j]);
							b[j] = tolower(c[j]);				    		
						}	
						if (strstr(a, b)){	
							printf ("| %-2d | %-30s | %-7d | %-12s |     %02d Jam %02d Menit     |\n", i, h->nama, h->umur, h->gender, h->ratarata_jam, h->ratarata_menit);
							i++;
					    }
					    h = h->next;
				    }
				    printf ("+----+--------------------------------+---------+--------------+-------------------------+\n");
				    
				    printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
					getch();
				    break;
				}
				
				case 2:{
					h = *head;
					printf ("\nMasukan Umur: ");
                    scanf ("%d", &d);
					printf ("\n+----+--------------------------------+---------+--------------+-------------------------+\n");
					printf ("| %2s | %-30s | %-7s | %-12s | %-10s  |\n", "No", "Nama", "Umur", "Gender", "Rata-Rata Durasi Tidur");
					printf ("|----+--------------------------------+---------+--------------+-------------------------|\n");
					while (h != NULL){
						if ((h->umur == d)){	
							printf ("| %-2d | %-30s | %-7d | %-12s |     %02d Jam %02d Menit     |\n", i, h->nama, h->umur, h->gender, h->ratarata_jam, h->ratarata_menit);
							i++;
					    }
					    h = h->next;
				    }
				    printf ("+----+--------------------------------+---------+--------------+-------------------------+\n");
					printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
					getch();
				    break;
				}
				
				case 3:{
					h = *head;
					printf ("\nMasukan Gender: ");
                    scanf (" %[^\n]s", &c);
					printf ("\n+----+--------------------------------+---------+--------------+-------------------------+\n");
					printf ("| %2s | %-30s | %-7s | %-12s | %-10s  |\n", "No", "Nama", "Umur", "Gender", "Rata-Rata Durasi Tidur");
					printf ("|----+--------------------------------+---------+--------------+-------------------------|\n");
					while (h != NULL){
				    	for(j = 0; j < 30; j++){
				    		a[j] = tolower(h->gender[j]);
							b[j] = tolower(c[j]);				    		
						}
						if (strstr(a, b)){		
							printf ("| %-2d | %-30s | %-7d | %-12s |     %02d Jam %02d Menit     |\n", i, h->nama, h->umur, h->gender, h->ratarata_jam, h->ratarata_menit);
							i++;
					    }
					    h = h->next;
				    }
				    printf ("+----+--------------------------------+---------+--------------+-------------------------+\n");
					printf ("\nSilahkan tekan key apapun untuk lanjut...\n");
					getch();
				    break;
				}
	
				case 0:{			
					return;
				}
				
				default:{
					printf ("\nInput yang diberikan salah! Silahkan tekan key apapun untuk lanjut...\n");
					getch();
					system("cls");					
					admin(head, tail);
				}
			}
			break;
		}
		case 0:{			
			return;
		}
	}
	system("cls");
	printuser(*head);
	submenu(head, tail);
}

void listdata(){
	printf ("\nSort by :\n");
	printf ("[1] Nama\n");
	printf ("[2] Umur\n");	
	printf ("[3] Gender\n");
	printf ("[0] Keluar\n");
	printf ("Input : ");	
}

void listsearch(){
	printf ("\nSearch by :\n");
	printf ("[1] Nama\n");
	printf ("[2] Umur\n");	
	printf ("[3] Gender\n");
	printf ("[0] Keluar\n");
	printf ("Input : ");
}

void petunjukuser(){
	system("cls");
	printf ("================ APLIKASI BOBOSEHAT ================\n\n");
	printf ("              ------ PETUNJUK ------\n");
	printf ("Program digunakan untuk mengevaluasi kualitas tidur anda  \n\n");
	printf ("Sebagai User : \n");
	printf ("[1] Masuk ke menu Sign Up untuk membuat akun pertama kali dengan memasukkan biodata anda\n");
	printf ("[2] Masuk ke menu Log In untuk memasukkan username dan password akun yang telah dibuat \n");
	printf ("[3] Jika Log In berhasil, anda akan diarahkan pada menu useran ketua \n");
	printf ("[4] Silakan masukkan waktu tidur anda selama 7 hari kebelakang \n");
	printf ("[5] Setelah itu, anda akan mendapatkan analisis kualitas tidur anda \n");
}

void petunjukadmin(){
	system("cls");
	printf ("================ APLIKASI BOBOSEHAT ================\n\n");
	printf ("              ------ PETUNJUK ------\n");
	printf ("Program digunakan untuk mengevaluasi kualitas tidur anda  \n\n");
	printf ("Sebagai Admin : \n");
	printf ("[1] Masuk ke menu Daftar User untuk melihat daftar user yang sudah melakukan Sign Up\n");
	printf ("[2] Anda dapat melakukan sorting dan searching setiap data daftar user\n");
}

void inisialisasi(userptr *head, userptr *tail){
	userptr newPtr1, newPtr2, newPtr3, newPtr4, newPtr5;
	userptr newPtr6, newPtr7, newPtr8, newPtr9, newPtr10;
	newPtr1 = malloc(sizeof(User));
	newPtr2 = malloc(sizeof(User)); 
	newPtr3 = malloc(sizeof(User)); 
	newPtr4 = malloc(sizeof(User)); 
	newPtr5 = malloc(sizeof(User)); 
	newPtr6 = malloc(sizeof(User));
	newPtr7 = malloc(sizeof(User)); 
	newPtr8 = malloc(sizeof(User)); 
	newPtr9 = malloc(sizeof(User)); 
	newPtr10 = malloc(sizeof(User));                      

	strcpy(newPtr1->username, "jordan.nguyen");
	strcpy(newPtr1->password, "jordan");
	strcpy(newPtr1->nama, "Jordan Nguyen");
	newPtr1->umur = 13;
	strcpy(newPtr1->gender, "Laki-Laki");
	newPtr1->ratarata_jam = 8;
	newPtr1->ratarata_menit = 12;
	newPtr1->next = NULL;
	
	if (*head == NULL){
		*head = newPtr1;			
	}
	else{
		(*tail)->next = newPtr1;
	}
	*tail = newPtr1; 
	
	strcpy(newPtr2->username, "owen.adams");
	strcpy(newPtr2->password, "owen");
	strcpy(newPtr2->nama, "Owen Adams");
	newPtr2->umur = 20;
	strcpy(newPtr2->gender, "Laki-Laki");
	newPtr2->ratarata_jam = 10;
	newPtr2->ratarata_menit = 13;
	newPtr2->next = NULL;	
	(*tail)->next = newPtr2;
	*tail = newPtr2; 

	strcpy(newPtr3->username, "george.lewis");
	strcpy(newPtr3->password, "george");
	strcpy(newPtr3->nama, "George Lewis");
	newPtr3->umur = 19;
	strcpy(newPtr3->gender, "Laki-Laki");
	newPtr3->ratarata_jam = 9;
	newPtr3->ratarata_menit = 20;
	newPtr3->next = NULL;	
	(*tail)->next = newPtr3;
	*tail = newPtr3; 
	
	strcpy(newPtr4->username, "mila.williams");
	strcpy(newPtr4->password, "mila");
	strcpy(newPtr4->nama, "Mila Williams");
	newPtr4->umur = 21;
	strcpy(newPtr4->gender, "Perempuan");
	newPtr4->ratarata_jam = 8;
	newPtr4->ratarata_menit = 34;
	newPtr4->next = NULL;	
	(*tail)->next = newPtr4;
	*tail = newPtr4;
	
	strcpy(newPtr5->username, "liam.jackson");
	strcpy(newPtr5->password, "liam");
	strcpy(newPtr5->nama, "Liam Jackson");
	newPtr5->umur = 18;
	strcpy(newPtr5->gender, "Laki-Laki");
	newPtr5->ratarata_jam = 10;
	newPtr5->ratarata_menit = 54;
	newPtr5->next = NULL;	
	(*tail)->next = newPtr5;
	*tail = newPtr5;
	
	strcpy(newPtr6->username, "harriet.edwards");
	strcpy(newPtr6->password, "harriet");
	strcpy(newPtr6->nama, "Harriet Edwards");
	newPtr6->umur = 18;
	strcpy(newPtr6->gender, "Laki-Laki");
	newPtr6->ratarata_jam = 7;
	newPtr6->ratarata_menit = 13;
	newPtr6->next = NULL;	
	(*tail)->next = newPtr6;
	*tail = newPtr6;
	
	strcpy(newPtr7->username, "eleanor.graham");
	strcpy(newPtr7->password, "eleanor");
	strcpy(newPtr7->nama, "Eleanor Graham");
	newPtr7->umur = 21;
	strcpy(newPtr7->gender, "Perempuan");
	newPtr7->ratarata_jam = 9;
	newPtr7->ratarata_menit = 16;
	newPtr7->next = NULL;	
	(*tail)->next = newPtr7;
	*tail = newPtr7; 
	
	strcpy(newPtr8->username, "azzam.muhammadi");
	strcpy(newPtr8->password, "azzam");
	strcpy(newPtr8->nama, "Azzam Muhammadi Rizqun Karima");
	newPtr8->umur = 18;
	strcpy(newPtr8->gender, "Laki-Laki");
	newPtr8->ratarata_jam = 10;
	newPtr8->ratarata_menit = 34;
	newPtr8->next = NULL;
	(*tail)->next = newPtr8;
	*tail = newPtr8; 
	
	strcpy(newPtr9->username, "kirana.rashifa");
	strcpy(newPtr9->password, "kirana");
	strcpy(newPtr9->nama, "Kirana Rashifa Zahra");
	newPtr9->umur = 20;
	strcpy(newPtr9->gender, "Perempuan");
	newPtr9->ratarata_jam = 9;
	newPtr9->ratarata_menit = 13;
	newPtr9->next = NULL;
	(*tail)->next = newPtr9;
	*tail = newPtr9; 
	
	strcpy(newPtr10->username, "humam.nauvally");
	strcpy(newPtr10->password, "humam");
	strcpy(newPtr10->nama, "Humam Nauvally Hammam");
	newPtr10->umur = 19;
	strcpy(newPtr10->gender, "Laki-Laki");
	newPtr10->ratarata_jam = 6;
	newPtr10->ratarata_menit = 10;
	newPtr10->next = NULL;
	(*tail)->next = newPtr10;
	*tail = newPtr10;
}

void konversigender(int key, char konversi[]){
	if (key == 1){
		strcpy(konversi, "Perempuan");
	}
	else if (key == 2){
		strcpy(konversi, "Laki-Laki");
	}
}

void writeLinkedList(char filename[], userptr *head){
    userptr temp;
    temp = malloc(sizeof(User));
    temp = *head;
    
    FILE* file;
    file = fopen (filename, "a");
    if (file == NULL){
        exit (1);
    }
    while(temp!=NULL){
    	fprintf (file, "|%-30s | %-7d | %-12s |\n", temp->nama, temp->umur, temp->gender);
        temp = temp->next;
    }
    fclose(file);   
}
