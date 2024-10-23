#include "signal_generator.h"

static const char *TAG_SIGNAL = "SIGNAL_GEN";

uint8_t waveform[ARRAY_LEN] = {0};

// Função para criar o vetor de forma de onda
void new_waveform(){
  switch (onda) {
    case TRIANGULAR: 
      for(uint16_t i = 0; i<ARRAY_LEN; i++){
        waveform[i] = (i > (ARRAY_LEN / 2)) ? (2 * ampl * (ARRAY_LEN - i) / ARRAY_LEN) : (2 * ampl * i / ARRAY_LEN);
      }
      break;
    case DENTE_DE_SERRA: 
      for(uint16_t i = 0; i<ARRAY_LEN; i++){
        waveform[i] = (i == ARRAY_LEN) ? 0 : (i * ampl / ARRAY_LEN);
      }
      break;
    case QUADRADA: 
      for(uint16_t i = 0; i<ARRAY_LEN; i++){
        waveform[i] = (i < (ARRAY_LEN / 2)) ? ampl : 0;
      }
      break;
    case SENOIDE: 
      for(uint16_t i = 0; i<ARRAY_LEN; i++){
        waveform[i] = (uint8_t)((sin(i * CONST_PERIOD_2_PI / ARRAY_LEN) + 1) * (float)(ampl) / 2 + 0.5);
      }
      break;
  }
  size_t buf_len = ARRAY_LEN;
  ESP_ERROR_CHECK(dac_continuous_write_cyclically(cont_handle, (uint8_t *)waveform, buf_len, NULL));
}

// Função para alterar a frequência
void handle_freq() {
  if (freq == 4E3) freq = 2E3;
  else freq += 100;
  ESP_ERROR_CHECK(dac_continuous_disable(cont_handle));
  ESP_ERROR_CHECK(dac_continuous_del_channels(cont_handle));
  dac_continuous_config_t cont_cfg = (dac_continuous_config_t) {
    .chan_mask = DAC_CHANNEL_MASK_CH0,
    .desc_num = 8,
    .buf_size = 2048,
    .freq_hz = freq*ARRAY_LEN,
    .offset = 0,
    .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
  };
  ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &cont_handle));
  ESP_ERROR_CHECK(dac_continuous_enable(cont_handle));
  ESP_ERROR_CHECK(dac_continuous_write_cyclically(cont_handle, (uint8_t *)waveform, ARRAY_LEN, NULL));
  ESP_LOGI(TAG_SIGNAL, "Valor de FREQUENCIA: %d Hz", freq);
}

// Função para alterar a amplitude
void handle_ampl() {
  if (ampl == 250) ampl = 25;
  else ampl += 25;
  float tmp = ampl * 3.3 / 255;
  new_waveform();
  ESP_LOGI(TAG_SIGNAL, "Valor de AMPLITUDE: %.2f V", tmp);
}

// Função para alternar a forma de onda
void handle_switch_sig() {
  if (onda == SENOIDE) onda = TRIANGULAR;
  else onda++;
  new_waveform();
  char *tmp = "";
  switch (onda) {
    case TRIANGULAR: tmp = "TRIANGULAR"; break;
    case DENTE_DE_SERRA: tmp = "DENTE DE SERRA"; break;
    case QUADRADA: tmp = "QUADRADA"; break;
    case SENOIDE: tmp = "SENOIDE"; break;
  }
  ESP_LOGI(TAG_SIGNAL, "Onda a ser gerada: %s", tmp);
}
