#include "UART_manager.h"

static uint8_t tab_trait[TAILLEMAX_TRAME];
static UART_BUFFER buffers_slots[20];
static UART_s Uart;
int fd;
int curr_pos = 0;
uint8_t adresseDevice;

//On s'en sert pas maintenant
void UART_compress(UART_Message *msg) {
	if (msg->dlc < TAILLEMAX_TRAME - 1) {
		uint8_t dlc = msg->dlc;
		msg->Datas[dlc] = msg->Checksum;
		msg->Datas[dlc + 1] = msg->Stop;
	}
}


void UART_init(char* device) {
	//utilisation buffer génériques
	struct termios tty_attributes;
	if ((fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0) {
		fprintf(stderr, "Open error on %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		tcgetattr(fd, &tty_attributes);
		// Enable receiver
		cfmakeraw(&tty_attributes);// indispensable pour desactiver caractères de controle!!! ex 0x11
		tty_attributes.c_cflag |= CREAD;

		// 8 data bit
		tty_attributes.c_cflag |= CS8;

		// c_iflag
		// Ignore framing errors and parity errors.
		tty_attributes.c_iflag |= IGNPAR;

		// c_lflag
		// DISABLE canonical mode.
		// Disables the special characters EOF, EOL, EOL2,
		// ERASE, KILL, LNEXT, REPRINT, STATUS, and WERASE, and buffers by lines.
		tty_attributes.c_lflag &= ~(ICANON);

		// DISABLE this: Echo input characters.
		tty_attributes.c_lflag &= ~(ECHO);

		// DISABLE this: If ICANON is also set, the ERASE character erases the preceding input
		// character, and WERASE erases the preceding word.
		tty_attributes.c_lflag &= ~(ECHOE);

		// DISABLE this: When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal.
		tty_attributes.c_lflag &= ~(ISIG);

		/* polling read : Si data dispo read()
		 * retourne nb de bytes dispo ou nb bytes demandes.
		 */
		// Minimum number of characters for non-canonical read.
		tty_attributes.c_cc[VMIN] = 0;

		// Timeout in deciseconds for non-canonical read.
		tty_attributes.c_cc[VTIME] = 0;

		// Set the baud rate
		cfsetospeed(&tty_attributes, B9600);
		cfsetispeed(&tty_attributes, B9600);
		tcsetattr(fd, TCSANOW, &tty_attributes);
		sleep(1);
	}

}

void UART_initMessage(UART_Message *msg) {
	msg = (UART_Message*) malloc(sizeof(UART_Message));
}

void UART_send(UART_Message *msg) {
	int taille = (msg->dlc) + 5;
	int i;

	Uart.Tx[0]= msg->Start;
	Uart.Tx[1]=msg->Slot_adress;
	Uart.Tx[2]=msg->dlc;

	for (i = 3; i < (msg->dlc) + 3; i++) {
		Uart.Tx[i] = msg->Datas[i - 3];
	}
	Uart.Tx[(msg->dlc) + 3] = msg->Checksum;
	Uart.Tx[(msg->dlc) + 4] = msg->Stop;
	write(fd, Uart.Tx, taille);

}

void UART_receive() {

	uint8_t test[TAILLEMAX_TRAME];
	//dans un 1er temps, je lis les donnees bit a bit

	while (read(fd, &(Uart.Rx[0]), 1) != 0) {
		writeBuffer(&Uart.Rxbuffer, Uart.Rx, 1);
	}
	UART_traitement();

	int j = readBuffer(&buffers_slots[adresseDevice], test, 255);// si je met l'adresse en dur ça marche
	int k;
	printf("datas --> slot d'adresse : %x\n",adresseDevice);
	for (k=0; k < j; k++) {
		printf("%x\n", test[k]);
	}
	printf("--\n");
}


uint8_t UART_checksum(uint8_t tab[TAILLEMAX_TRAME]) {
	int i;
	uint8_t somme;
	for (i = 0; i < tab[2]; i++) {
		somme += tab[3 + i];
	}
	return somme;
}


int UART_recopie() {
	int i;
	uint8_t datas_cp[tab_trait[2]];
	for (i = 3; i < tab_trait[2] + 3; i++) {
		datas_cp[i - 3] = tab_trait[i];
	}
	//on recopie les datas dans le bon buffer à la bonne adresse TODO conventions adresses.
	writeBuffer(&buffers_slots[adresseDevice], datas_cp, tab_trait[2]);
	return 0;
}

void UART_traitement() {
	int flag_traitement = 0;
	// Uart.Rxbuffer les infos sont stockées la dedans
	// je stocke toutes les données arrivées dans un tableau pour le traitement.
	uint8_t tab[255];
	int i = readBuffer(&Uart.Rxbuffer, tab, 255);
	int j;
	for (j = 0; j < i; j++) {
		tab_trait[j] = tab[j];//j'avais tab[j]c'était ça l'erreur..
		curr_pos+=1;
	}
	//je regarde si il y a bien un start dans ma trame
	if (tab_trait[0] == 0x55) {
		flag_traitement = 1;
	} else {
		curr_pos = 0;
		for (i = 0; i < TAILLEMAX_TRAME; i++) {
			tab_trait[i] = 0;

		}
	}

	if (flag_traitement) {

		if(tab_trait[tab_trait[2] + 4] == 0xAA) {
			uint8_t chk = UART_checksum(tab_trait);

			if (tab_trait[tab_trait[2]+3]==chk) {
				adresseDevice = tab_trait[1];
				//je stocke l'adresse dans une variable globale
				UART_recopie();
				curr_pos = 0;
			}
			flag_traitement = 0;
			curr_pos =0;//ajout
			//je vide le tableau pour pouvoir commencer un nouveau traitement "propre"
			for (i = 0; i < TAILLEMAX_TRAME; i++) {
				tab_trait[i] = 0;
			}
		}
		else{
			printf("Attention : pas d'octet de stop\n");
			flag_traitement = 0;
			curr_pos =0;//ajout
			//je vide le tableau pour pouvoir commencer un nouveau traitement "propre"
			for (i = 0; i < TAILLEMAX_TRAME; i++) {
				tab_trait[i] = 0;
			}
		}
	}
}


int main() {
	UART_Message msg, msg2, msg3;

	msg.Start = 0x55;
	msg.Slot_adress = 0x02;
	msg.dlc = 2;
	msg.Datas[0] = 0x10;
	msg.Datas[1] = 0x36;
	msg.Checksum = 0x46;
	msg.Stop = 0xAA;

	msg2.Start = 0x55;
	msg2.Slot_adress = 0x03;
	msg2.dlc = 2;
	msg2.Datas[0] = 0x11;
	msg2.Datas[1] = 0x12;
	msg2.Checksum = 0x23;
	msg2.Stop = 0x33;

	msg3.Start = 0x55;
	msg3.Slot_adress = 0x04;
	msg3.dlc = 2;
	msg3.Datas[0] = 0x10;
	msg3.Datas[1] = 0x15;
	msg3.Checksum = 0x25;
	msg3.Stop = 0xAA;

	UART_init("/dev/ttyACM0");
	initUARTBuffer(&Uart.Rxbuffer);
	initUARTBuffer(&Uart.Txbuffer);
	int i;

	for(i=0;i<500;i++){
		UART_send(&msg);
		sleep(1);
		UART_receive();
		UART_send(&msg2);
		sleep(1);//on est obligé de mettre des sleep() sinon il recoit rien.
		UART_receive();
		UART_send(&msg3);
		sleep(1);
		UART_receive();
	}

	return 0;

}

