#include "utils/logger.h"

#include <stddef.h>
#include <string.h>

static logger_cfg_t s_logger = {
    .print = NULL,
    .get_timestamp = NULL,
    .default_level = LOG_LEVEL_DEBUG,
};

void logger_init(logger_cfg_t *cfg) {
  if (cfg == NULL) {
    return;
  }

  memcpy(&s_logger, cfg, sizeof(logger_cfg_t));
}

void logger_log(const char *tag, log_level_t level, const char *message) {
  log_message_t log_message = {.tag = tag,
                               .level = level,
                               .message = message,
                               .timestamp = s_logger.get_timestamp()};
  if (s_logger.default_level > level) {
    return;
  }
  if (s_logger.print == NULL) {
    return;
  }
  s_logger.print(&log_message);
}