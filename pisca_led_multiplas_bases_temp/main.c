#include <msp430.h> 


/**
 * main.c
 */

// bases de tempo
unsigned int baseT1 = 4000;
unsigned int baseT2 = 6000;
unsigned int baseT3 = 10000;
unsigned int baseT4 = 16000;

unsigned int tmpOn = 2000;
int max = 60000;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= 0x0F; // inicializando as portas


	int i = 0;


    while(1)
    {
        if (i == max) // resetando contador para evitar estouro
            i = 0;

        if (i % tmpOn == 0) { //se tiver alcançado o tempo de duração do LED, ele é desligado

            if ((P1IN & BIT0) == BIT0)
                P1OUT ^= BIT0;
            else if (i % baseT1 == 0) // se não, ele será ligado em sua base de tempo
                P1OUT ^= BIT0;

            if ((P1IN & BIT1) == BIT1)
                P1OUT ^= BIT1;
            else if (i % baseT2 == 0)
                P1OUT ^= BIT1;

            if ((P1IN & BIT2) == BIT2)
                P1OUT ^= BIT2;
            else if (i % baseT3 == 0)
                P1OUT ^= BIT2;

            if ((P1IN & BIT3) == BIT3)
                P1OUT ^= BIT3;
            else if (i % baseT4 == 0)
                P1OUT ^= BIT3;
        }


        i++;
    }

	return 0;
}


// fazer divindo as bases se der o número inteiro, é hora do led ser piscado
void timerBase(){

}
