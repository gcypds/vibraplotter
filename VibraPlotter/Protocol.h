// Habilitar informacion de debug.
#define DEBUG_PRINTF_ON

// Adquisicion minimo de 1 canal
#define NUMBER_OF_MIN_ADQ_CHANNELS 1

// Adquisicion maximo de 7 canales
#define NUMBER_OF_MAX_ADQ_CHANNELS 7

// Tiempo de adquisicion minimo: 1 segundo
#define NUMBER_OF_MIN_ADQ_SECONDS 1

// Tiempo de adquisicion maximo: 600 segundos equivalente a 10 minutos
#define NUMBER_OF_MAX_ADQ_SECONDS 600

#define ADQ_BYTES_PER_SAMPLE 3
#define ADQ_SAMPLES_PER_SECOND 52734
#define ADQ_MAX_BUFFER_SIZE ADQ_SAMPLES_PER_SECOND * NUMBER_OF_MAX_ADQ_SECONDS

#define APC_FRAME_START 0x23
#define APC_FRAME_COMMAND 0x43
#define APC_FRAME_RESPONSE 0x52
#define APC_FRAME_END 0x2A
#define APC_FRAME_HEADER_SIZE 6
#define APC_FRAME_FOOTER_SIZE 3
#define APC_FRAME_CRC_H_OFFSET 3
#define APC_FRAME_CRC_L_OFFSET 2
#define APC_FRAME_END_OFFSET 1
#define APC_FRAME_MAX_APC_COMMAND_PAYLOAD_SIZE 0xFF
#define APC_FRAME_MAX_APC_RESPONSE_PAYLOAD_SIZE ADQ_BYTES_PER_SAMPLE*ADQ_SAMPLES_PER_SECOND*NUMBER_OF_MAX_ADQ_CHANNELS
#define APC_COMMAND_FRAME_BUFFER_SIZE APC_FRAME_HEADER_SIZE+APC_FRAME_MAX_APC_COMMAND_PAYLOAD_SIZE+APC_FRAME_FOOTER_SIZE
#define APC_RESPONSE_FRAME_BUFFER_SIZE APC_FRAME_HEADER_SIZE+APC_FRAME_MAX_APC_RESPONSE_PAYLOAD_SIZE+APC_FRAME_FOOTER_SIZE

// Defines para calculo de CRC-CCITT
#define POLYNOMIAL			0x1021
#define INITIAL_REMAINDER	0xFFFF
#define FINAL_XOR_VALUE		0x0000
#define WIDTH	(8 * sizeof(unsigned short))
#define TOPBIT	(1 << (WIDTH - 1))

typedef enum {
	_UNKNOWN = 0x00,
	_CHECK_COMMUNICATION = 0xF1, // Realizar una verificacion de correcta comunicacion. Devuelve el numero maximo de segundos soportados y el numero maximo de canales.
	_START_ADQ = 0xF2, // Inicia la adquisicion de datos.
	_CHECK_ADQ = 0xF3, // Informa el estado de la adquisicion. Chequea si la adquision ha finalizado e informa el numero de paquetes obtenidos.
	_GET_PACKAGE = 0xF4 // Contiene los datos del paquete solicitado.
} apc_protocol_t;

typedef enum {
	_OK = 0x00,
	_CRC_ERROR = 0x01,
	_PAYLOAD_OVERFLOW = 0x02,
	_BUFFER_OVERFLOW = 0x03,
	_NO_RESPONSE = 0x04
} protocol_frame_analyzed_error_code_t;

typedef enum {
	_NONE = 0x00,
	_FINISHED = 0xFF
} adq_status_t;

typedef enum {
	_NORMAL = 0x00,
	_FRAME_START = 0x01,
	_FRAME_TYPE = 0x02,
	_CID = 0x03,
	_PAYLOAD_LENGTH_H = 0x04,
	_PAYLOAD_LENGTH_M = 0x05,
	_PAYLOAD_LENGTH_L = 0x06,
	_PAYLOAD = 0x07,
	_CRC_H = 0x08,
	_CRC_L = 0x09,
	_FRAME_END = 0x0A
} apc_response_frame_state_t;