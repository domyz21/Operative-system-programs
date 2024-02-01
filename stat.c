#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void)
{
    struct stat s;
    
    stat("file.txt",&s); //tutte le informazioni del file li salviamo della stat
    //le syscall NON possono ritornare indirizzi di memoria (perchè sono indirizzi kernel)

    printf("%ld\n", s.st_ino); //ST_INO per prendere l'dentificativo del file

    printf("%s\n", ctime(&s.st_atime)); /* Time of last access.  */		
    printf("%s\n", ctime(&s.st_mtime)); /* Time of last modification. */
    printf("%s\n", ctime(&s.st_ctime)); /* Time of last status change.  */

    //st_dev = device code, codice device sul quale è salvato
    //st_rdev = device number, se è salvato un device (la partizione sulla quale è salvato)
    //st_ino = file serial number
    //st_mode = file mode
    //st_blksize = taglia blocco logico
    //st_blocks = taglia blocco fisico
    //st_size = è la dim del file in bytes
    //data di accesso, modifica, ultmo cambiamento di stato e creazione
    //NON ti dice il nome del file perche tu lo usi quando chiami la stat


    exit(0);
}
