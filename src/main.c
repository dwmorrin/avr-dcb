#include <util/delay.h>
#include <DCB.h>

int main()
{
  DCB_init();
  struct DCB_frame frame = {
      .identifier = ID_KEY_CODE,
      .voices = {
          {.gate = 0, .note = 0x18},
          {.gate = 0, .note = 0x18},
          {.gate = 0, .note = 0x18},
          {.gate = 0, .note = 0x18},
          {.gate = 0, .note = 0x18},
          {.gate = 0, .note = 0x18},
      }};
  while (1)
  {
    frame.voices[0].gate = !frame.voices[0].gate;
    DCB_send_frame(&frame);
    _delay_ms(500);
  }
}