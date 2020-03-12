#include <lpc214x.h>
#define PLOCK 0x00000400
#define RS_ON (IO0SET = 1U << 20)
#define RS_OFF (IO0CLR = 1U << 20)
#define EN_ON (IO1SET = 1U << 25)
#define EN_OFF (IO1CLR = 1U << 25)
void SystemInit(void);
void delay_ms(unsigned int j);//millisecond delay
 void delay_us(unsigned int count);//microsecond delay
 void LCD_SendCmdSignals(void);
 void LCD_SendDataSignals(void);
 void LCD_SendHigherNibble(unsigned char dataByte);
 void LCD_CmdWrite( unsigned char cmdByte);
 void LCD_DataWrite( unsigned char dataByte);
 void LCD_Reset(void);
 void LCD_Init(void);
void LCD_DisplayString(const char *ptr_stringPointer_u8);
 void LCD_CmdWrite( unsigned char cmdByte)
{
LCD_SendHigherNibble(cmdByte);
LCD_SendCmdSignals();
cmdByte = cmdByte << 4;
LCD_SendHigherNibble(cmdByte);
LCD_SendCmdSignals();
}
 void LCD_DataWrite( unsigned char dataByte)
{
LCD_SendHigherNibble(dataByte);
LCD_SendDataSignals();
dataByte = dataByte << 4;
LCD_SendHigherNibble(dataByte);
LCD_SendDataSignals();
}
 void LCD_Reset(void)
{
/* LCD reset sequence for 4-bit mode*/
LCD_SendHigherNibble(0x30);
LCD_SendCmdSignals();
delay_ms(100);
LCD_SendHigherNibble(0x30);
LCD_SendCmdSignals();
delay_us(200);
LCD_SendHigherNibble(0x30);
LCD_SendCmdSignals();
delay_us(200);
LCD_SendHigherNibble(0x20);
LCD_SendCmdSignals();
delay_us(200);
}
 void LCD_SendHigherNibble(unsigned char dataByte)
{
//send the D7,6,5,D4(uppernibble) to P0.16 to P0.19
IO0CLR = 0X000F0000;IO0SET = ((dataByte >>4) & 0x0f) << 16;
}
 void LCD_SendCmdSignals(void)
{
RS_OFF; // RS - 1
EN_ON;delay_us(100);EN_OFF; // EN - 1 then 0
}
void LCD_SendDataSignals(void)
{
RS_ON;// RS - 1
EN_ON;delay_us(100);EN_OFF; // EN - 1 then 0
}
 void LCD_Init(void)
{
delay_ms(100);
LCD_Reset();
LCD_CmdWrite(0x28u); //Initialize the LCD for 4-bit 5x7 matrix type
LCD_CmdWrite(0x0Eu); // Display ON cursor ON
LCD_CmdWrite(0x01u); //Clear the LCD
LCD_CmdWrite(0x80u); //go to First line First Position
}
void LCD_DisplayString(const char *ptr_string)
{
// Loop through the string and display char by char
while((*ptr_string)!=0)
LCD_DataWrite(*ptr_string++);
}
 void delay_us(unsigned int count)
{
unsigned int j=0,i=0;
for(j=0;j<count;j++)
{
for(i=0;i<10;i++);
}
}
void SystemInit(void)
{
PLL0CON = 0x01;
PLL0CFG = 0x24;
PLL0FEED = 0xAA;
PLL0FEED = 0x55;
while( !( PLL0STAT & PLOCK ))
{ ; }
PLL0CON = 0x03;
PLL0FEED = 0xAA; // lock the PLL registers after setting the required PLL
PLL0FEED = 0x55;
VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz
}
void delay_ms(unsigned int j)
{
unsigned int x,i;
for(i=0;i<j;i++)
{
for(x=0; x<10000; x++);
}
}