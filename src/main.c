#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Fonksiyonlar.h"

int main (int argc, char **argv, char **envp)
{
	int komutKarakterSayisi = 90;

	char temp[komutKarakterSayisi];
	environ=envp;
	char *komutlar[15];
	int komutSayisi;
	int durum=1;
	

	while(durum)
	{
		komutBekle();
		memset(temp, '\0',komutKarakterSayisi); //char tipinde temp dizisinin tamami bosaltildi
		fgets(temp,komutKarakterSayisi,stdin); //klavyeden okuyacagi veriyi temp dizisine aktarir.
		
		// printf("%c \n", temp[2]);
		// printf("%ld \n", strlen(temp));

		if(strlen(temp) > 80){
			printf("Hata: Komut en fazla 80 karakter olabilir\n");
			continue;
		};

		if((komutlar[0] = strtok(temp," \n\t")) == NULL) continue;
		
		komutSayisi = 1;

		if(temp[0] == ' ' || temp[0] == '\t') { //sonunda bosluk yaplacak
			printf("Hata: Komut basinda veya sonunda bosluk bulunamaz!\n");
			continue;
		}

		while((komutlar[komutSayisi] = strtok(NULL, " \n\t")) != NULL) {
			// printf("%s\n",komutlar[komutSayisi]);
			komutSayisi++;
		}

		if(komutSayisi > 10) {
			printf("Hata: Bir komut boslukla ayrilmis en fazla 10 kelimeden olusabilir!\n");
			continue;
		}
		komutlariAyir(komutlar);
	}
}
