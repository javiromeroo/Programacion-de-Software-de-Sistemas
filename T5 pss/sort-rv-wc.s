# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

    .file "sort-rv.s"
    .text
    .globl sort         # Se necesita para que la etiqueta sea conocida en
                        # test-sort.c
    .type sort, @function # typedef unsigned int uint;
sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // nums esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
.while_begin:           #     // del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

    # no puede alterar los registros s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 44(sp)
    # El valor de p esta temporalmente en el registro t0
    # No puede hacer mas trabajo que la comparacion (no puede usar ret)
    lw      a0,0(t0)    #     int rc= strcmp(p[0], p[1]); // registro t1
    lw      a1,4(t0)
    j .L16 #vamos a palabras 

.L16:
	lbu	a5,0(a0) #carga en a5 lo de a0 es decir *lector = *str
	beq	a5,zero,.L8 #si *lector termina saltamos a L8 
	li	a4,0 #si no entramos al loop cargamos a4 =0 en palabra
	li	a2,0 #a2=0 contador 
	li	a3,32 #espacio a3
	li	a6,1 #true de en palabra
	li	a7,0 #false de en palabra
	j	.L4 #saltamos a L4
.L14:
	beq	a4,zero,.L3 #si en palabra es falso vamos a L3
	addi	a2,a2,1 #si es verdadero avanzamos contador 
	mv	a4,a7 #y ponemos en palabra en 0
.L3:
	addi	a0,a0,1 #avanzamos el str
	lbu	a5,0(a0) #avanzamos lector 
	beq	a5,zero,.L2 #si no cumple la condicion para el loop vamos a L2, si no sigue loop 
.L4: #inicio loop 
	beq	a5,a3,.L14 # si lector es el espacio vamos a L14 
	mv	a4,a6 #si es distinto ponemos true en pálabra 
	j	.L3 #y vamos a L3
.L8:
	li	a4,0
	li	a2,0
.L2:
	add	a0,a2,a4 #guarda en a0 el resultado de contador + en palabra 
	lbu	a5,0(a1) #carga en a5 a1 es decir en *lector2= *str2
	beq	a5,zero,.L10 #si no se cumple la condicion de loop vamos a L10
	li	a4,0 #si se cummple cargamos en a4 =0 en palabra 2 
	li	a2,0 #a2= 0 contador 2
	li	a3,32 # espacio
	li	a6,1 #true en palabra
	li	a7,0 #false en palabra 
	j	.L7 #vamos a L7
.L15:
	beq	a4,zero,.L6
	addi	a2,a2,1
	mv	a4,a7
.L6:
	addi	a1,a1,1 #avanzamos str 2
	lbu	a5,0(a1) # y lector 2
	beq	a5,zero,.L5 #si no cumple la condicion de loop vamos a L5
.L7: #inicio loop
	beq	a5,a3,.L15 #si el lector es espacio vamos a L15
	mv	a4,a6 #si no en palabra true
	j	.L6 #y vamos a L6
.L10:
	li	a4,0 #si nunca entro a loop los ponemos en 0 en palabra y contador 
	li	a2,0
.L5:
	add	a2,a2,a4 #cuando termine el loop guarda en a2 la suma de palabra 2 y contador 2
	sub	a0,a0,a2 #resta los resultados y lo guarda en a0, valor retornado queda en registro a0
    mv      t1,a0       # Dejar resultado de la comparacion en t1
    j .decision

    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada
    # Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo

.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       // p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       int aux= p[0]; // a0
    lw      a1,4(t0)    #       int aux2= p[1];
    sw      a0,4(t0)    #       p[0]= aux2;
    sw      a1,0(t0)    #       p[1]= aux;
    lw      t0,48(sp)   #       p= noms;
                        #     }

.while_cond:            #     // se evalua la condicion del while
    lw      t1,52(sp)   #     // ult esta en t1
    bltu    t0,t1,.while_begin #  // Condicion del while es p<ult
			#   }
    lw      ra,60(sp)   #   // Se restaura direccion de retorno
    addi    sp,sp,64    #   // Desapila registro de activacion
    ret			# }
