;/*
;THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES INC. ``AS IS'' AND ANY EXPRESS OR
;IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
;MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT, ARE
;DISCLAIMED. IN NO EVENT SHALL ANALOG DEVICES INC. BE LIABLE FOR ANY DIRECT,
;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
;ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;POSSIBILITY OF SUCH DAMAGE.
;
;YOU ASSUME ANY AND ALL RISK FROM THE USE OF THIS CODE OR SUPPORT FILE.
;
;IT IS THE RESPONSIBILITY OF THE PERSON INTEGRATING THIS CODE INTO AN APPLICATION
;TO ENSURE THAT THE RESULTING APPLICATION PERFORMS AS REQUIRED AND IS SAFE.
;
;    Module       : startup_ADuCM320i.s
;    Description  : Cortex-M3 startup file - ADuCM320i - EWARM Version
;    Date         : Monday January 04 2016 16:29
;    Version      : v0.2
;*/



         MODULE  ?cstartup

         ;; Forward declaration of sections.
         SECTION CSTACK:DATA:NOROOT(3)

         SECTION .intvec:CODE:NOROOT(2)

         EXTERN  __iar_program_start
         PUBLIC  __vector_table

         DATA
__vector_table
         DCD     sfe(CSTACK)                       ; Top of Stack
         DCD     __iar_program_start               ; Reset Handler

         DCD     Nmi_Handler                       ; The NMI handler   
         DCD     Fault_Handler                     ; The hard fault handler 
         DCD     MemManage_Handler                 ; The MPU fault handler  
         DCD     BusFault_Handler                  ; The bus fault handler  
         DCD     UsageFault_Handler                ; The usage fault handler
         DCD     0                                 ; Reserved               
         DCD     0                                 ; Reserved               
         DCD     0                                 ; Reserved               
         DCD     0                                 ; Reserved               
         DCD     SVC_Handler                       ; SVCall handler         
         DCD     DebugMon_Handler                  ; Debug monitor handler  
         DCD     0                                 ; Reserved               
         DCD     PendSV_Handler                    ; The PendSV handler     
         DCD     SysTick_Handler                   ; The SysTick handler    

         ; External Interrupts
         DCD     WakeUp_Int_Handler        ; Wakeup Timer Interrupt        [ 0]
         DCD     Ext_Int0_Handler          ; External Interrupt 0          [ 1]
         DCD     Ext_Int1_Handler          ; External Interrupt 1          [ 2]
         DCD     Ext_Int2_Handler          ; External Interrupt 2          [ 3]
         DCD     Ext_Int3_Handler          ; External Interrupt 3          [ 4]
         DCD     Ext_Int4_Handler          ; External Interrupt 4          [ 5]
         DCD     Ext_Int5_Handler          ; External Interrupt 5          [ 6]
         DCD     Ext_Int6_Handler          ; External Interrupt 6          [ 7]
         DCD     Ext_Int7_Handler          ; External Interrupt 7          [ 8]
         DCD     Ext_Int8_Handler          ; External Interrupt 8          [ 9]
         DCD     WDog_Tmr_Int_Handler      ; Watchdog Timer Interrupt      [10]
         DCD     UnUsed_Handler            ; Reserved                      [11]
         DCD     UnUsed_Handler            ; Reserved                      [12]
         DCD     LV0_Int_Handler           ; Low Voltage Die Interrupt 0   [13]
         DCD     MDIO_Int_Handler          ; MDIO Interrupt                [14]
         DCD     GP_Tmr0_Int_Handler       ; Timer0 Interrupt              [15]
         DCD     GP_Tmr1_Int_Handler       ; Timer1 Interrupt              [16]
         DCD     Flsh_Int_Handler          ; Flash Memory Interrupt        [17]
         DCD     UART_Int_Handler          ; UART Interrupt                [18]
         DCD     SPI0_Int_Handler          ; SPI0 Interrupt                [19]
         DCD     SPI1_Int_Handler          ; SPI1 Interrupt                [20]
         DCD     I2C0_Slave_Int_Handler    ; I2C0 Slave Interrupt          [21]
         DCD     I2C0_Master_Int_Handler   ; I2C0 Master Interrupt         [22]
         DCD     PLA0_Int_Handler          ; PLA0 Interrupt                [23]
         DCD     PLA1_Int_Handler          ; PLA1 Interrupt                [24]
         DCD     DMA_Err_Int_Handler       ; DMA Error Interrupt           [25]
         DCD     DMA_SPI0_TX_Int_Handler   ; DMA SPI0 TX Interrupt         [26]
         DCD     DMA_SPI0_RX_Int_Handler   ; DMA SPI0 RX Interrupt         [27]
         DCD     DMA_SPI1_TX_Int_Handler   ; DMA SPI1 TX Interrupt         [28]
         DCD     DMA_SPI1_RX_Int_Handler   ; DMA SPI1 RX Interrupt         [29]
         DCD     DMA_UART_TX_Int_Handler   ; DMA UART TX Interrupt         [30]
         DCD     DMA_UART_RX_Int_Handler   ; DMA UART RX Interrupt         [31]
         DCD     DMA_I2C0_STX_Int_Handler  ; DMA I2C0 Slave TX Interrupt   [32]
         DCD     DMA_I2C0_SRX_Int_Handler  ; DMA I2C0 Slave RX Interrupt   [33]
         DCD     DMA_I2C0_M_Int_Handler    ; DMA I2C0 Master Interrupt     [34]
         DCD     DMA_I2C1_STX_Int_Handler  ; DMA I2C1 Slave TX Interrupt   [35]
         DCD     DMA_I2C1_SRX_Int_Handler  ; DMA I2C1 Slave RX Interrupt   [36]
         DCD     DMA_I2C1_M_Int_Handler    ; DMA I2C1 Master Interrupt     [37]
         DCD     DMA_ADC_Int_Handler       ; DMA ADC Interrupt             [38]
         DCD     DMA_Flsh_Int_Handler      ; DMA Flash Interrupt           [39]
         DCD     UnUsed_Handler            ; Reserved                      [40]
         DCD     UnUsed_Handler            ; Reserved                      [41]
         DCD     UnUsed_Handler            ; Reserved                      [42]
         DCD     UnUsed_Handler            ; Reserved                      [43]
         DCD     I2C1_Slave_Int_Handler    ; I2C1 Slave Interrupt          [44]
         DCD     I2C1_Master_Int_Handler   ; I2C1 Master Interrupt         [45]
         DCD     PLA2_Int_Handler          ; PLA2 Interrupt                [46]
         DCD     PLA3_Int_Handler          ; PLA3 Interrupt                [47]
         DCD     GP_Tmr2_Int_Handler       ; Timer2 Interrupt              [48]
         DCD     LV1_Int_Handler           ; Low Voltage Die Interrupt 1   [49]
         DCD     PWMTrip_Int_Handler       ; PWM TRIP Interrupt            [50]
         DCD     PWM0_Int_Handler          ; PWM Channel Pair 0 interrupt  [51]
         DCD     PWM1_Int_Handler          ; PWM Channel Pair 1 interrupt  [52]
         DCD     PWM2_Int_Handler          ; PWM Channel Pair 2 interrupt  [53]
         DCD     PWM3_Int_Handler          ; PWM Channel Pair 3 interrupt  [54]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
         PUBWEAK SysTick_Handler
         PUBWEAK Nmi_Handler
         PUBWEAK Fault_Handler
         PUBWEAK MemManage_Handler
         PUBWEAK BusFault_Handler
         PUBWEAK UsageFault_Handler
         PUBWEAK SVC_Handler
         PUBWEAK DebugMon_Handler
         PUBWEAK PendSV_Handler
         PUBWEAK WakeUp_Int_Handler          
         PUBWEAK Ext_Int0_Handler            
         PUBWEAK Ext_Int1_Handler            
         PUBWEAK Ext_Int2_Handler            
         PUBWEAK Ext_Int3_Handler            
         PUBWEAK Ext_Int4_Handler            
         PUBWEAK Ext_Int5_Handler            
         PUBWEAK Ext_Int6_Handler            
         PUBWEAK Ext_Int7_Handler            
         PUBWEAK Ext_Int8_Handler            
         PUBWEAK WDog_Tmr_Int_Handler        
         PUBWEAK LV0_Int_Handler             
         PUBWEAK MDIO_Int_Handler            
         PUBWEAK GP_Tmr0_Int_Handler         
         PUBWEAK GP_Tmr1_Int_Handler         
         PUBWEAK Flsh_Int_Handler            
         PUBWEAK UART_Int_Handler            
         PUBWEAK SPI0_Int_Handler            
         PUBWEAK SPI1_Int_Handler            
         PUBWEAK I2C0_Slave_Int_Handler      
         PUBWEAK I2C0_Master_Int_Handler     
         PUBWEAK PLA0_Int_Handler            
         PUBWEAK PLA1_Int_Handler            
         PUBWEAK DMA_Err_Int_Handler         
         PUBWEAK DMA_SPI0_TX_Int_Handler     
         PUBWEAK DMA_SPI0_RX_Int_Handler     
         PUBWEAK DMA_SPI1_TX_Int_Handler     
         PUBWEAK DMA_SPI1_RX_Int_Handler     
         PUBWEAK DMA_UART_TX_Int_Handler     
         PUBWEAK DMA_UART_RX_Int_Handler     
         PUBWEAK DMA_I2C0_STX_Int_Handler    
         PUBWEAK DMA_I2C0_SRX_Int_Handler    
         PUBWEAK DMA_I2C0_M_Int_Handler      
         PUBWEAK DMA_I2C1_STX_Int_Handler    
         PUBWEAK DMA_I2C1_SRX_Int_Handler    
         PUBWEAK DMA_I2C1_M_Int_Handler      
         PUBWEAK DMA_ADC_Int_Handler         
         PUBWEAK DMA_Flsh_Int_Handler        
         PUBWEAK I2C1_Slave_Int_Handler      
         PUBWEAK I2C1_Master_Int_Handler     
         PUBWEAK PLA2_Int_Handler            
         PUBWEAK PLA3_Int_Handler            
         PUBWEAK GP_Tmr2_Int_Handler         
         PUBWEAK LV1_Int_Handler             
         PUBWEAK PWMTrip_Int_Handler         
         PUBWEAK PWM0_Int_Handler            
         PUBWEAK PWM1_Int_Handler            
         PUBWEAK PWM2_Int_Handler            
         PUBWEAK PWM3_Int_Handler            

         PUBWEAK UnUsed_Handler


         THUMB
         SECTION .text:CODE:REORDER:NOROOT(1)
