#include "spectre.h"

#include <stddef.h>

#include "message_service.h"

static message_service_t *s_message_service = NULL;

static message_error_t spectre_send_command(spectre_command_t command,
                                            uint8_t *data,
                                            uint8_t data_length) {
  if (data_length > MAX_MESSAGE_LENGTH) {
    return MESSAGE_ERROR_INVALID_LENGTH;
  }
  if (data_length > 0 && data == NULL) {
    return MESSAGE_ERROR_INVALID_DATA;
  }

  message_t message;
  message.command = command;
  message.data = data;
  message.data_length = data_length;

  return message_service_send(s_message_service, &message);
}

static message_error_t spectre_receive_command(spectre_command_t command,
                                               uint8_t *data,
                                               uint8_t max_data_length) {
  message_t message;
  message.data = data;

  message_error_t error =
      message_service_receive(s_message_service, &message, max_data_length);

  if (error != MESSAGE_ERROR_NONE) {
    return error;
  }

  if (message.command != command) {
    return MESSAGE_ERROR_INVALID_DATA;
  }

  return MESSAGE_ERROR_NONE;
}

void spectre_init(message_service_t *message_service) {
  s_message_service = message_service;
}

bool spectre_send_heartbeat(void) {
  message_t message;
  message.command = SPECTRE_COMMAND_HEARTBEAT;
  message.data_length = 0;

  return message_service_send(s_message_service, &message) ==
         MESSAGE_ERROR_NONE;
}

message_error_t
spectre_get_software_version(spectre_software_version_t *version) {
  message_error_t status;
  status = spectre_send_command(SPECTRE_COMMAND_GET_SOFTWARE_VERSION, NULL, 0);
  if (MESSAGE_ERROR_NONE != status) {
    return status;
  }

  uint8_t data[2] = {0};
  status =
      spectre_receive_command(SPECTRE_COMMAND_GET_SOFTWARE_VERSION, data, 2);
  if (MESSAGE_ERROR_NONE != status) {
    return status;
  }

  version->major = data[0];
  version->minor = data[1];

  return MESSAGE_ERROR_NONE;
}

message_error_t
spectre_get_hardware_version(spectre_hardware_version_t *version) {
    message_error_t status;
    status = spectre_send_command(SPECTRE_COMMAND_GET_HARDWARE_VERSION, NULL, 0);
    if (MESSAGE_ERROR_NONE != status) {
        return status;
    }

    uint8_t data[2] = {0};
    status =
        spectre_receive_command(SPECTRE_COMMAND_GET_HARDWARE_VERSION, data, 2);
    if (MESSAGE_ERROR_NONE != status) {
        return status;
    }

    version->major = data[0];
    version->minor = data[1];

    return MESSAGE_ERROR_NONE;
}