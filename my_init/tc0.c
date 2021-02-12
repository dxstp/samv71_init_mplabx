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
#include "tc0.h"

void TC0_init() {
    // disable PCK7
    PMC_REGS->PMC_SCDR = PMC_SCDR_PCK7_Msk;
    
    // select SLCK for PCK7
    PMC_REGS->PMC_PCK[7] = PMC_PCK_CSS_SLOW_CLK | PMC_PCK_PRES(0);
    
    // enable PCK7
    PMC_REGS->PMC_SCER = PMC_SCER_PCK7_Msk;
    
    // wait until PCK7 is ready
    while(!(PMC_REGS->PMC_SR & PMC_SR_PCKRDY7_Msk));
    
    // turn on peripheral clock for TC0
    PMC_REGS->PMC_PCER0 = PMC_PCER0_PID23_Msk;
    
    // use PCK7 for TC0
    MATRIX_REGS->CCFG_PCCR |= CCFG_PCCR_TC0CC(1);
        
    // use PCK7 from PMC
    TC0_REGS->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1;
    
    // select waveform mode and let timer reset if RC matches
    TC0_REGS->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVE(1) | TC_CMR_WAVEFORM_WAVSEL_UP_RC;
    
    // set RC compare value to have match condition every 100 ms
    TC0_REGS->TC_CHANNEL[0].TC_RC = 6554;    
    
    // enable TC0
    TC0_REGS->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG_Msk | TC_CCR_CLKEN_Msk;
    
    // wait until TC0 is enabled
    while(!(TC0_REGS->TC_CHANNEL[0].TC_SR & TC_SR_CLKSTA_Msk));
}
