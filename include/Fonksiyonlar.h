#ifndef Fonksiyonlar_h
#define Fonksiyonlar_h

#define YEL   "\x1B[33m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

static char* bulunanDizin;
extern char** environ;

int calistir(char **komut, int arkapCalis);
int komutlariAyir(char * komut[]);
void komutBekle();
int cDirectory(char **komut);
int cikis(char **komut);
int showpid(char **komut);

#endif