Nmi_Handler
Fault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
WakeUp_Int_Handler
Ext_Int0_Handler
Ext_Int1_Handler
Ext_Int2_Handler
Ext_Int3_Handler
Ext_Int4_Handler
Ext_Int5_Handler
Ext_Int6_Handler
Ext_Int7_Handler
Ext_Int8_Handler
WDog_Tmr_Int_Handler
LV0_Int_Handler
MDIO_Int_Handler
GP_Tmr0_Int_Handler
GP_Tmr1_Int_Handler
Flsh_Int_Handler
UART_Int_Handler
SPI0_Int_Handler
SPI1_Int_Handler
I2C0_Slave_Int_Handler
I2C0_Master_Int_Handler
PLA0_Int_Handler
PLA1_Int_Handler
DMA_Err_Int_Handler
DMA_SPI0_TX_Int_Handler
DMA_SPI0_RX_Int_Handler
DMA_SPI1_TX_Int_Handler
DMA_SPI1_RX_Int_Handler
DMA_UART_TX_Int_Handler
DMA_UART_RX_Int_Handler
DMA_I2C0_STX_Int_Handler
DMA_I2C0_SRX_Int_Handler
DMA_I2C0_M_Int_Handler
DMA_I2C1_STX_Int_Handler
DMA_I2C1_SRX_Int_Handler
DMA_I2C1_M_Int_Handler
DMA_ADC_Int_Handler
DMA_Flsh_Int_Handler
I2C1_Slave_Int_Handler
I2C1_Master_Int_Handler
PLA2_Int_Handler
PLA3_Int_Handler
GP_Tmr2_Int_Handler
LV1_Int_Handler
PWMTrip_Int_Handler
PWM0_Int_Handler
PWM1_Int_Handler
PWM2_Int_Handler
PWM3_Int_Handler
UnUsed_Handler
         B UnUsed_Handler

         END


