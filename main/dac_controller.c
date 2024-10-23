#include "dac_controller.h"

static const char *TAG_DAC = "DAC";

void config_dac() {
  ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &cont_handle));
  ESP_ERROR_CHECK(dac_continuous_enable(cont_handle));

  ESP_LOGI(TAG_DAC, "--------------------------------------------------");
  ESP_LOGI(TAG_DAC, "DAC continuous output by DMA");
  ESP_LOGI(TAG_DAC, "DAC channel 0 io: GPIO_NUM_%d", DAC_CHAN0_GPIO_NUM);
  ESP_LOGI(TAG_DAC, "Forma de onda: TRIANGULAR -> DENTE_DE_SERRA -> QUADRADA -> SENOIDE");
  ESP_LOGI(TAG_DAC, "DAC conversion frequency (Hz): %d", CONVERT_FREQ_HZ);
  ESP_LOGI(TAG_DAC, "DAC wave frequency (Hz): %d", freq);
  ESP_LOGI(TAG_DAC, "--------------------------------------------------");
}
