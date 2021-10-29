#include "DCB.h"

void DCB_init()
{
  // HARDWARE NOTE: signals on bus are inverted, handled in hardware
  // assumes 1 MHz clock
  // Set the baud rate to 31250
  // sync main mode UBRR0 = (1e6 / (2 * 31250)) - 1 = 15
  UBRR0 = 15;
  // Keep default of 8 data bits
  // Set the parity to odd
  UCSR0C |= (1 << UPM01) | (1 << UPM00);
  // Set the stop bits to 2
  UCSR0C |= (1 << USBS0);
  // Syncronous USART
  UCSR0C |= (1 << UMSEL00);
  // enable receiver and transmitter
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  // DDR must be set to output for TX, clock, and busy output
  DDRD |= (1 << TXD) | (1 << XCK) | (1 << CTS);
  // pullup on RTS
  PORTD |= (1 << RTS);
}

void DCB_tx(uint8_t data)
{
  // Wait for the transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // Put the data in the buffer
  UDR0 = data;
}

void DCB_send(struct DCB_frame *frame)
{
  // wait for receiver to not be busy
  while (PIND & (1 << RTS))
    ;
  // tx frame->identifier
  DCB_tx(frame->identifier);
  for (int i = 0; i < 6; ++i)
  {
    // tx frame->voices[i]
    DCB_tx((frame->voices[i].gate << 7) | frame->voices[i].note);
  }
}