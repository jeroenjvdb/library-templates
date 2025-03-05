#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <stdint.h>

typedef enum log_level_t {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_ERROR
} log_level_t;

typedef struct log_message_t {
  const char *message;
  const char *tag;
  log_level_t level;
  uint32_t timestamp;
} log_message_t;

typedef struct logger_cfg_s {
  void (*print)(const log_message_t *message);
  uint32_t (*get_timestamp)(void);
  log_level_t default_level;
} logger_cfg_t;

void logger_init(logger_cfg_t *cfg);

void logger_log(const char *tag, log_level_t level, const char *message);


#endif // UTILS_LOGGER_H