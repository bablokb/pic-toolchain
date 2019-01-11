; --------------------------------------------------------------------------
; Sample project uart_rxtx
;
; Author: B-bablok
; https://github.com/bablokb/pic-toolchain
;
; --------------------------------------------------------------------------
#include   <P12f675.INC>

        global  _delay_208, _delay_416, _delay_833

        udata_ovr
count	res 1

        code

_delay_208
        ;; cycle calculation:
        ;; - call 1
        ;; - init 4
        ;; - loop (2+3)*(count-1)
        ;; - last decfsz 2
        ;; - return 1
        
       	movlw D'41'
	movwf count
        nop
        nop
        
loop1   nop
        nop
        decfsz count, 1
        goto  loop1
        return

_delay_416
        ;; cycle calculation:
        ;; - call 1
        ;; - init 2
        ;; - loop (2+3)*(count-1)
        ;; - last decfsz 2
        ;; - return 1
        
       	movlw D'83'
	movwf count
        
loop2   nop
        nop
        decfsz count, 1
        goto  loop2
        return

_delay_833
        ;; cycle calculation:
        ;; - call 1
        ;; - init 4
        ;; - loop (2+3)*(count-1)
        ;; - last decfsz 2
        ;; - return 1
        
       	movlw D'166'
	movwf count
        nop
        nop
        
loop3   nop
        nop
        decfsz count, 1
        goto  loop3
        return

        end
