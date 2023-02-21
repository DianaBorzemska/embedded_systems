#include <stdint.h>
 
typedef volatile struct {
 uint32_t DR;
 uint32_t RSR_ECR;
 uint8_t reserved1[0x10];
 const uint32_t FR;
 uint8_t reserved2[0x4];
 uint32_t LPR;
 uint32_t IBRD;
 uint32_t FBRD;
 uint32_t LCR_H;
 uint32_t CR;
 uint32_t IFLS;
 uint32_t IMSC;
 const uint32_t RIS;
 const uint32_t MIS;
 uint32_t ICR;
 uint32_t DMACR;
} pl011_T;
 
 struct State {
  unsigned long Out;
  unsigned long Time; 
  unsigned long Next[4];};
typedef const struct State STyp;

#define goN   0
#define waitN 1
#define goE   2
#define waitE 3

STyp FSM[4]={
 {0x21,3000,{goN,waitN,goN,waitN}},
 {0x22, 500,{goE,goE,goE,goE}},
 {0x0C,3000,{goE,goE,waitE,waitE}},
 {0x14, 500,{goN,goN,goN,goN}}};

unsigned long S; 

unsigned long Input=0;

enum {
 RXFE = 0x10,
 TXFF = 0x20,
};
 
pl011_T * const UART0 = (pl011_T *)0x101f1000;
pl011_T * const UART1 = (pl011_T *)0x101f2000;
pl011_T * const UART2 = (pl011_T *)0x101f3000;

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
 
static void uart_echo(pl011_T *uart) {
 if ((uart->FR & RXFE) == 0) {
    char ch = uart->DR;
    while(uart->FR & TXFF);
        uart->DR = ch;
    if(ch=='n' || ch=='N'){
            Input = 2; 
          }
    else if(ch =='e' || ch=='E'){
    Input = 1;
    
    }
    else if(ch=='b' || ch=='B'){
    Input = 3;
    
    }
    else{
    Input = 0;
    
    }
 }
}

void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}
//run the program using: qemu-system-arm -M versatilepb -m 128M -kernel task3.bin -serial stdio
void c_entry() {
    char data[200];
    int oldOutput = 0;
    S = goN;
    while(1){
        int lights = FSM[S].Out; 
        if(oldOutput != lights){
            oldOutput=lights;
            if(lights == 34){
                print_uart0("Yellow north and red east.\n");
            }
            else if(lights == 33){
                print_uart0("Green north and red east.\n");
            }
            else if(lights == 20){
                print_uart0("Red north and yellow east.\n");
            }
            else{
                print_uart0("Red north and green east.\n");
            }
        }

        uart_echo(UART0);

    S = FSM[S].Next[Input];
    }      
    //}
 }
