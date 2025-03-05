#include <stdbool.h>
#include <stdint.h>

typedef enum spectre_command_e {
  SPECTRE_COMMAND_HEARTBEAT = 0,
  SPECTRE_COMMAND_GET_SOFTWARE_VERSION = 1,
  SPECTRE_COMMAND_GET_HARDWARE_VERSION = 2,
} spectre_command_t;

typedef struct spectre_software_version_s {
  uint8_t major;
  uint8_t minor;
} spectre_software_version_t;

typedef struct spectre_hardware_version_s {
  uint8_t major;
  uint8_t minor;
} spectre_hardware_version_t;

void spectre_init(message_service_t *message_service);

bool spectre_send_heartbeat(void);

message_error_t
spectre_get_software_version(spectre_software_version_t *version);

message_error_t
spectre_get_hardware_version(spectre_hardware_version_t *version);