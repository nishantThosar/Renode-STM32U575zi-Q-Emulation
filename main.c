#include <stdint.h>
#include <string.h>

// ==============================================================================
// REGISTER DEFINITIONS
// ==============================================================================

// RCC Base Address
#define RCC_BASE            0x46020C00
#define RCC_AHB2ENR         (*((volatile uint32_t *)(RCC_BASE + 0x4C)))
#define RCC_APB2ENR         (*((volatile uint32_t *)(RCC_BASE + 0x60)))

// GPIO Base Addresses
#define GPIOA_BASE          0x42020000
#define GPIOB_BASE          0x42020400
#define GPIOC_BASE          0x42020800
#define GPIOG_BASE          0x42021800

// GPIO Register Offsets
#define GPIO_MODER_OFFSET   0x00
#define GPIO_ODR_OFFSET     0x14
#define GPIO_BSRR_OFFSET    0x18

// GPIO Registers - Port B (Blue LED - PB7)
#define GPIOB_MODER         (*((volatile uint32_t *)(GPIOB_BASE + GPIO_MODER_OFFSET)))
#define GPIOB_ODR           (*((volatile uint32_t *)(GPIOB_BASE + GPIO_ODR_OFFSET)))
#define GPIOB_BSRR          (*((volatile uint32_t *)(GPIOB_BASE + GPIO_BSRR_OFFSET)))

// GPIO Registers - Port C (Green LED - PC7)
#define GPIOC_MODER         (*((volatile uint32_t *)(GPIOC_BASE + GPIO_MODER_OFFSET)))
#define GPIOC_ODR           (*((volatile uint32_t *)(GPIOC_BASE + GPIO_ODR_OFFSET)))
#define GPIOC_BSRR          (*((volatile uint32_t *)(GPIOC_BASE + GPIO_BSRR_OFFSET)))

// GPIO Registers - Port G (Red LED - PG2)
#define GPIOG_MODER         (*((volatile uint32_t *)(GPIOG_BASE + GPIO_MODER_OFFSET)))
#define GPIOG_ODR           (*((volatile uint32_t *)(GPIOG_BASE + GPIO_ODR_OFFSET)))
#define GPIOG_BSRR          (*((volatile uint32_t *)(GPIOG_BASE + GPIO_BSRR_OFFSET)))

// USART1 Base Address
#define USART1_BASE         0x40013800
#define USART1_CR1          (*((volatile uint32_t *)(USART1_BASE + 0x00)))
#define USART1_BRR          (*((volatile uint32_t *)(USART1_BASE + 0x0C)))
#define USART1_ISR          (*((volatile uint32_t *)(USART1_BASE + 0x1C)))
#define USART1_TDR          (*((volatile uint32_t *)(USART1_BASE + 0x28)))

// ==============================================================================
// FUNCTION DECLARATIONS
// ==============================================================================
void system_init(void);
void gpio_init(void);
void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *str);
void delay_ms(uint32_t ms);
void led_green_on(void);
void led_green_off(void);
void led_blue_on(void);
void led_blue_off(void);
void led_red_on(void);
void led_red_off(void);

// ==============================================================================
// MAIN PROGRAM
// ==============================================================================
int main(void) {
    system_init();
    gpio_init();
    uart_init();
    
    // Startup message
    uart_puts("\r\n");
    uart_puts("========================================\r\n");
    uart_puts("   STM32U575 NUCLEO Board\r\n");
    uart_puts("========================================\r\n");
    uart_puts("Board: NUCLEO-U575ZI-Q\r\n");
    uart_puts("CPU: ARM Cortex-M33\r\n");
    uart_puts("Flash: 2MB | SRAM: 786KB\r\n");
    uart_puts("========================================\r\n");
    uart_puts("\r\n");
    uart_puts("Starting LED Blink Demo...\r\n");
    uart_puts("LEDs: Green (PC7), Blue (PB7), Red (PG2)\r\n");
    uart_puts("\r\n");
    
    uint32_t counter = 0;
    
    while (1) {
        // === Pattern 1: Green LED ===
        led_green_on();
        led_blue_off();
        led_red_off();
        uart_puts("[");
        if (counter < 10) uart_putc('0');
        if (counter < 100) uart_putc('0' + (counter / 10) % 10);
        uart_putc('0' + counter % 10);
        uart_puts("] GREEN LED ON  | Blue: OFF | Red: OFF\r\n");
        delay_ms(1000);
        
        // === Pattern 2: Blue LED ===
        led_green_off();
        led_blue_on();
        led_red_off();
        uart_puts("[");
        if (counter < 10) uart_putc('0');
        if (counter < 100) uart_putc('0' + (counter / 10) % 10);
        uart_putc('0' + counter % 10);
        uart_puts("] Green: OFF | BLUE LED ON  | Red: OFF\r\n");
        delay_ms(1000);
        
        // === Pattern 3: Red LED ===
        led_green_off();
        led_blue_off();
        led_red_on();
        uart_puts("[");
        if (counter < 10) uart_putc('0');
        if (counter < 100) uart_putc('0' + (counter / 10) % 10);
        uart_putc('0' + counter % 10);
        uart_puts("] Green: OFF | Blue: OFF | RED LED ON\r\n");
        delay_ms(1000);
        
        // === Pattern 4: All OFF ===
        led_green_off();
        led_blue_off();
        led_red_off();
        uart_puts("[");
        if (counter < 10) uart_putc('0');
        if (counter < 100) uart_putc('0' + (counter / 10) % 10);
        uart_putc('0' + counter % 10);
        uart_puts("] ALL LEDs OFF\r\n");
        delay_ms(1000);
        
        // === Pattern 5: All ON ===
        led_green_on();
        led_blue_on();
        led_red_on();
        uart_puts("[");
        if (counter < 10) uart_putc('0');
        if (counter < 100) uart_putc('0' + (counter / 10) % 10);
        uart_putc('0' + counter % 10);
        uart_puts("] ALL LEDs ON!\r\n");
        delay_ms(1000);
        
        counter++;
        
        if (counter % 5 == 0) {
            uart_puts("\r\n--- Cycle ");
            uart_putc('0' + (counter / 5));
            uart_puts(" completed ---\r\n\r\n");
        }
    }
    
    return 0;
}

