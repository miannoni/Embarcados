/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
  ** Entrega realizada em parceria com:
  **  - matteo
  **  - sabrina
  **  - https://youtu.be/fLjHUY5Kqgg
  
  
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"
#include <time.h>

/************************************************************************/
/* defines                                                              */
/************************************************************************/

 #define LED_PIO           PIOC                  // periferico que controla o LED
 #define LED_PIO_ID        12                    // ID do periférico PIOC (controla LED)
 #define LED_PIO_IDX       8u                    // ID do LED no PIO
 #define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// // Configuracoes do botao
#define BUT_PIO			PIOA
#define BUT_PIO_ID		10
#define BUT_PIO_IDX		11u
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

// // Configuracoes do botao amarelo
#define BUT_PIO_AM			PIOA
#define BUT_PIO_ID_AM		10
#define BUT_PIO_IDX_AM		6u
#define BUT_PIO_IDX_MASK_AM (1u << BUT_PIO_IDX_AM)

// // Configuracoes do botao vermelho
#define BUT_PIO_VR			PIOA
#define BUT_PIO_ID_VR		10
#define BUT_PIO_IDX_VR		2u
#define BUT_PIO_IDX_MASK_VR (1u << BUT_PIO_IDX_VR)

// Configuracoes do buzzer
#define BUZ_PIO			PIOA
#define BUZ_PIO_ID		10
#define BUZ_PIO_IDX		3u
#define BUZ_PIO_IDX_MASK (1u << BUZ_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

double freqtotime(double frequency) {
	return 1000000/frequency;
}


 

volatile Bool flag = true;
volatile Bool flagv = false;
int idx_nota = 0;

int comeca = 0;
int n = 2;
int i = 0;
double m[5][1000][2] = {{{8, 466.24},{8, 587.2},{8, 587.2},{8, 466.24},{8, 466.24},{4, 392.0},{4, -1},{8, 587.2},{8, 523.2},{8, 587.2},{8, 622.4},{8, 587.2},{8, 523.2},{8, 466.24},{8, 587.2},{8, 587.2},{8, 466.24},{8, 466.24},{4, 392.0},{4, -1},{8, 587.2},{8, 523.2},{8, 587.2},{8, 622.4},{8, 587.2},{8, 523.2},{8, 466.24},{8, 587.2},{8, 587.2},{8, 466.24},{8, 466.24},{4, 392.0},{4, -1},{8, 587.2},{8, 523.2},{8, 587.2},{8, 622.4},{8, 587.2},{8, 523.2},{8, 466.24},{8, 587.2},{8, 466.24},{8, -1},{8, 587.2},{8, 523.2},{8, 587.2},{8, 523.2},{-1, -1} }, 
	{{8, 830.72},{8, 830.72},{8, 415.36},{8, 415.36},{8, 622.4},{8, 622.4},{8, 415.36},{8, 415.36},{8, 830.72},{8, 830.72},{8, 659.2},{8, 493.92},{8, 739.84},{8, 739.84},{8, 369.92},{8, 369.92},{8, 830.72},{8, 830.72},{8, 415.36},{8, 415.36},{8, 622.4},{8, 622.4},{8, 415.36},{8, 415.36},{8, 830.72},{8, 830.72},{8, 659.2},{8, 493.92},{8, 739.84},{8, 739.84},{8, 369.92},{8, 369.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 554.24},{8, 493.92},{8, 554.24},{8, 493.92},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 622.4},{8, 659.2},{8, 622.4},{8, 659.2},{8, 622.4},{8, -1},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{2, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 369.92},{8, 369.92},{8, 369.92},{8, 830.72},{8, 622.4},{8, 554.24},{8, 622.4},{8, 659.2},{8, 622.4},{8, 554.24},{8, 622.4},{8, 659.2},{8, 622.4},{8, 554.24},{8, 493.92},{4, 466.24},{8, -1},{8, 415.36},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{8, 493.92},{-1, -1} },
		{
			{16, 659.2},
			{16, 659.2},
			{16, -1},
			{16, 659.2},
			{16, -1},
			{16, 523.2},
			{8, 659.2},
			{8, 784.0},
			{8, -1},
			{8, 392.0},
			{8, -1},
			{5, 523.2},
			{16, 392.0},
			{8, -1},
			{5, 329.6},
			{8, 440.0},
			{8, 493.92},
			{16, 466.24},
			{8, 440.0},
			{12, 392.0},
			{12, 329.6},
			{12, 784.0},
			{8, 880.0},
			{16, 698.56},
			{16, 784.0},
			{16, -1},
			{8, 659.2},
			{16, 523.2},
			{16, 587.2},
			{5, 493.92},
			{5, 523.2},
			{16, 392.0},
			{8, -1},
			{5, 329.6},
			{8, 440.0},
			{8, 493.92},
			{16, 466.24},
			{8, 440.0},
			{12, 392.0},
			{12, 329.6},
			{12, 784.0},
			{8, 880.0},
			{16, 698.56},
			{16, 784.0},
			{16, -1},
			{8, 659.2},
			{16, 523.2},
			{16, 587.2},
			{5, 493.92},
			{-1, -1} }};

