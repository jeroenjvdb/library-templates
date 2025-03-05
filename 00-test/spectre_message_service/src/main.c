#include <stdio.h>

#include "utils/logger.h"

static void print_log(const log_message_t *message);
static uint32_t get_timestamp(void);

logger_cfg_t logger_cfg = {
    .print = print_log,
    .get_timestamp = get_timestamp,
    .default_level = LOG_LEVEL_DEBUG
};

int main(int argc, char ** argv)
{
    logger_init(&logger_cfg);

    logger_log("main", LOG_LEVEL_INFO, "Hello, World!");
    logger_log("main", LOG_LEVEL_DEBUG, "This is a debug message");
    logger_log("main", LOG_LEVEL_WARNING, "This is a warning message");
    logger_log("main", LOG_LEVEL_ERROR, "This is an error message");

    return 0;
}

static void print_log(const log_message_t *message)
{
    printf("%10d | [%10s] %d: %s\n", message->timestamp, message->tag, message->level, message->message);
}

static uint32_t get_timestamp(void)
{
    return 0;
}