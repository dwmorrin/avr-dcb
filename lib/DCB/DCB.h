/**
 * Juno 60 Digital Communications Bus
 * reference: https://www.chd-el.cz/support/application/app003-dcb/
 *
 * Juno 60 just streams current voice data out.
 * Identifier byte is 0xFE followed by six bytes of voice data.
 * Each voice data byte contains the gate (note on/off) in the MSB
 * and the note # in bits 0-6.
 *
 * Unlike MIDI, we do need to send a separate clock signal alongside our
 * TX data, so we will use the XCK pin.
 *
 * Baud rate: 31250
 * Data bits: 8
 * Parity: odd
 * Stop bits: 2
 * Inverted (1=low, 0=high) (whether this is done in software or hardware is TBD)
 *
 * There is a busy signal for both RX and TX, TBD how to implement those.
 *
 * Just implementing the TX side for now.
 *
 * Note #s: 0x18 to 0x54
 */

#include <avr/io.h>

#define RXD PD0
#define TXD PD1
#define XCK PD4

// Ready To Send (IN; remote device signals ready to receive data)
#define RTS PD2

// Clear To Send (OUT; this uC signals ready to receive data)
#define CTS PD3

#define ID_KEY_CODE 0xFE

struct DCB_voice
{
  uint8_t gate; // 0=off, 1=on
  uint8_t note; // 0x18 to 0x54
};

struct DCB_frame
{
  uint8_t identifier;
  struct DCB_voice voices[6];
};

void DCB_init(void);
void DCB_send(struct DCB_frame *frame);

// TODO: receive