#include "esp_check.h"

#include "buttons.h"
#include "dac_controller.h"
#include "signal_generator.h"

#define EXAMPLE_DAC_CHAN0_IO                DAC_CHAN0_GPIO_NUM

#define DAC_AMPLITUDE       255
#define CONVERT_FREQ_HZ     (ARRAY_LEN * freq)

// Variáveis globais para frequencia, amplitude e forma de onda
uint16_t freq = 2000;
uint8_t ampl = 125;
forma_onda_t onda = TRIANGULAR;

dac_continuous_handle_t cont_handle;
dac_continuous_config_t cont_cfg = (dac_continuous_config_t) {
  .chan_mask = DAC_CHANNEL_MASK_CH0,
  .desc_num = 8,
  .buf_size = 2048,
  .freq_hz = 800000,
  .offset = 0,
  .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
  .chan_mode = DAC_CHANNEL_MODE_SIMUL,
};

void app_main() {
  uint8_t button_s = 0;
  
  esp_log_level_set("*", ESP_LOG_INFO);

  config_buttons();
  config_dac();
  new_waveform();

  while (true) {
    handle_button(&bt_amp, &button_s);
    handle_button(&bt_freq, &button_s);
    handle_button(&bt_sw_sig, &button_s);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}