//Stepper Motor Program:
//P0.16 to P0.19 are connected to Windings of SMotor
#include <lpc214x.h>
#define LED_OFF (IO0SET = 1U << 31)
#define LED_ON (IO0CLR = 1U << 31)


void rotate_clock(int);
void rotate_anticlock(int);
void delay_ms(unsigned int j);
void SystemInit(void);

int main()
{
//unsigned int no_of_steps_clk = 1000, no_of_steps_aclk = 1000;
	IO0DIR |= 1U << 31 | 0x00FF0000 | 1U << 30; 
	LED_ON; 
	delay_ms(500);
	LED_OFF; // make D7 Led on .. just indicate the program is running
	SystemInit( );
	rotate_clock(1000);
	rotate_anticlock(1000);

	IO0CLR = 0X00FF0000;
	while(1);
}




