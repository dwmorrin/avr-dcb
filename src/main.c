#include <util/delay.h>
#include <DCB.h>

#include "notes.h"

int main()
{
  DCB_init();
  struct DCB_frame frame = {
      .identifier = ID_KEY_CODE,
      .voices = {
          {.gate = 0, .note = E2},
          {.gate = 0, .note = GS2},
          {.gate = 0, .note = B3},
          {.gate = 0, .note = E3},
          {.gate = 0, .note = GS3},
          {.gate = 0, .note = B4},
      }};
  while (1)
  {
    for (int i = 0; i < 6; ++i)
      frame.voices[i].gate = !frame.voices[i].gate;
    DCB_send(&frame);
    _delay_ms(100);
  }
}