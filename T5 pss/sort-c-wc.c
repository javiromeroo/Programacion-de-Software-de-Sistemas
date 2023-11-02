#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palabras(char *str, char *str2){ 
    int contador = 0; //contador para cantidad de palabras
    int c2=0;
    int enp2=0;
    int enpalabra= 0; //para saber si estabamos en una palabra 
    for(char *lector=str; *lector; lector++){ //mientras no se termine la palabra 
      if(*lector!= ' '){ //si estamos leyendo un caracter 
        enpalabra=1; //ponemos true en q estamos en una palabra 
      }
      else if(enpalabra){ //si leemos espacio y estabamos en una palabra 
          contador++; //agregamos al contador de palabras ya q significa q terminó
          enpalabra=0; //ponemos q ya no estamos en una palabra
      }
    }    
    int r1= contador + enpalabra; //retornamos la ctda de palabras mas otra palabra si estabamos en una 
    for(char *lector2=str2; *lector2; lector2++){ //mientras no se termine la palabra 
      if(*lector2!= ' '){ //si estamos leyendo un caracter 
        enp2=1; //ponemos true en q estamos en una palabra 
      }
      else if(enp2){ //si leemos espacio y estabamos en una palabra 
          c2++; //agregamos al c2 de palabras ya q significa q terminó
          enp2=0; //ponemos q ya no estamos en una palabra
      }
    }    
    int r2= c2 + enp2;
    return r1-r2;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
    int t1= (palabras(p[0], p[1])); //a0
    if (t1 <= 0) //o sea las palabras en p[0] son menos q las de p[1]
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