// ==============================================================================
// INITIALIZATION FUNCTIONS
// ==============================================================================
void system_init(void) {
    // Basic system initialization
    // Clock configuration would go here (simplified for Renode)
}

void gpio_init(void) {
    // Enable GPIO clocks
    RCC_AHB2ENR |= (1 << 1);  // GPIOB clock enable
    RCC_AHB2ENR |= (1 << 2);  // GPIOC clock enable
    RCC_AHB2ENR |= (1 << 6);  // GPIOG clock enable
    
    // Configure PB7 (Blue LED) as output
    GPIOB_MODER &= ~(3 << (7 * 2));  // Clear mode bits
    GPIOB_MODER |= (1 << (7 * 2));   // Set to output mode (01)
    
    // Configure PC7 (Green LED) as output
    GPIOC_MODER &= ~(3 << (7 * 2));
    GPIOC_MODER |= (1 << (7 * 2));
    
    // Configure PG2 (Red LED) as output
    GPIOG_MODER &= ~(3 << (2 * 2));
    GPIOG_MODER |= (1 << (2 * 2));
    
    // Turn all LEDs off initially
    led_green_off();
    led_blue_off();
    led_red_off();
}

void uart_init(void) {
    // Enable USART1 clock
    RCC_APB2ENR |= (1 << 14);
    
    // Configure USART1
    // For simplicity, we'll just enable it
    // Baud rate is not critical in simulation
    USART1_BRR = 0x683;  // Approx 115200 baud at 160MHz (simplified)
    
    // Enable USART: UE=1, TE=1
    USART1_CR1 = (1 << 0) | (1 << 3);
}

// ==============================================================================
// LED CONTROL FUNCTIONS
// ==============================================================================
void led_green_on(void) {
    GPIOC_BSRR = (1 << 7);  // Set PC7
}

void led_green_off(void) {
    GPIOC_BSRR = (1 << (7 + 16));  // Reset PC7
}

void led_blue_on(void) {
    GPIOB_BSRR = (1 << 7);  // Set PB7
}

void led_blue_off(void) {
    GPIOB_BSRR = (1 << (7 + 16));  // Reset PB7
}

void led_red_on(void) {
    GPIOG_BSRR = (1 << 2);  // Set PG2
}

void led_red_off(void) {
    GPIOG_BSRR = (1 << (2 + 16));  // Reset PG2
}

// ==============================================================================
// UART FUNCTIONS
// ==============================================================================
void uart_putc(char c) {
    // Wait for transmit data register empty
    // In Renode, this might not be necessary, but good practice
    while (!(USART1_ISR & (1 << 7)));
    USART1_TDR = c;
}

void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

// ==============================================================================
// DELAY FUNCTION
// ==============================================================================
void delay_ms(uint32_t ms) {
    // Simple delay loop (adjust multiplier as needed for Renode)
    for (volatile uint32_t i = 0; i < ms * 10000; i++) {
        __asm__("nop");
    }
}

// ==============================================================================
// RESET HANDLER & VECTOR TABLE
// ==============================================================================
void Reset_Handler(void) {
    main();
    while(1);
}

// Vector table
__attribute__((section(".isr_vector")))
const void *vectors[] = {
    (void *)0x200C0000,  // Initial stack pointer
    Reset_Handler,        // Reset handler
};