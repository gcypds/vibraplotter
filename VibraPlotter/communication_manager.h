#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include "Protocol.h"

const unsigned char communication_ok_response[2] = { 0xEE, 0xFF };
const unsigned char communication_crc_error_response[2] = { 0xBB, 0xCC };

class CommunicationManager : public QObject
{
	Q_OBJECT

public:
	CommunicationManager(QObject *parent = NULL);
	~CommunicationManager();

	bool open_connection(QString port, int baudrate);
	bool close_connection();

	void init_protocol_frame_analyzer();
	int build_protocol_frame(apc_protocol_t cid, unsigned char* frame_buffer, unsigned char * payload, int payload_length);
	void process_response(apc_protocol_t primitive);
	void protocol_frame_analyzer(unsigned char data);	
	unsigned short calculate_ccitt_crc(unsigned char *frame, unsigned int size);
	char * get_frame_state_name(apc_response_frame_state_t state);

	QSerialPort *serial;
	long data_counter;

	// Bandera para definir si los paquetes ya estan listos para ser leidos.
	bool packages_made = false;

	// Total de canales para leer
	unsigned char channels_to_read = 0;

	// Total de paquetes para leer
	unsigned short packages_to_read = 0;

	// Numero de paquete actualmente leido.
	unsigned short current_package = 0;

private:

	unsigned short apc_command_frame_crc;
	unsigned int apc_response_frame_payload_length;
	unsigned int apc_response_frame_payload_read;
	unsigned int protocol_frame_bytes_analyzed;
	apc_response_frame_state_t apc_response_frame_state;		

	QVector<unsigned char> *bytes_to_save;

	unsigned char command_buffer[APC_COMMAND_FRAME_BUFFER_SIZE]; // For sending
	unsigned char response_buffer[APC_RESPONSE_FRAME_BUFFER_SIZE]; // For receiving
	unsigned char package_buffer[NUMBER_OF_MAX_ADQ_CHANNELS*ADQ_SAMPLES_PER_SECOND*ADQ_BYTES_PER_SAMPLE]; // For package sending	

	
};

#endif // COMMUNICATION_MANAGER_H
