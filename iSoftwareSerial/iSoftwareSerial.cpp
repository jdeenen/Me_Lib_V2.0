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

// 
// Includes
// 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <Arduino.h>
#include <iSoftwareSerial.h>
//
// Lookup table (Note: Move the progmem definition into the typedef to prevent an annoying compiler warning)
//
typedef struct
{
  uint32_t baud;
  uint16_t rx_delay_centering;
  uint16_t rx_delay_intrabit;
  uint16_t tx_delay;
} PROGMEM DELAY_TABLE;

#if F_CPU == 16000000

const PROGMEM DELAY_TABLE table[] = 
{
  //  baud    rxcenter   rxintra    tx
/*{ 115200,   1,         17,        12    },
  { 57600,    10,        37,        33    },
  { 38400,    25,        57,        54    },
  { 31250,    31,        70,        68    },
  { 28800,    34,        77,        74    },
  { 19200,    54,        117,       114   },
  { 14400,    74,        156,       153   },*/
  { 9600,     833,       1667,      1667  },
  { 4800,     1667,      3333,      3333  },
/*{ 2400,     471,       950,       947   },
  { 1200,     947,       1902,      1899  },
  { 600,      1902,      3804,      3800  },
  { 300,      3804,      7617,      7614  },*/
};

/*
#elif F_CPU == 8000000

static const DELAY_TABLE table[] = 
{
  //  baud    rxcenter    rxintra    rxstop  tx
  { 115200,   1,          5,         5,      3,      },
  { 57600,    1,          15,        15,     13,     },
  { 38400,    2,          25,        26,     23,     },
  { 31250,    7,          32,        33,     29,     },
  { 28800,    11,         35,        35,     32,     },
  { 19200,    20,         55,        55,     52,     },
  { 14400,    30,         75,        75,     72,     },
  { 9600,     50,         114,       114,    112,    },
  { 4800,     110,        233,       233,    230,    },
  { 2400,     229,        472,       472,    469,    },
  { 1200,     467,        948,       948,    945,    },
  { 600,      948,        1895,      1895,   1890,   },
  { 300,      1895,       3805,      3805,   3802,   },
};

#elif F_CPU == 20000000

// 20MHz support courtesy of the good people at macegr.com.
// Thanks, Garrett!

static const DELAY_TABLE table[] =
{
  //  baud    rxcenter    rxintra    rxstop  tx
  { 115200,   3,          21,        21,     18,     },
  { 57600,    20,         43,        43,     41,     },
  { 38400,    37,         73,        73,     70,     },
  { 31250,    45,         89,        89,     88,     },
  { 28800,    46,         98,        98,     95,     },
  { 19200,    71,         148,       148,    145,    },
  { 14400,    96,         197,       197,    194,    },
  { 9600,     146,        297,       297,    294,    },
  { 4800,     296,        595,       595,    592,    },
  { 2400,     592,        1189,      1189,   1186,   },
  { 1200,     1187,       2379,      2379,   2376,   },
  { 600,      2379,       4759,      4759,   4755,   },
  { 300,      4759,       9523,      9523,   9520,   },
};

#else

#error This version of iSoftwareSerial supports only 20, 16 and 8MHz processors
*/
#endif

//
// Interrupt handling
//

/* static */
// Pointer to active iSoftwareSerial object
iSoftwareSerial *iSoftwareSerial::curr = NULL;

void iSoftwareSerial::handle_interrupt(  )
{
  switch (in_state) {
    // We receive a start bit
    case STATE_WAIT:
      // We only want to proceed if we see a start bit (low)
      if (read_pin())
        break;
        
      // Reset the internal state
      in_byte = 0;
      in_n_byte = 0;  
      
      // Set up the timer comparison
      OCR1A = TCNT1 + rx_center;
      
      // Disable pin change interrupt
      *in_int_reg &= ~in_int_mask;
      
      // Enable timer interrupt
      TIMSK1 |= (1 << OCIE1A);
      
      // Set the new state
      in_state = STATE_START;
      
      break;
    case STATE_START:
      OCR1A = TCNT1 + rx_intra;
      in_state = STATE_RECV;
      break;
    case STATE_RECV:
      // Read in the next bit
      in_byte >>= 1;
      if (read_pin())
        in_byte |= (int8_t)(1 << 7);
      if (in_n_byte == 7)
        in_state = STATE_END;
      in_n_byte++;
      
      // Update timer comparison
      OCR1A += rx_intra;
      
      break;
    case STATE_END:
      // We are at the stop bit, store the read byte in the circular buffer
      // If the buffer is full, we lose the first read bit
      if (buf_full)
        buf_start++;
      buf[buf_end++] = in_byte;
      buf_end %= _SS_MAX_RX_BUFF;
      if (buf_end == buf_start)
        buf_full = true;
      
      // Disable timer interrupts
      TIMSK1 &= ~(1 << OCIE1A);
      
      // Enable the pin change interrupt
      *in_int_reg |= in_int_mask;
      
      // Reset state
      in_state = STATE_WAIT;
      
      break;
    default:
      break;
  }
}

#if defined(PCINT0_vect)
ISR(PCINT0_vect)
{
  iSoftwareSerial::curr->handle_interrupt();
}
#else
	#error "Could not find pin interrupt vectors"
#endif

#if defined(PCINT1_vect)
ISR(PCINT1_vect, ISR_ALIASOF(PCINT0_vect));
#endif

