#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

static int patron(char *str,char *pat) {
  while(*str != 0 && *pat !=0){
    if (*str != *pat){
      return 7;
    }
    else if (*str == *pat) { 
      str++;
      pat++;
    }
  } 
  return 0;
}

void eliminar(char *str, char *pat) {
  char *punteroi = str; 
  int largo = strlen(pat);

  while (*punteroi) { 
    if (*punteroi == *pat && strncmp(punteroi, pat, largo) == 0 ) { // si encontramos el patron
        punteroi = punteroi + largo; //lo dejamos en el string y seguimos 
    } 
    else { 
      *str++ = *punteroi++; // si no hacemos el switch entre los contenidos 
    }
  }
  *str = '\0'; // al final corto desde donde termino el puntero del str
}


char *eliminados(char *str, char *pat) {
  size_t largo = strlen(str);
  char *copia = malloc(largo+1) ;
  strcpy(copia, str);
  eliminar(copia, pat);
  char *pcopia = copia;
  while (*pcopia != '\0') {
    pcopia++;
  }
  *pcopia = '\0';
  size_t largocopia = strlen(copia);
  char *resultado = malloc(largocopia+1);
  strcpy(resultado, copia);
  char *presultado = resultado;
  while (*presultado != '\0') {
    presultado++;
  }
  *presultado = '\0';
  free(copia);
  return resultado;
}