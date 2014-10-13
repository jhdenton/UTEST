/* Unit Testing Port File */



/* ADD PLATFORM CONFIGURATION HERE */
_FOSCSEL(FNOSC_PRI)
_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_HS)
_FWDT(FWDTEN_OFF)
/* ADD PLATFORM CONFIGURATION HERE */


/* ADD PLATFORM PORT INITIALIZATION HERE */
/**
	This function is platform-specific and should handle any necessary system
	hardware and/or peripheral initialization. It takes no parameters and has
	no return value.
*/
void utest_init(void)
{
	/* Setup RA0 as Vref input */
	LATAbits.LATA0 = 1U;
	TRISAbits.TRISA0 = 1U;

	/* Setup RA1 as Vref- input */
	LATAbits.LATA1 = 1U;
	TRISAbits.TRISA1 = 1U;

	/* Setup RA2-RA3 as don't care inputs (special function - oscillator) */
	LATAbits.LATA2 = 1U;
	LATAbits.LATA3 = 1U;
	TRISAbits.TRISA2 = 1U;
	TRISAbits.TRISA3 = 1U;

	/* Setup RA4 as don't care input */
	LATAbits.LATA4 = 1U;
	TRISAbits.TRISA4 = 1U;

	/* Setup RA7 as Ext_Clr input */
	LATAbits.LATA7 = 0U;
	TRISAbits.TRISA7 = 1U;

	/* Setup RA8, RA9 as don't care inputs */
	LATAbits.LATA8 = 1U;
	TRISAbits.TRISA8 = 1U;
	LATAbits.LATA9 = 1U;
	TRISAbits.TRISA9 = 1U;

	/* Setup RA10 as LED output */
	LATAbits.LATA10 = 1U;
	TRISAbits.TRISA10 = 0U;

	/* Setup RB0-RB1 as don't care inputs (special function - programming pins) */
	LATBbits.LATB0 = 0U;
	LATBbits.LATB1 = 0U;
	TRISBbits.TRISB0 = 1U;
	TRISBbits.TRISB1 = 1U;

	/* Setup RB2-RB3 as don't care inputs (special function - analog inputs) */
	LATBbits.LATB2 = 0U;
	LATBbits.LATB3 = 0U;
	TRISBbits.TRISB2 = 1U;
	TRISBbits.TRISB3 = 1U;

	/* Setup RB4 as don't care input */
	LATBbits.LATB4 = 1U;
	TRISBbits.TRISB4 = 1U;

	/* Setup RB5-RB6 as capture inputs */
	LATBbits.LATB5 = 0U;
	LATBbits.LATB6 = 0U;
	TRISBbits.TRISB5 = 1U;
	TRISBbits.TRISB6 = 1U;

	/* Setup RB7 as Watchdog output */
	LATBbits.LATB7 = 0U;
	TRISBbits.TRISB7 = 0U;

	/* Setup RB8-RB9 as don't care inputs (special function - I2C) */
	LATBbits.LATB8 = 0U;
	LATBbits.LATB9 = 0U;
	TRISBbits.TRISB8 = 1U;
	TRISBbits.TRISB9 = 1U;

	/* Setup RB10-RB11 as capture inputs */
	LATBbits.LATB10 = 0U;
	LATBbits.LATB11 = 0U;
	TRISBbits.TRISB10 = 1U;
	TRISBbits.TRISB11 = 1U;

	/* Setup RB12-RB15 as don't care input */
	LATBbits.LATB12 = 1U;
	TRISBbits.TRISB12 = 1U;
	LATBbits.LATB13 = 1U;
	TRISBbits.TRISB13 = 1U;
	LATBbits.LATB14 = 1U;
	TRISBbits.TRISB14 = 1U;
	LATBbits.LATB15 = 1U;
	TRISBbits.TRISB15 = 1U;

	/* Setup RC0 as don't care input (special function - analog input) */
	LATCbits.LATC0 = 0U;
	TRISCbits.TRISC0 = 1U;

	/* Setup RC1 as Hall_M1C Input */
	LATCbits.LATC1 = 1U;
	TRISCbits.TRISC1 = 1U;

	/* Setup RC2 as Hall_M2C Input */
	LATCbits.LATC2 = 1U;
	TRISCbits.TRISC2 = 1U;

	/* Setup RC3 as PBIT_Done output */
	LATCbits.LATC3 = 1U;
	TRISCbits.TRISC3 = 0U;

	/* Setup RC4 as don't care input (special function - UART TX) */
	LATCbits.LATC4 = 0U;
	TRISCbits.TRISC4 = 1U;

	/* Setup RC5 as OS_Status output */
	LATCbits.LATC5 = 1U;
	TRISCbits.TRISC5 = 0U;

	/* Setup RC6 as nDIR/TP15 input */
	LATCbits.LATC6 = 1U;
	TRISCbits.TRISC6 = 1U;

	/* Setup RC7 as TS_Control output */
	LATCbits.LATC7 = 0U;
	TRISCbits.TRISC7 = 0U;

	/* Setup RC8 as BS_Control output */
	LATCbits.LATC8 = 0U;
	TRISCbits.TRISC8 = 0U;

	/* Setup RC9 as OVS_Control output */
	LATCbits.LATC9 = 0U;
	TRISCbits.TRISC9 = 0U;

	/* Setup RP20 as UART2 TX */
	RPOR10bits.RP20R = 5U;

	/* bit 15 UARTEN: 1 = UARTx is enabled; 0 = UARTx is disabled; */
	/* bit 14 Unimplemented */
	/* bit 13 USIDL: 0 = Continue operation in Idle mode */
	/* bit 12 IREN: 0 = IrDA encoder and decoder are disabled */
	/* bit 11 RTSMD: 0 = UxRTS is in Flow Control mode */
	/* bit 10 Unimplemented */
	/* bit 9-8 UEN<1:0>: 00 = UxTX and UxRX pins are enabled and used; UxCTS, */
	/*						UxRTS and BCLKx pins controlled by port latches */
	/* bit 7 WAKE: 0 = Wake-up is disabled */
	/* bit 6 LPBACK: 0 = Loopback mode is disabled */
	/* bit 5 ABAUD: 0 = Baud rate measurement disabled or completed */
	/* bit 4 URXINV: 0 = UxRX Idle state is ‘1’ */
	/* bit 3 BRGH: 0 = Low-speed mode */
	/* bit 2-1 PDSEL<1:0>: 00 = 8-bit data, no parity */
	/* bit 0 STSEL: 0 = 1 Stop bit */

	U2MODEbits.UARTEN = 0U;
	U2MODEbits.USIDL  = 0U;
	U2MODEbits.IREN   = 0U;
	U2MODEbits.RTSMD  = 0U;
	U2MODEbits.UEN    = 0U;
	U2MODEbits.WAKE   = 0U;
	U2MODEbits.LPBACK = 0U;
	U2MODEbits.ABAUD  = 0U;
	U2MODEbits.URXINV = 0U;
	U2MODEbits.BRGH   = 0U;
	/* SRD588 */
	U2MODEbits.PDSEL  = 0U;
	/* SRD588 */
	U2MODEbits.STSEL  = 0U;

	/* Load a value into Baud Rate Generator. */
	/* U2BRG = (Fcy / (16 * BaudRate)) - 1 */
	/*         ((20MHz/2) / (16*9600)) - 1 = 64 */
	/* SRD588 */
	U2BRG = 10U;


	/* bit 15,13 UTXISEL<1:0>: 00 = Interrupt generated when any character is transferred to the Transmit Shift register */
	/* bit 14 UTXINV: 0 = UxTX Idle state is ‘1’ */
	/* bit 12 Unimplemented */
	/* bit 11 UTXBRK: 0 = Sync Break transmission is disabled or completed */
	/* bit 10 UTXEN: 0 = UARTx transmitter disabled; any pending transmission is aborted and the buffer is reset; */
	/* 				UxTX pin is controlled by PORT; */
	/* 				 1 = UARTx transmitter enabled; UxTX pin is controlled by UARTx (if UARTEN = 1) */
	/* bit 9 UTXBF: Transmit Buffer Full Status bit (read-only) */
	/* bit 8 TRMT: Transmit Shift Register is Empty bit (read-only) */
	/* bit 7-6 URXISEL<1:0>: 0x = Interrupt flag bit is set when a character is received */
	/* bit 5 ADDEN: 0 = Address Detect mode disabled */
	/* bit 4 RIDLE: Receiver Idle bit (read-only) */
	/* bit 3 PERR: Parity Error Status bit (read-only) */
	/* bit 2 FERR: Framing Error Status bit (read-only) */
	/* bit 1 OERR: Receive Buffer Overrun Error Status bit (clear/read-only) */
	/* bit 0 URXDA: Receive Buffer Data Available bit (read-only) */

	U2STAbits.UTXISEL1 = 0U;
	U2STAbits.UTXISEL0 = 0U;
	U2STAbits.UTXINV   = 0U;
	U2STAbits.UTXBRK   = 0U;
	U2STAbits.UTXEN    = 0U;
	U2STAbits.URXISEL  = 0U;
	U2STAbits.ADDEN    = 0U;

	/* And turn the peripheral on */
	U2MODEbits.UARTEN  = 1U;
	U2STAbits.UTXEN    = 1U;
}
/* ADD PLATFORM PORT INITIALIZATION HERE */


/* ADD PLATFORM PORT STDOUT FUNCTIONALITY HERE */
/**
	This function is platform-specific and should handle outputting
	the specified string on the desired test output peripheral.
	Any other occassional activities (e.g. watchdog timer) may also
	be handled here. It has no return value.
	@param [in] buf A pointer to a null-terminated character array
*/
void utest_puts(char* buf)
{
	int i;
	LATBbits.LATB7 ^= 1U;	/* Toggle Watchdog */
	i = 0;
	while (buf[i] != 0)
	{
		while (0 != U2STAbits.UTXBF);
		U2TXREG = buf[i];
		i++;
	}
}
/* ADD PLATFORM PORT STDOUT FUNCTIONALITY HERE */
