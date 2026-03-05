/**
 * @file    app_netxduo_status.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement callbacks from the NetXDuo stack.
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

// Just a quick logger config
#define LOG_MODULE "NETX_STATUS"

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_netxduo_status.h"

// Local libraries
#include "logger.h"
#include "nx_api.h"

// ======================================================================
//                              VARIABLES
// ======================================================================

extern NX_IP ip;
extern NX_PACKET_POOL pool;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

VOID telnet_new_connection(NX_TELNET_SERVER *server_ptr, UINT logical_connection) {
    NX_PACKET *response_packet;

    // On alloue un paquet pour envoyer le message de bienvenue
    nx_packet_allocate(
        &pool, // Votre Packet Pool global
        &response_packet,
        NX_TCP_PACKET,
        NX_NO_WAIT);

    // On écrit le prompt
    nx_packet_data_append(
        response_packet,
        "Welcome to EtherBench CLI!\r\nEtherBench> ",
        38,
        &pool,
        NX_NO_WAIT);

    // On envoie le paquet au client
    nx_telnet_server_packet_send(
        server_ptr, logical_connection, response_packet, NX_WAIT_FOREVER);
}

void telnet_data_in(
    NX_TELNET_SERVER *server_ptr, UINT logical_connection, NX_PACKET *packet_ptr) {
    /* * 1. Astuce Zero-Copy : on ajoute le '\0' terminal.
     */
    packet_ptr->nx_packet_append_ptr[0] = '\0';

    char *cmd_string = (char *)packet_ptr->nx_packet_prepend_ptr;
    LOG("Command received: %s", cmd_string);

    /* * 2. On envoie cmd_string à execute_scpi_string() ou au parseur gperf !
     * ...
     */

    /*
     * 3. On libère TOUJOURS le paquet reçu pour ne pas vider le pool.
     */
    nx_packet_release(packet_ptr);

    /*
     * 4. (Optionnel) On renvoie le prompt "EtherBench> " pour la ligne suivante
     * via un nx_telnet_server_packet_send() comme dans la connexion.
     */
}

void telnet_close_connection(NX_TELNET_SERVER *server_ptr, UINT logical_connection) {
    LOG("Telnet client disconnected.");
    // Nettoyage si nécessaire (arrêt d'une séquence de test en cours, etc.)
}
