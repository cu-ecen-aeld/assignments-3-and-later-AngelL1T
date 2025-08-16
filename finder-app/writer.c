#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Uso: writer <ruta_del_archivo> <cadena_a_escribir>");
        closelog();
        return 1;
    }

    const char *filepath = argv[1];
    const char *str = argv[2];

    syslog(LOG_DEBUG, "Escribiendo \"%s\" en %s", str, filepath);

    FILE *f = fopen(filepath, "w");
    if (!f) {
        syslog(LOG_ERR, "No se pudo abrir %s: %s", filepath, strerror(errno));
        closelog();
        return 1;
    }

    if (fputs(str, f) == EOF) {
        syslog(LOG_ERR, "No se pudo escribir en %s: %s", filepath, strerror(errno));
        fclose(f);
        closelog();
        return 1;
    }

    if (fclose(f) != 0) {
        syslog(LOG_ERR, "Error al cerrar %s: %s", filepath, strerror(errno));
        closelog();
        return 1;
    }

    closelog();
    return 0;
}

