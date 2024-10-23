#ifndef DAC_CONTROLLER_H
#define DAC_CONTROLLER_H

#include "esp_check.h"

#include "soc/dac_channel.h"
#include "driver/dac_continuous.h"

#include "signal_generator.h"
#include "types.h"

#define DAC_AMPLITUDE       255
#define CONVERT_FREQ_HZ     (ARRAY_LEN * freq)

extern uint16_t freq;
extern uint8_t ampl;
extern forma_onda_t onda;

extern dac_continuous_handle_t cont_handle;
extern dac_continuous_config_t cont_cfg;

/**
 * @brief configuração do DAC
 */
void config_dac();

#endif  // DAC_CONTROLLER_H
