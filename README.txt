
Super Mario-PRACTICA PRO2
Autor: Ignasi Albert Hohenhorst
Asignatura: Programación 2 (FIB)

==================================
Descripción
==================================
En los ficheros adjuntos se encuentra el videojuego de Mario, dividido en clases, con dos ficheros 
para cada clase (.hh, .cc). Todos los métodos implementados en las clases han sido documentados en
los ficheros .hh en formato doxygen. 

==================================
Clases Nuevas(5)
==================================
- Enemy: representa los enemigos en el juego.
- Checkpoint: punto de control para guardar la posicion del Mario tras su muerte.
- MessageQueue: gestiona los mensajes de salida de información en una cola de forma ordenada.
- Coin: gestiona las monedas recogibles.
- Finder: optimiza la aparicion de plataformas, monedas y enemigos en el juego

==================================
Contenedores STL Utilizados (5)
==================================
- List: para almacenar a los enemigos y las monedas (clase enemy y coin).
- Stack: para gestionar las vidas que tiene el Mario (usada en game).
- Árbol binario: para almacenar y buscar el punto de control más cercano (checkpoint).
- Queue: para gestionar los mensajes imprimidos en pantalla (clase message).
- Set: para gestionar el uso del finder.

==================================
Jugabilidad
==================================
-Al iniciar el juego se debe seleccionar la cantidad de enemigos deseada.
-Si Mario toca un punto de control(banderita roja), la siguiente vez que muera, reaparecerá en ese punto de control.
-Mario parte de 3 vidas, al tocar un enemigo, o caer de una plataforma, se le resta una vida y vuelve al ultimo punto de control.
-Hay monedas por el mapa, cuantas más recoja Mario, más puntos gana
-Tanto la entrada como la salida de informacion se gestiona por terminal.

==================================
Controles
==================================
- Flechas (left, right): mover al personaje horizontalmente.
- Espacio: salto vertical.
-'P': pausar el juego.
-'Esc': cerrar el juego


==================================
Casos de prueba interesantes / Comportamiento esperado
==================================
Probar con 40000 enemigos o plataformas. Se espera que  el finder haga su función.
Probar con un numero negativo de enemigos. Se espera que aparezcan 0 enemigos.

