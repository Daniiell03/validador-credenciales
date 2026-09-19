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
    size_t i;
    int digito;

    /* 1. formato */
    if (!cred_formato_valido(uid)) {
        return CRED_ERR_FORMATO;
    }

    /* 2. checksum: el ultimo digito debe coincidir */
    digito = cred_checksum(uid);
    if (digito < 0 || uid[CRED_LONGITUD - 1u] - '0' != digito) {
        return CRED_ERR_CHECKSUM;
    }

    /* 3. lista de permitidas */
    if (permitidas == NULL) {
        return CRED_ERR_NO_AUTORIZADA;
    }
    for (i = 0u; i < n; ++i) {
        if (permitidas[i] != NULL && strcmp(uid, permitidas[i]) == 0) {
            return CRED_OK;
        }
    }
    return CRED_ERR_NO_AUTORIZADA;
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
