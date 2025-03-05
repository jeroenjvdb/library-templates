#include "spectre_message_service/message_service.h"

#define MESSAGE_START_BYTE_VAL 0xFF
#define MESSAGE_START_BYTE_LOC 0

#define MESSAGE_COMMAND_BYTE_LOC 1

#define MESSAGE_LENGTH_BYTE_LOC 2

#define MESSAGE_DATA_BYTE_LOC 3

#define MESSAGE_CHECKSUM_BYTE_LOC(LEN) (LEN + 3)

// buffer to store received data
static uint8_t receive_buffer[MAX_MESSAGE_LENGTH * 2];
static uint8_t receive_buffer_write_index = 0;
static uint8_t receive_buffer_read_index = 0;

void message_service_init(const message_service_t *message_service) {
  // add initialization code here
}

message_error_t message_service_send(const message_service_t *message_service,
                                     const message_t *message) {
  // prepare data to be sent
  uint8_t data[] = {0};
  data[MESSAGE_START_BYTE_LOC] = MESSAGE_START_BYTE_VAL;
  data[MESSAGE_COMMAND_BYTE_LOC] = message->command;
  data[MESSAGE_LENGTH_BYTE_LOC] = message->data_length;
  for (uint8_t i = 0; i < message->data_length; i++) {
    data[MESSAGE_DATA_BYTE_LOC + i] = message->data[i];
  }
  data[MESSAGE_CHECKSUM_BYTE_LOC(message->data_length)] =
      message_service->calculate_checksum(message->data, message->data_length);

  // send data
  if (!message_service->send_cb(data, message->data_length + 4)) {
    return MESSAGE_ERROR_SEND_FAILED;
  }

  return MESSAGE_ERROR_NONE;
}

message_error_t message_service_receive(message_service_t *message_service,
                                        message_t *message, uint8_t max_length) {
  // add receive code here
  return MESSAGE_ERROR_NONE;
}