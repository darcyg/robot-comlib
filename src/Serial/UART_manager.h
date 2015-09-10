/*
 * UART_manager.h
 *
 *  Created on: 13 avr. 2015
 *      Author: ethel
 */

#ifndef UART_MANAGER_H
#define UART_MANAGER_H

#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include <stdlib.h>
#include "stdarg.h"
#include <termios.h>
#include "UART_buffer.h"
#include "UART_trame.h"

#define TAILLEMAX_DATA 255
#define TAILLEMAX_TRAME TAILLEMAX_DATA+4


/*cette structure sera envoyée à server_run() dans
 * sa boucle while(1)
 *
 */
//TODO faire une fonction pour initialiser cette structure
typedef struct UART_s{
	int uartFD; //File descriptor de l'UART
	UART_BUFFER Txbuffer;
	UART_BUFFER Rxbuffer;
	uint8_t Tx[TAILLEMAX_TRAME];
	uint8_t Rx[TAILLEMAX_TRAME];
}UART_s;



/*UART_Message
 *Trame d'un message.
 */
typedef struct UART_Message{
	uint8_t Start;
	uint8_t Slot_adress;
	uint8_t dlc;//dlc: data length code taille des donnees (de 0 a 8 octets inclus)
	uint8_t Datas[TAILLEMAX_DATA];
	uint8_t Checksum;
	uint8_t Stop;
}UART_Message;

/* UART_compress(UART_Message *msg)
 * Cette fonction permet de creer une trame de taille optimisee par rapport au nombre
 * de données que l'on souhaite envoyer.*/
void UART_compress(UART_Message *msg);

/*UART_send(UART_Message *msg)
 *cette fonction prend une structure de message
 *et la transforme en tableau pour pouvoir ensuite être
 *traitée par les fonction write() et read()
 */
void UART_send(UART_Message *msg);

/*UART_receive(UART_Message *msg)
 * cette fonction va stocker dans un tableau "TRAME" les données arrivant par le buffer
 */
void UART_receive();

/* UART_print(UART_Message *msg)
 * Cette fonction affichera le message sur la sortie standard,
 * utile pour le debug.
 */
void UART_print(UART_Message *msg);
//Todo verifier la pertinence de mes arguments pour ces fonctions.
void UART_traitement();
void UART_stockerDatas(UART_Message *msg);


/*UART_init(char * device, int Baud_rate)
 *Initialise la liaison serie.
 */
void UART_init(char * device);
uint8_t UART_checksum(uint8_t tab[TAILLEMAX_TRAME]);
int UART_recopie();

void UART_initMessage(UART_Message *msg);

#endif /* UART_MANAGER_H */
