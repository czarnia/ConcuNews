# ConcuNews
Segundo TP de Técnicas de programación concurrentes I



### Corriendo el server de ejemplo

Compilar y correr con `make valgrind`, o alternativamente realizar los pasos por separado primero compilando con `make` y luego ejecutando el servidor de echo con `./echo`.

Una vez el servidor esté corriendo, se pueden realizar dos operaciones:

- Terminar la ejecución de inmediato: sencillamente enviando `SIGINT`  o `SIGTERM` al servidor mientras espera conexiones.
- Iniciar una nueva conexión (concurrentemente) mediante el comando `telnet 127.0.0.1 16000`.