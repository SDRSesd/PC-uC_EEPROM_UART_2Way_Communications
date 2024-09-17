#include "real_time_uart_data.h"

void setup() {
    uart_init(MYUBRR);  // Initialize UART with calculated baud rate
    init_timer0();      // Initialize Timer0 for speed monitoring
    sei();              // Enable global interrupts
}

void loop() {
    // Main loop remains empty as the work is done in ISR
}

