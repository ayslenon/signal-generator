# Using DAC DMA to generate waveforms

## Settings

Using channel 0 DAC, GPIO 25

Waveforms supported: Sawtooth, Triangle, Squared, Sine

Frequencies tested: from 2kHz to 4kHz (up to several MHz according to espressif idf guides)

- Next steps:
  - Create more customizable waveforms
  - Create an easier way to setup the signal in DAC
  - Implement freeRTOS tasks