#if defined(PCINT2_vect)
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
#endif

#if defined(PCINT3_vect)
ISR(PCINT3_vect, ISR_ALIASOF(PCINT0_vect));
#endif

ISR(TIMER1_COMPA_vect)
{
	iSoftwareSerial::curr->handle_interrupt();
}

ISR(TIMER1_COMPB_vect)
{
	iSoftwareSerial::curr->handle_interrupt();
}

//
// Constructor
//
iSoftwareSerial::iSoftwareSerial(int8_t receivePin, int8_t transmitPin) :
	setup(false), 
  in(receivePin), 
	in_port(digitalPinToPort(receivePin)), // Get the port mappings (1 = PA, 2 = PB ...)
	in_pin_reg(portInputRegister(in_port)), // Get the register to read port numbers
	in_int_reg(digitalPinToPCMSK(receivePin)), // Get the interrupt mask register for the input
	in_port_mask(digitalPinToBitMask(receivePin)),
  in_int_mask(_BV(digitalPinToPCMSKbit(receivePin))),
	out(transmitPin),
	out_port(digitalPinToPort(transmitPin)),
	out_port_reg(portOutputRegister(out_port)), // Get the output port register
	out_port_mask(digitalPinToBitMask(transmitPin)),
  buf_start(0),
  buf_end(0),
  buf_full(0),
  in_byte(0),
  in_n_byte(0),
  out_byte(0),
  out_n_byte(0),
  in_state(STATE_WAIT),
  out_state(STATE_WAIT)
{

    _receivePin = receivePin;
    _transmitPin = transmitPin;
    _baudRate = 0;
}

//
// Destructor
//
iSoftwareSerial::~iSoftwareSerial()
{
  // Disable interrupt on receive
  *in_int_reg &= ~in_int_mask;
  
  // Disable the timer interrupts, in case we were in the 
  // middle of receiving or transmitting.
  TIMSK1 &= ~((1 << OCIE1A) & (1 << OCIE1B));
  
}

//
// Public methods
//

void iSoftwareSerial::begin(uint32_t req_baud)
{

    _baudRate = req_baud;
    _bitPeriod = 1000000 / 9600;//_baudRate;
  // Set up pins
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);
  digitalWrite(in, HIGH); // Activate the pullup on the receive pin
    
  // Activate and set up the pin change interrupts
  // Reset all pin change interrupt masks to zero
  PCMSK0 = 0;
  PCMSK1 = 0;
  PCMSK2 = 0;
    
  // Enable the corresponding interrupts in the Pin Change Interrupt control register
  PCICR |= _BV(PCIE0);
  PCICR |= _BV(PCIE1);
  PCICR |= _BV(PCIE2);
    
  // Set up the timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TIMSK1 = 0;
  TCCR1B = (1 << CS10);
  
  // Load delays from program memory into RAM.
  for (unsigned int i = 0; i < sizeof(table)/sizeof(table[0]); i++) {
    uint32_t baud = pgm_read_dword(&table[i].baud);
    if (req_baud == baud) {
      baud = req_baud;
      rx_center = pgm_read_word(&table[i].rx_delay_centering);
      rx_intra = pgm_read_word(&table[i].rx_delay_intrabit);
      tx_delay = pgm_read_word(&table[i].tx_delay);
      setup = true;
      break;
    }
  }
  
  // If we were unable to set up, fail out.
  if (setup == false)
    return;
  
  // Set this object as the active iSoftwareSerial object
  iSoftwareSerial::curr = this;
  
  // Activate the pin change interrupt
  *in_int_reg |= in_int_mask;
}


// Read data from buffer
int iSoftwareSerial::read()
{
	if (buf_start != buf_end) {
    int8_t byte = buf[buf_start++];
    buf_start %= _SS_MAX_RX_BUFF;
    buf_full = false;
    return byte;
  }
  return 0;
}

int iSoftwareSerial::available()
{
	return (buf_start != buf_end);
}

size_t iSoftwareSerial::write(uint8_t b)
{
	uint8_t oldSREG = SREG;
	cli();
    int bitDelay = _bitPeriod - clockCyclesToMicroseconds(50); // a digitalWrite is about 50 cycles
    byte mask;

    digitalWrite(_transmitPin, LOW);
    delayMicroseconds(bitDelay);

    for (mask = 0x01; mask; mask <<= 1) {
      digitalWrite(_transmitPin,(b & mask));
     delayMicroseconds(bitDelay);
    }

    digitalWrite(_transmitPin, HIGH);
    delayMicroseconds(bitDelay);
	sei();
	SREG = oldSREG;
    return 1;
}
void iSoftwareSerial::tx_pin_write(uint8_t pin_state)
{
  if (pin_state == LOW)
    *out_port_reg &= ~out_port_mask;
  else
    *out_port_reg |= out_port_mask;
}
inline void iSoftwareSerial::tunedDelay(uint16_t delay) { 
  uint8_t tmp=0;

  asm volatile("sbiw    %0, 0x01 \n\t"
    "ldi %1, 0xFF \n\t"
    "cpi %A0, 0xFF \n\t"
    "cpc %B0, %1 \n\t"
    "brne .-10 \n\t"
    : "+r" (delay), "+a" (tmp)
    : "0" (delay)
    );
}
void iSoftwareSerial::flush()
{
}

int iSoftwareSerial::peek()
{
	return 0;
}
