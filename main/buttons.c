#include "buttons.h"

static const char *TAG_BUTTON = "BUTTON";

Button bt_freq = {
  ._pin = BUTTON_FREQ_PIN,
  ._flag = 0x04,
  ._name = "frequencia",
  ._action = handle_freq
};

Button bt_amp = {
  ._pin = BUTTON_AMP_PIN,
  ._flag = 0x02,
  ._name = "amplitude",
  ._action = handle_ampl
};

Button bt_sw_sig = {
  ._pin = BUTTON_SIG_PIN,
  ._flag = 0x01,
  ._name = "forma de onda",
  ._action = handle_switch_sig
};

void config_button(uint8_t pin) {
  gpio_reset_pin(pin);
  gpio_set_direction(pin, GPIO_MODE_INPUT);
  gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
}

// Função de configuração dos botões
void config_buttons() {
  config_button(bt_freq._pin);
  config_button(bt_amp._pin);
  config_button(bt_sw_sig._pin);
  ESP_LOGI(TAG_BUTTON, "--------------------------------------------------");
  ESP_LOGI(TAG_BUTTON, "Botoes configurados");
  ESP_LOGI(TAG_BUTTON, "Botao de Frequencia na GPIO: %d", BUTTON_FREQ_PIN);
  ESP_LOGI(TAG_BUTTON, "Botao de Amplitude na GPIO: %d", BUTTON_AMP_PIN);
  ESP_LOGI(TAG_BUTTON, "Botao de Forma de onda na GPIO: %d", BUTTON_SIG_PIN);
  ESP_LOGI(TAG_BUTTON, "--------------------------------------------------");
}

void handle_button(Button *bt, uint8_t *button_s) {
  if (!gpio_get_level(bt->_pin) && ~(*button_s) & bt->_flag) {
    *button_s |= bt->_flag;
    ESP_LOGI(TAG_BUTTON, "Botao %s pressionado", bt->_name);
    if (bt->_action != NULL) bt->_action();
  } else if (*button_s & bt->_flag && gpio_get_level(bt->_pin)) {
    *button_s &= ~(bt->_flag);
    ESP_LOGI(TAG_BUTTON, "Botao %s solto", bt->_name);
  }
}
