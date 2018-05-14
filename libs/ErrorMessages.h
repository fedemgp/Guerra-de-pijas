/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#ifndef __ERROR_MESSAGES_H__
#define __ERROR_MESSAGES_H__

#define ERR_MSG_SOCKET_INVALID_PORT "Puerto %s inválido: %s."
#define ERR_MSG_SOCKET_BINDING "No se pudo bindear el socket al puerto %s:"
#define ERR_MSG_SOCKET_LISTEN                         \
    "No se pudo establecer la cantidad de conexiones" \
    "en espera: %s."
#define ERR_MSG_SOCKET_INVALID_HOST_OR_PORT "Host %s o puerto %s inválido: %s."
#define ERR_MSG_CONNECTION_COULD_NOT_BE_STABLISHED \
    "La conexión a %s:%s no "                     \
    "pudo ser establecida."
#define ERR_MSG_SOCKET_ACCEPT "No se pudo aceptar la conexión: %s"
#define ERR_MSG_SOCKET_CLOSED "Conexión cerrada."
#define ERR_MSG_SOCKET_CLOSED_UNEXPECTLY \
    "Error: terminación inesperada al " \
    "recibir un mensaje."

#endif  //__ERROR_MESSAGES_H__
