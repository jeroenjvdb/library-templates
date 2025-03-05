#ifndef SPECTRE_MESSAGE_SERVICE_MESSAGE_SERVICE_H
#define SPECTRE_MESSAGE_SERVICE_MESSAGE_SERVICE_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_MESSAGE_LENGTH 20

/*!
 * @enum message_error_e
 * @brief Enumeration for message service error codes.
 *
 * This enumeration defines various error codes that can be returned by the
 * message service functions.
 */
typedef enum message_error_e {
  /*
   * Indicates that no error occurred.
   */
  MESSAGE_ERROR_NONE = 0,
  /*
   * @brief Error code indicating that an invalid command was received.
   */
  MESSAGE_ERROR_INVALID_COMMAND = 1,
  /**
   * @brief Error code indicating that the provided data is invalid.
   */
  MESSAGE_ERROR_INVALID_DATA = 2,
  /**
   * @brief Error code indicating that the message length is invalid.
   *
   * This error code is used to signify that the length of the message being
   * processed does not meet the required criteria.
   */
  MESSAGE_ERROR_INVALID_LENGTH = 3,
  /**
   * @brief Error code indicating that the checksum of the message is invalid.
   */
  MESSAGE_ERROR_INVALID_CHECKSUM = 4,
  /**
   * @brief Error code indicating that sending a message has failed.
   */
  MESSAGE_ERROR_SEND_FAILED = 5,
  /**
   * @brief Error code indicating that receiving a message has failed.
   */
  MESSAGE_ERROR_RECEIVE_FAILED = 6,
} message_error_t;

/*!
 * @struct message_s
 * @brief Represents a message structure used in the Spectre Message Service.
 *
 * This structure is used to encapsulate a message with a command and associated
 * data.
 *
 * @param command
 * The command identifier for the message.
 *
 * @param data
 * Pointer to the data associated with the message.
 *
 * @param data_length
 * The length of the data in bytes.
 */
typedef struct message_t {
  /**
   * @brief Command identifier for the message service.
   */
  uint8_t command;
  /**
   * @brief Pointer to a data buffer.
   */
  uint8_t *data;

  /**
   * @brief Length of the data in bytes.
   */
  uint8_t data_length;
} message_t;

/**
 * @struct message_service_s
 * @brief Structure representing a message service with send and receive
 callbacks.
 *
 * This structure defines a message service that includes two callback
 functions:
 * one for sending data and one for receiving data.
 *
 * @param send_cb
 * Callback function to send data.
 *
 * @param receive_cb
 * Callback function to receive data.
 */
typedef struct message_service_s {
  /**
   * @brief Callback function pointer for sending data.
   *
   * This function pointer is used to send data through a specified
   * communication channel. The function should be implemented to handle
   * the actual sending of data.
   *
   * @param data Pointer to the data buffer to be sent.
   * @param length Length of the data buffer.
   * @return true if the data was sent successfully, false otherwise.
   */
  bool (*send_cb)(uint8_t *data, uint8_t length);

  /*!
   * @brief Callback function pointer for receiving messages.
   *
   * This function pointer is used to define a callback function that will be
   * called when a message is received. The callback function should handle the
   * received data.
   *
   * @param data Pointer to the received data.
   * @param length Length of the received data.
   * @return true if the message was successfully processed, false otherwise.
   */
  bool (*receive_cb)(uint8_t *data, uint8_t length);

  uint8_t (*calculate_checksum)(uint8_t *data, uint8_t length);
} message_service_t;

/**
 * @brief Initializes the message service.
 *
 * This function sets up the message service, preparing it for use.
 *
 * @param message_service A pointer to the message service instance to
 * initialize.
 */
void message_service_init(const message_service_t *message_service);

/**
 * @brief Sends a message using the specified message service.
 *
 * This function sends a message through the provided message service.
 *
 * @param message_service A pointer to the message service to be used for
 * sending the message.
 * @param message A pointer to the message to be sent.
 */
message_error_t message_service_send(const message_service_t *message_service,
                                     const message_t *message);

/**
 * @brief Receives a message from the message service.
 *
 * This function is responsible for receiving a message from the specified
 * message service and storing it in the provided message structure.
 *
 * @param message_service A pointer to the message service from which to receive
 * the message.
 * @param message A pointer to the message structure where the received message
 * will be stored.
 * @param max_length The maximum length of the message to receive.
 */
message_error_t message_service_receive(message_service_t *message_service,
                                        message_t *message, uint8_t max_length);

#endif // SPECTRE_MESSAGE_SERVICE_MESSAGE_SERVICE_H