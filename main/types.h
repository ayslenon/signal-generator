#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// Enum para a forma de onda
typedef enum {
  TRIANGULAR,
  DENTE_DE_SERRA,
  QUADRADA,
  SENOIDE
} forma_onda_t;

// Definição da estrutura Button
typedef struct {
  uint8_t _pin;
  uint8_t _flag;
  const char *_name;
  void (*_action)();
} Button;

#endif // TYPES_H
