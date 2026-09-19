#include "credencial.h"
#include <stddef.h>
#include <string.h>

int cred_formato_valido(const char *uid)
{
    size_t i;

    if (uid == NULL) {
        return 0;
    }
    if (strlen(uid) != CRED_LONGITUD) {
        return 0;
    }
    for (i = 0u; i < CRED_LONGITUD; ++i) {
        if (uid[i] < '0' || uid[i] > '9') {
            return 0;
        }
    }
    return 1;
}


int cred_checksum(const char *uid)
{
    size_t i;
    int suma = 0;

    if (!cred_formato_valido(uid)) {
        return -1;
    }
    for (i = 0u; i < CRED_LONGITUD - 1u; ++i) {
        suma += uid[i] - '0';
    }
    return suma % 10;
}

cred_resultado_t cred_autorizar(const char *uid,
                                const char *permitidas[],
                                size_t n)
{
    (void)uid;
    (void)permitidas;
    (void)n;
    return CRED_ERR_FORMATO;
}

const char *cred_nombre_resultado(cred_resultado_t r)
{
    switch (r) {
    case CRED_OK:                 return "OK";
    case CRED_ERR_FORMATO:        return "ERR_FORMATO";
    case CRED_ERR_CHECKSUM:       return "ERR_CHECKSUM";
    case CRED_ERR_NO_AUTORIZADA:  return "ERR_NO_AUTORIZADA";
    default:                      return "DESCONOCIDO";
    }
}
