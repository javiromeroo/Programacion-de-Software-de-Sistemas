#include <stdlib.h>

#include "suma.h"

Bcd sumaBcd(Bcd x, Bcd y) {
  Bcd total = 0; //para llevar el total
  Bcd carry = 0; //para llevar la reserva de la suma
  Bcd mask = 0xF; //para extraer bits

  for (int i =0; i < 64; i+=4){   //for para q recorra el bcd
    Bcd digitox = (x>>i) & mask; // extraemos el digito de x y shifteamos para tener el digito correcto
    Bcd digitoy = (y>>i) & mask; // lo mismo pero y 
    Bcd suma = digitox + digitoy + carry;  // guardamos la suma de los digitos y el carry
    if (suma > 9){ //si la suma es mayor a 9
      carry = 1; //cambiamos el carry a 1
    }
    else { //si no es mayor a 9 
      carry = 0; // dejamos el carry en 0
    }  
    Bcd sumaReal = suma - (carry * 10); //la verdadera suma depende del carry, si es 1 restamos 10 
    total = total | (sumaReal << (i)); //el total corresponde a llenar 
    //con el numero ocupando el or y shiftear para dejarlo en la posicion final correcta
  }


  if (carry == 1){ //si es uno el carry al salir es pq estamos en caso borde donde queda algo de 17 digitos
    return 0xffffffffffffffff ; //retornamos overflow
  }
  else{
    return total; //si no retornamos el total
  }
}