int tocando = m[0];
/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

void musica(double musica[][2]){
	int ticks = 0;
	int delay = 40;
	while ((musica[idx_nota][0] != -1) && !flag) {
		if (musica[idx_nota][1] == -1) {
			delay_ms(3000/musica[idx_nota][0]);
			idx_nota++;
			} else {
			ticks = (int) (musica[idx_nota][1]/musica[idx_nota][0]) - delay/10;
			while (ticks > 0) {
				if (musica[idx_nota][1] != -1) {
					pio_clear(PIOA, BUZ_PIO_IDX_MASK);
				}
				delay_us((int) freqtotime(musica[idx_nota][1]));
				pio_set(PIOA, BUZ_PIO_IDX_MASK);
				delay_us((int) freqtotime(musica[idx_nota][1]));
				ticks--;
			}
			idx_nota++;
			delay_ms(delay);
			
		}	
	}
	if (musica[idx_nota][0] == -1){
	flag = false;
	}
}
/************************************************************************/
/* funcoes   
                                                        */
/************************************************************************/
void but_callback(void){
	flag = !flag;
	comeca += 1;
}


void but_callback_musica(void){
	flagv = true;
}
// Função de inicialização do uC
void init(void){
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);

	// Ativar PIO do Buzzer
	pmc_enable_periph_clk(BUZ_PIO_ID);
	
	//Inicializa PC8 como saída
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);

	//inicializa PA9 como saida
	pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	//pmc_enable_periph_clk(BUT_PIO_ID);
	//pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_DEFAULT);
	//pio_pull_up	(BUT_PIO, BUT_PIO_IDX_MASK, 1);
	
	// Inicializa PIO do botao amarelo
	pmc_enable_periph_clk(BUT_PIO_ID_AM);
	
	// Configura PIO para lidar com o pino do botão amarelo como entrada
	// com pull-up
	pio_configure(BUT_PIO_AM, PIO_INPUT, BUT_PIO_IDX_MASK_AM, PIO_PULLUP);
	
	
	// Configura interrupção no pino referente ao botao amarelo e associa
	// função de callback caso uma interrupção for gerada
	// a função de callback é a: but_callback()
	pio_handler_set(BUT_PIO_AM,
	BUT_PIO_ID_AM,
	BUT_PIO_IDX_MASK_AM,
	PIO_IT_FALL_EDGE,
	but_callback);
	
	// Ativa interrupção
	pio_enable_interrupt(BUT_PIO_AM, BUT_PIO_IDX_MASK_AM);

	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais próximo de 0 maior)
	NVIC_EnableIRQ(BUT_PIO_ID_AM);
	NVIC_SetPriority(BUT_PIO_ID_AM, 1); // Prioridade 4
	
	
	// Inicializa PIO do botao amarelo
	pmc_enable_periph_clk(BUT_PIO_ID_VR);
	
	// Configura PIO para lidar com o pino do botão amarelo como entrada
	// com pull-up
	pio_configure(BUT_PIO_VR, PIO_INPUT, BUT_PIO_IDX_MASK_VR, PIO_PULLUP);
	
	
	// Configura interrupção no pino referente ao botao amarelo e associa
	// função de callback caso uma interrupção for gerada
	// a função de callback é a: but_callback()
	pio_handler_set(BUT_PIO_VR,
	BUT_PIO_ID_VR,
	BUT_PIO_IDX_MASK_VR,
	PIO_IT_FALL_EDGE,
	but_callback_musica);
	
	// Ativa interrupção
	pio_enable_interrupt(BUT_PIO_VR, BUT_PIO_IDX_MASK_VR);

	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais próximo de 0 maior)
	NVIC_EnableIRQ(BUT_PIO_ID_VR);
	NVIC_SetPriority(BUT_PIO_ID_VR, 0); // Prioridade 4

	
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	// Initialize the board clock
	sysclk_init();
	
	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	init();

  
  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	pio_set(PIOA, BUZ_PIO_IDX_MASK);
	if (flagv){
		pio_set(PIOA, BUZ_PIO_IDX_MASK);
		if (i<n){
			i += 1;
		}
		else{
			i = 0;
			
		}
		idx_nota = 0;
		tocando = m[i];
		flagv = false;
		
	}
	if (comeca > 1){
		musica(tocando);
	}
	
	
	
	
	/*
	if (flag) {
		pio_set(PIOA, BUZ_PIO_IDX_MASK);
		//pio_clear(PIOA, BUZ_PIO_IDX_MASK);
	} else {
		musica(Havana);
		
	}
	*/
	//pio_set(PIOC, LED_PIO_IDX_MASK);      // Coloca 1 no pino LED
    //delay_ms(200);                   // Delay por software de 200 ms
    //pio_clear(PIOC, LED_PIO_IDX_MASK);    // Coloca 0 no pino do LED
    //delay_ms(200);                   // Delay por software de 200 ms
	//ticks++;
  }
  return 0;
}
