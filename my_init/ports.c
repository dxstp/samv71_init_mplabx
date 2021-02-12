// DOM-IGNORE-BEGIN
/*
    (c) 2021 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */
// DOM-IGNORE-END

#include <xc.h>
#include "ports.h"


// VCOM PB4,PA21
// SW0 PA9
// LED0 PA23
// LED1 PC09
// WM8904 I2C: DAT PA3, CLK PA4
// WM8904 I2S: RD PA10, TF PB0, TK PB1, RF PD24, TD PD26, INT PD11
// WM8904 MCLK: PCK2 PA18



void PORTS_init() {
    // turn on peripheral clock for PIO controllers
    PMC_REGS->PMC_PCER0 = PMC_PCER0_PID10_Msk; // A
    PMC_REGS->PMC_PCER0 = PMC_PCER0_PID11_Msk; // B
    PMC_REGS->PMC_PCER0 = PMC_PCER0_PID12_Msk; // C
    PMC_REGS->PMC_PCER0 = PMC_PCER0_PID16_Msk; // D
    PMC_REGS->PMC_PCER0 = PMC_PCER0_PID17_Msk; // E
    
    
    // enable output for LED0, PA23
    PIOA_REGS->PIO_OER = PIO_OER_P23_Msk;
    PIOA_REGS->PIO_SODR = PIO_SODR_P23_Msk;
    
    // enable output for LED1, PC09
    PIOC_REGS->PIO_OER = PIO_OER_P9_Msk;
    PIOC_REGS->PIO_SODR = PIO_SODR_P9_Msk;
}

void LED0_On() {
    PIOA_REGS->PIO_CODR = PIO_CODR_P23_Msk;
}

void LED0_Off() {
    PIOA_REGS->PIO_SODR = PIO_SODR_P23_Msk;
}

void LED0_Toggle() {
    if(PIOA_REGS->PIO_ODSR & PIO_ODSR_P23_Msk) {
        PIOA_REGS->PIO_CODR = PIO_CODR_P23_Msk;
    } else {
        PIOA_REGS->PIO_SODR = PIO_SODR_P23_Msk;
    }
}

void LED1_On() {
    PIOC_REGS->PIO_CODR = PIO_CODR_P9_Msk;
}

void LED1_Off() {
    PIOC_REGS->PIO_SODR = PIO_SODR_P9_Msk;
}

void LED1_Toggle() {
    if(PIOC_REGS->PIO_ODSR & PIO_ODSR_P9_Msk) {
        PIOC_REGS->PIO_CODR = PIO_CODR_P9_Msk;
    } else {
        PIOC_REGS->PIO_SODR = PIO_SODR_P9_Msk;
    }
}