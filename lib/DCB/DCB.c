#include "DCB.h"

void DCB_init()
{
  // Set the baud rate to 31250
  // Set the data bits to 8
  // Set the parity to odd
  // Set the stop bits to 2
  // TBD: inverted - software or hardware?
}

void DCB_send(struct DCB_frame *frame)
{
  // check the receivers busy signal? (unsure of this spec)
  // tx frame->identifier
  for (int i = 0; i < 6; ++i)
  {
    // tx frame->voices[i]
  }
}