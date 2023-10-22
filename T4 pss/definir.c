#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pss.h"
//0 ejecutable
//1 nombre arch 
//2 llave
//3 definicion
int main(int argc, char *argv[]) { 
  
  //error si no tiene la ctda de argumentos necesarios
  if(argc!=4){
    fprintf(stderr,"Uso: ./definir <diccionario> <llave> <definicion>\n");
    return 1;
  }


  //abrimos en r+ para escribir y leer
  FILE *f=fopen(argv[1], "r+");

  //caso error de archivo vacío
  if(f==NULL){
    perror(argv[1]);
    return 1;
  }


  //calculo de tamaño de lineas
  int tamlinea= 81; //80 mas fin de linea? tamaño de cada linea
  fseek(f,0,SEEK_END); 
  int tamarch = ftell(f); //tamaño del archivo en bytes 
  int cantlineas= tamarch/tamlinea; //cantidad de lineas en el archivo

  long long numllave= hash_string(argv[2]) % cantlineas; //con la indicacion saco el numero de llave por revisar 
  char buff[tamlinea]; //hago un buffer con el tamaño de linea para guardar lo q leamos 

  //hacemos un for desde la linea que da el hash hasta que acabe el diccionario 
  for(int i = numllave; i <= cantlineas; i++){
    //leemos la linea
    fseek(f, i*tamlinea, SEEK_SET); //buscamos el inicio de la linea que queremos 
    fread(buff, 1, 81, f); //leo la linea, guarda en buffer y mueve el puntero f
    fseek(f, i*tamlinea, SEEK_SET); //volvemos a dejar el puntero en el inicio de la linea 

    char *c= buff; //puntero al inicio de lo leido 

    //chequeamos si podemos escribir primero 
    if(*c == ' '){ //si esta vacio
      fputs(argv[2], f); //ponemos la llave en la linea y mueve el puntero al espacio sgte 
      fputc(':', f); //dos puntos
      fputs(argv[3], f); //ponemos la definicion 
      fclose(f); //cerramos archivo 
      return 0; //terminamos se puso la definicion 
      break;
    }

    else{ // si no esta vacia vemos si esta la definicion u otra cosa nomas 
      char *p = buff;  //otro puntero al inicio de lo leido 
      //vemos el tamaño de la llave 
      int tamllave=0; 
      while(*p!=':'){
        tamllave++;
        p++;
      }
      //comparamos los caracteres de la llave con lo leido en la linea 
      if((strncmp(buff, argv[2], tamllave))==0){ //si la llave esta escrita ya 
        fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", argv[2]); //mandamos el error 
        return 1;
      } 

    }
    //en el caso de que sea una linea ocupada por otra definicion continua el for nomas 
  }



  //ahora continuamos la busqueda del inicio hasta la linea q revisamos al inicio del otro for, se hace el mismo proceso
  for(int i = 0; i < numllave; i++){ //for para recorrer lineas archivo 
    fseek(f, i*tamlinea, SEEK_SET); //buscamos la linea 
    fread(buff, 1, 81, f); //leo la linea guarda en buffer 
    fseek(f, i*tamlinea, SEEK_SET); //volvemos a dejar el puntero en la linea

    char *c= buff; //puntero al inicio de la linea

    //nuevamente chequeamos en el caso si podemos escribir
    if(*c == ' '){ //si esta vacio
      fputs(argv[2], f); //ponemos la llave en la linea 
      fputc(':', f); //dos puntos
      fputs(argv[3], f); //ponemos la definicion 
      fclose(f); //cerramos archivo 
      return 0; //terminamos 
    }

    else{
      char *p= buff;  
      int tamllave=0;
      while(*p!=':'){
        tamllave++;
        p++;
      }
      if((strncmp(buff, argv[2], tamllave))==0){ //caso donde la llave ya esta 
        fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", argv[2]);
        return 1;
      } 
    }
  }
  //si sale de los for el archivo estaba lleno
  fprintf(stderr, "%s: el diccionario esta lleno\n", argv[1]);
  return 1;
}