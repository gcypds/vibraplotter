#include "communication_manager.h"

#ifdef DEBUG_PRINTF_OFF
char printf_buffer[255] = { 0 };
#endif

CommunicationManager::CommunicationManager(QObject *parent)
	: QObject(parent)
{
	serial = new QSerialPort(this);

	//Initialize variables
	apc_command_frame_crc = 0x00;
	apc_response_frame_payload_length = 0x00;
	apc_response_frame_payload_read = 0x00;
	protocol_frame_bytes_analyzed = 0;
	apc_response_frame_state = _NORMAL;

	bytes_to_save = NULL;

	command_buffer[APC_COMMAND_FRAME_BUFFER_SIZE] = { 0 }; // For sending
	response_buffer[APC_RESPONSE_FRAME_BUFFER_SIZE] = { 0 }; // For receiving
	package_buffer[NUMBER_OF_MAX_ADQ_CHANNELS*ADQ_SAMPLES_PER_SECOND*ADQ_BYTES_PER_SAMPLE] = { 0 }; // For package sending	
}

CommunicationManager::~CommunicationManager()
{

}

void CommunicationManager::init_protocol_frame_analyzer() {
	apc_response_frame_state = _NORMAL;
	protocol_frame_bytes_analyzed = 0;
	apc_response_frame_payload_length = 0;
	apc_response_frame_payload_read = 0;
	apc_command_frame_crc = 0;
}

int CommunicationManager::build_protocol_frame(apc_protocol_t cid, unsigned char* frame_buffer, unsigned char * payload, int payload_length) {
	int apc_command_frame_size = 0x00;
	int i;

	// Build Header
	frame_buffer[apc_command_frame_size++] = APC_FRAME_START;
	frame_buffer[apc_command_frame_size++] = APC_FRAME_COMMAND;

	// CID
	frame_buffer[apc_command_frame_size++] = cid;

	// Payload Length
	frame_buffer[apc_command_frame_size++] = (unsigned char)(payload_length >> 16);
	frame_buffer[apc_command_frame_size++] = (unsigned char)(payload_length >> 8);
	frame_buffer[apc_command_frame_size++] = (unsigned char)(payload_length);

	// Payload
	for (i = 0; i<payload_length; i++) {
		frame_buffer[apc_command_frame_size++] = payload[i];
	}

	// Compute CRC
	unsigned short apc_command_frame_crc = calculate_ccitt_crc((unsigned char *)frame_buffer, apc_command_frame_size);

	frame_buffer[apc_command_frame_size++] = (unsigned char)(apc_command_frame_crc >> 8);
	frame_buffer[apc_command_frame_size++] = (unsigned char)(apc_command_frame_crc);

	// Builder Footer
	frame_buffer[apc_command_frame_size++] = APC_FRAME_END;

	return apc_command_frame_size;
}

