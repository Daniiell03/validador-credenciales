#include "minitest.h"
#include "credencial.h"

static void test_formato_acepta_ocho_digitos(void)
{
    MT_ASSERT_EQ(cred_formato_valido("12345678"), 1);
}

static void test_formato_rechaza_corta(void)
{
    MT_ASSERT_EQ(cred_formato_valido("1234567"), 0);
}

static void test_formato_rechaza_larga(void)
{
    MT_ASSERT_EQ(cred_formato_valido("123456789"), 0);
}

static void test_formato_rechaza_letra(void)
{
    MT_ASSERT_EQ(cred_formato_valido("1234567A"), 0);
}

static void test_formato_rechaza_nulo(void)
{
    MT_ASSERT_EQ(cred_formato_valido(NULL), 0);
}

static void test_checksum_suma_modulo_diez(void)
{
    MT_ASSERT_EQ(cred_checksum("12345678"), 8);
}

static void test_checksum_suma_pequena(void)
{
    MT_ASSERT_EQ(cred_checksum("11111117"), 7);
}

static void test_checksum_rechaza_invalida(void)
{
    MT_ASSERT_EQ(cred_checksum("1234567A"), -1);
}


static const char *PERMITIDAS[] = {
    "12345678",
    "20250010"
};

static void test_autoriza_credencial_valida(void)
{
    MT_ASSERT_EQ(cred_autorizar("12345678", PERMITIDAS, 2), CRED_OK);
}

static void test_rechaza_formato_invalido(void)
{
    MT_ASSERT_EQ(cred_autorizar("1234567A", PERMITIDAS, 2),
                 CRED_ERR_FORMATO);
}

static void test_rechaza_checksum_erroneo(void)
{
    MT_ASSERT_EQ(cred_autorizar("12345670", PERMITIDAS, 2),
                 CRED_ERR_CHECKSUM);
}

static void test_rechaza_no_autorizada(void)
{
    MT_ASSERT_EQ(cred_autorizar("11111117", PERMITIDAS, 2),
                 CRED_ERR_NO_AUTORIZADA);
}

static void test_formato_gana_al_orden(void)
{
    MT_ASSERT_EQ(cred_autorizar("ABC", PERMITIDAS, 2),
                 CRED_ERR_FORMATO);
}

static void test_lista_vacia_no_autoriza(void)
{
    MT_ASSERT_EQ(cred_autorizar("12345678", NULL, 0),
                 CRED_ERR_NO_AUTORIZADA);
}


int main(void)
{
    printf("Pruebas del validador de credenciales\n");
    printf("-------------------------------------\n");

    MT_PRUEBA(test_autoriza_credencial_valida);
    MT_PRUEBA(test_rechaza_formato_invalido);
    MT_PRUEBA(test_rechaza_checksum_erroneo);
    MT_PRUEBA(test_rechaza_no_autorizada);
    MT_PRUEBA(test_formato_gana_al_orden);
    MT_PRUEBA(test_lista_vacia_no_autoriza);

    return mt_informe("build/reports/credencial.xml", "credencial");
}
