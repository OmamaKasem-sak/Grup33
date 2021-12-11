#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

#include "Fonksiyonlar.h"

int processArray[100] = {0};

char *builtin_str[]={
	"cd",
	"exit",
	"showpid"
};

int (*builtin_func[])(char**) = {
	&cDirectory,
	&cikis,
	&showpid
};

int boyut()
{
	return sizeof(builtin_str)/sizeof(char *);
}

int cDirectory(char **komut)
{
	if (komut[1]==NULL)
	{ // cd
		// yazip 2.parametre olarak deger girilmezse
		fprintf(stderr,"Dizin belirtilmedi. \"cd\"\n");
	}
	else // 2. parametre bos degilse
	{
		if (chdir(komut[1])!=0) //2.parametre 0'dan farkliysa
		{
			perror("Hata");
		}
	}
	return 1;
}

int cikis(char **komut)
{
	int durum;
	while (!waitpid(-1,&durum,WNOHANG)){}
	exit(0);
}

int showpid(char **komut)
{
	int i = 0;
	while(processArray[i] != 0) {
		printf("%d\n", processArray[i]);
		i++;
	}
}

int komutlariAyir(char * komut[])
{
	int pipeIn = -1;
	int bagKo = -1;
	int standartOut;
	int durum;
	int arkapCalis = 0;
	int i=0,j=0,k;
	int file;
	char *komutlar[256];


	while(komut[j] != NULL)
	{
		if ((strcmp(komut[j],"|") == 0) || (strcmp(komut[j],">") == 0) || (strcmp(komut[j],"<") == 0) || (strcmp(komut[j],"&") == 0))
		{
			break;
		}
		komutlar[j] = komut[j];
		j++;
	}

	// printf("%s\n",komut[0]); //komut[j] kelimeleri tutuyor. 0 ilk kelime

	komutlar[j]=NULL;

	// printf("%s\n%d\n",komutlar[j],j);

	int m;
	if (komut[0] == NULL)
	{
		printf ("Bos komut.\n");
		return 1; // Eger bos komut gönderildiyse return 1 döner.
	}

	// printf("%d\n",boyut());

	for (m = 0 ; m < boyut() ; m++)
	{
		// cd: m=0, exit: m=1, showpid: m=2
		// Eðer cd,showpid veya exit komutu girildiyse ilgili iþlemi yapar ve fonksiyondan çikar.

		if (strcmp(komut[0],builtin_str[m])==0)
		{
			(*builtin_func[m])(komut);
			return 1;
		}
	}
	
	komutlar[i]==NULL;
	calistir(komutlar, arkapCalis);

	return 1;
}

int calistir(char **komut,int arkapCalis)
{
	if (arkapCalis==0) //arkaplan komutu değilse..
	{
		int pid;
		int durum;
		pid=fork();

		for(int i = 0; i < 100; i++){
			if(processArray[i] == 0){
				processArray[i] = pid;
				break;
			}
		}

		if (pid == 0) //child processteyken.
		{
			if (execvp(komut[0],komut) == -1)
			{
				printf("Hata: Komut bulunamadı.\n");
				kill(getpid(),SIGTERM);
			}
		}

		else if (pid < 0)
		{
			perror("Hata: Process olusturulamadi.\n");
		}

		else //child process bitene kadar bekle.
		{
			waitpid(pid, NULL, 0);
		}

		return 1;
	}

	return 1;
}

void komutBekle()
{
	char hostn[1204] = "";
	gethostname(hostn, sizeof(hostn));
	printf(MAG "%s/: " RESET YEL "sau > " RESET, getcwd(bulunanDizin, 1024));
}