#include <msp430.h> 

#define CONST_TACCR0 62500;

/**
 * main.c
 */

// bases de tempo (em segundos)
unsigned int baseT1 = 2; //a cada 2s
unsigned int baseT2 = 3; // a cada 3s
unsigned int baseT3 = 5; // a cada 4s
unsigned int baseT4 = 6; // a cada 6s

unsigned int i = 0;
int max = 6;

// fazer divindo as bases se der o número inteiro, é hora do led ser piscado
void timerBase(){
    if (i % baseT1 == 0)
        P1OUT ^= BIT0;

    if (i % baseT2 == 0)
        P1OUT ^= BIT1;

    if (i % baseT3 == 0)
        P1OUT ^= BIT2;

    if (i % baseT4 == 0)
        P1OUT ^= BIT3;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // stop watchdog timer
    P1DIR = 0x0F; // inicializando as portas

    BCSCTL1 = CALBC1_1MHZ; // set clock to 1MHz
    DCOCTL = CALDCO_1MHZ;

    TACTL = TASSEL_2 + ID_3 + MC_3;
    // MC_1:  TACCR0 + 1
    // ID_0: 2^3 = 8

    TACCR0 = CONST_TACCR0; //tempo máximo possível do registrador CCR0

    _enable_interrupts();
    TACCTL0 = CCIE;

    return 0;
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void) {
    P1OUT = 0x00; //desligando os leds ligados!
    if (i == max){ // resetando contador para evitar estouro
      i = 0;
    }
    i += 1;
   timerBase();
   // P1OUT ^= BIT0;
}


