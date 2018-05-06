 # cliente
   * El cliente va a tener hilos distintos para enviar y recibir
   * paquete individual, con un header con id de acción.
   * camara independiente del servidor (se actualiza localmente)
   * hardcodear al principio, aislando modulos (sockets, threads, editor) para facilitar el debuggeo
 # server
   *  un hilo por sala, y cada sala tiene 2n threads (con n clientes, un thread para enviar y otro para recibir)
 # framework
   * usar sdl
 # archivos
   * se patea hacia mas adelante la configuración por archivos, y el editor
# Preguntar a martin
   * tema de protocolo, envio cada n tiempo el estado del worm (moviendo a la derecha, saltando, etc) o enviar el comienzo y el fin de la acción.