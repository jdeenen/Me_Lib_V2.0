/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.
*/

#ifndef __I_SOFTWARE_SERIAL_H__
#define __I_SOFTWARE_SERIAL_H__

#include <inttypes.h>
#include <Stream.h>
#include <Arduino.h>

/******************************************************************************
* Definitions
******************************************************************************/

#define _SS_MAX_RX_BUFF 64 // RX buffer size
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class iSoftwareSerial : public Stream
{
private:
  // Setup bit
  bool setup;

  // Pointers for accessing the input and output pins
  uint8_t in;
  uint8_t in_port;
  volatile uint8_t *in_pin_reg;
  volatile uint8_t *in_int_reg;
  uint8_t in_port_mask;
  uint8_t in_int_mask;
  uint8_t out;
  uint8_t out_port;
  volatile uint8_t *out_port_reg;
  uint8_t out_port_mask;
  
  // Circular buffer for bytes read
  volatile uint8_t buf[_SS_MAX_RX_BUFF];
  volatile uint8_t buf_start;
  volatile uint8_t buf_end;
  volatile uint8_t buf_full;
  
  // Calculated delay values
  uint32_t baud;
  uint16_t rx_center;
  uint16_t rx_intra;
  uint16_t tx_delay;

  uint8_t _receivePin;
  uint8_t _transmitPin;
  long _baudRate;
  int _bitPeriod;
  
  // State information
  typedef enum {
    STATE_WAIT,
    STATE_START,
    STATE_RECV,
    STATE_SEND,
    STATE_END
  } state;
  uint8_t in_byte;
  uint8_t in_n_byte;
  uint8_t out_byte;
  uint8_t out_n_byte;
  state in_state;
  state out_state;
  void tx_pin_write(uint8_t pin_state);
  __attribute__((always_inline))
  inline uint8_t read_pin() {
    return (*in_pin_reg & in_port_mask);
  }
  // private static method for timing
  static inline void tunedDelay(uint16_t delay);
  
public:
  // public methods
  iSoftwareSerial(int8_t receivePin, int8_t transmitPin);
  ~iSoftwareSerial();
  void begin(uint32_t speed);
  bool overflow() { return buf_full == true; }
  int peek();

  
  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int available();
  virtual void flush();
  
  using Print::write;
  
  void handle_interrupt();

  // Static members/methods used by the interrupt handlers
  static iSoftwareSerial *curr;
};

#endif
