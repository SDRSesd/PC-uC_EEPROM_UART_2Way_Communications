#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 2400
#define MYUBRR F_CPU/16/BAUD-1
#define EEPROM_SIZE 1024  // EEPROM size in bytes

volatile uint16_t eeAddress = 0;
volatile uint32_t byteCounter = 0;
volatile uint32_t startTime = 0;

void uart_init(unsigned int ubrr) {
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    
    /* Set frame format: 8 data bits, 1 stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(unsigned char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)));
    
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char uart_receive(void) {
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)));
    
    /* Get and return received data from buffer */
    return UDR0;
}

void uart_print_string(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

void uart_print_number(uint32_t num) {
    char buffer[10];
    itoa(num, buffer, 10);  // Convert number to string
    uart_print_string(buffer);
}

// ISR to handle received data
ISR(USART_RX_vect) {
    /* Receive data from UART */
    unsigned char receivedByte = UDR0;
    
    /* Store byte in EEPROM */
    if (eeAddress < EEPROM_SIZE) {
        eeprom_write_byte((uint8_t*)eeAddress, receivedByte);
        eeAddress++;
    }
    
    /* Transmit byte back to PC */
    uart_transmit(receivedByte);
    
    /* Print received byte to the serial console */
    uart_print_string("Received: ");
    uart_transmit(receivedByte);  // Print as character
    uart_print_string("\n");
    
    /* Increment byte counter */
    byteCounter++;
}

void init_timer0() {
    /* Set timer to CTC mode */
    TCCR0A = (1 << WGM01);
    
    /* Set prescaler to 1024 and start the timer */
    TCCR0B = (1 << CS02) | (1 << CS00);
    
    /* Enable Timer compare interrupt */
    TIMSK0 = (1 << OCIE0A);
    
    /* Set compare value for 1-second interval */
    OCR0A = 156;  // 1 second interval
}

// Timer interrupt to calculate and print speed every second
ISR(TIMER0_COMPA_vect) {
    /* Calculate the speed (bits per second) */
    uint32_t bitsPerSecond = byteCounter * 8;  // Convert bytes to bits
    
    /* Print the speed */
    uart_print_string("Speed: ");
    uart_print_number(bitsPerSecond);
    uart_print_string(" bps\n");
    
    /* Reset byte counter */
    byteCounter = 0;
}

int main(void) {
    /* Initialize UART and Timer */
    uart_init(MYUBRR);
    init_timer0();
    
    /* Enable global interrupts */
    sei();
    
    uart_print_string("Ready to receive data...\n");
    
    /* Main loop */
    while (1) {
        // Main work is done in ISR
    }
}