// Máquina de estados de comunicación.
void CommunicationManager::protocol_frame_analyzer(unsigned char data) {
	switch (apc_response_frame_state) {
	case _NORMAL:
		if (data == APC_FRAME_START) {
#ifdef DEBUG_PRINTF_ON
			//printf("\n%02X", data);
			//printf("\n.S1");
#endif

			apc_response_frame_state = _FRAME_START;
			response_buffer[protocol_frame_bytes_analyzed++] = data;
		}
		break;
	case _FRAME_START:
		if (data == APC_FRAME_RESPONSE) {
#ifdef DEBUG_PRINTF_ON
			//printf("\n%02X", data);
			//printf("\n.S2");
#endif

			apc_response_frame_state = _FRAME_TYPE;
			response_buffer[protocol_frame_bytes_analyzed++] = data;
		}
		else {
			// TODO Enviar trama de error, mal frame.
		}
		break;
	case _FRAME_TYPE:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S3");
#endif

		apc_response_frame_state = _CID;
		response_buffer[protocol_frame_bytes_analyzed++] = data;
		break;
	case _CID:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S4");
#endif

		apc_response_frame_payload_length = ((unsigned short)data) << 16;
		apc_response_frame_payload_read = 0x00;
		apc_response_frame_state = _PAYLOAD_LENGTH_H;
		response_buffer[protocol_frame_bytes_analyzed++] = data;
		break;
	case _PAYLOAD_LENGTH_H:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S5");
#endif

		apc_response_frame_payload_length += ((unsigned short)data) << 8;
		apc_response_frame_state = _PAYLOAD_LENGTH_M;
		response_buffer[protocol_frame_bytes_analyzed++] = data;

		break;
	case _PAYLOAD_LENGTH_M:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S6");
#endif

		apc_response_frame_payload_length += (unsigned short)data;

		if (apc_response_frame_payload_length == 0x00) {
			apc_response_frame_state = _PAYLOAD;
			response_buffer[protocol_frame_bytes_analyzed++] = data;
		}
		else {
			apc_response_frame_state = _PAYLOAD_LENGTH_L;
			response_buffer[protocol_frame_bytes_analyzed++] = data;
#ifdef DEBUG_PRINTF_ON
			//printf("\nP%d", apc_response_frame_payload_read);
#endif
		}

		break;
	case _PAYLOAD_LENGTH_L:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S7");
#endif

		apc_response_frame_payload_read++;
		response_buffer[protocol_frame_bytes_analyzed++] = data;

		if (apc_response_frame_payload_read == apc_response_frame_payload_length) {
			apc_response_frame_state = _PAYLOAD;
		}
		else {
#ifdef DEBUG_PRINTF_ON
			//printf("\nP%d", apc_response_frame_payload_read);
#endif
		}

		break;
	case _PAYLOAD:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S8");
#endif

		apc_command_frame_crc = ((unsigned short)data) << 8;
		apc_response_frame_state = _CRC_H;
		response_buffer[protocol_frame_bytes_analyzed++] = data;
		break;
	case _CRC_H:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S9");
#endif

		apc_command_frame_crc += (unsigned short)data;
		apc_response_frame_state = _CRC_L;
		response_buffer[protocol_frame_bytes_analyzed++] = data;
		break;
	case _CRC_L:
#ifdef DEBUG_PRINTF_ON
		//printf("\n%02X", data);
		//printf("\n.S10");
#endif

		if (data == APC_FRAME_END) {
			apc_response_frame_state = _NORMAL;
			response_buffer[protocol_frame_bytes_analyzed++] = data;

			//                QMessageBox::information(this, "Bytes analyzed", "Analyzed " + QString::number(protocol_frame_bytes_analyzed) + " bytes!");

			unsigned short received_crc = calculate_ccitt_crc(response_buffer, protocol_frame_bytes_analyzed - APC_FRAME_FOOTER_SIZE);

			if (received_crc == apc_command_frame_crc) { // CRC OK
#ifdef DEBUG_PRINTF_ON
				//printf("\nCRC OK!");
#endif
				//                    QMessageBox::information(this, "CRC", "CRC OK!");
				process_response((apc_protocol_t)response_buffer[2]);
			}
			else { // CRC FAILED
#ifdef DEBUG_PRINTF_ON
				//printf("\nCRC FAILED!");
#endif
				// TODO Implementar logica de reintentos para mal CRC.
				// QMessageBox::critical(this, "CRC", "CRC Failed!: CRC Computed = " + QString::number((long)received_crc) + " CRC Sent = " + QString::number((long)apc_command_frame_crc));
			}
			////usleep(1);
			//init_protocol_frame_analyzer();
			memset(response_buffer, '\0', protocol_frame_bytes_analyzed);
			protocol_frame_bytes_analyzed = 0;
			apc_response_frame_payload_length = 0;
			apc_response_frame_payload_read = 0;
			apc_command_frame_crc = 0;
		}
		break;
	default:
		break;
	}
}

void CommunicationManager::process_response(apc_protocol_t primitive) {
	data_counter = 0;

	switch (primitive) {
	case _CHECK_COMMUNICATION:
#ifdef DEBUG_PRINTF_ON
		//printf("\nRecibiendo _CHECK_COMMUNICATION...\n");
#endif       
		//QMessageBox::information(this, "Información", "Recibida respuesta de _CHECK_COMMUNICATION!");

		break;
	case _START_ADQ:
#ifdef DEBUG_PRINTF_ON
		//printf("\nRecibiendo _START_ADQ...\n");
#endif

		//QMessageBox::information(this, "Información", "Recibida respuesta de _START_ADQ!");

		break;
	case _CHECK_ADQ:
#ifdef DEBUG_PRINTF_ON
		//printf("\nRecibiendo _CHECK_ADQ...\n");
#endif

		//QMessageBox::information(this, "Información", "Recibida respuesta de _CHECK_ADQ!");

		if (response_buffer[6] == 0xFF) {
			packages_made = true;
			channels_to_read = response_buffer[7];
			packages_to_read = (((unsigned short)response_buffer[8]) << 8) + response_buffer[9];
		}
		else {
			packages_made = false;
		}

		break;
	case _GET_PACKAGE:
#ifdef DEBUG_PRINTF_ON
		//printf("\nRecibiendo _GET_PACKAGE...\n");
#endif
		//readPackage();
		//        QMessageBox::information(this, "Información", "Recibida respuesta de _GET_PACKAGE!");

		break;
	default:
		// Construir frame de comando desconocido, informando error.
		break;
	}
}

unsigned short CommunicationManager::calculate_ccitt_crc(unsigned char *frame, unsigned int size) {
	unsigned short remainder = INITIAL_REMAINDER;
	unsigned int byte;
	unsigned char bit;

	for (byte = 0; byte < size; ++byte) {
		remainder ^= (frame[byte] << (WIDTH - 8));
		for (bit = 8; bit > 0; --bit) {
			if (remainder & TOPBIT) {
				remainder = (remainder << 1) ^ POLYNOMIAL;
			}
			else {
				remainder = (remainder << 1);
			}
		}
	}
	return (remainder ^ FINAL_XOR_VALUE);
}
