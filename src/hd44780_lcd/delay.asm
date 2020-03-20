; --------------------------------------------------------------------------
; Sample project hd44780_lcd
;
; Author: B-bablok
; https://github.com/bablokb/pic-toolchain/src/hd44780_lcd
;
; --------------------------------------------------------------------------
#include   <P12f675.INC>

        global  _delay_10, _delay_150, _delay_1000, _delay_ms

        udata_ovr
count	res 1
count2	res 1

        code

; --------------------------------------------------------------------------
_delay_10
        ;; cycle calculation:
        ;; - call:                  2
        ;; - 3 x goto:              6
        ;; - return                 2
        
       	goto $+1
       	goto $+1
       	goto $+1
        return

; --------------------------------------------------------------------------
_delay_150
        ;; cycle calculation:
        ;; - call:                  2
        ;; - init:                  3
        ;; - loop (1+2)*(count-1) 141 = 3*47
        ;; - last decfsz 2          2
        ;; - return                 2
        
       	movlw D'48'
	movwf count
        nop

d_150   decfsz count, 1
        goto d_150
        return
        

; --------------------------------------------------------------------------
_delay_1000
        ;; cycle calculation:
        ;; - call:                         2
        ;; - init1:                        2
        ;; - loop: (2+1+2)*(count-1)     990 = 198*5
        ;; - last:  (2+2)                  4
        ;; - return                        2
        
       	movlw D'199'
	movwf count

d_1000  goto $+1
        decfsz count, 1
        goto d_1000

        return

; --------------------------------------------------------------------------
_delay_ms
        ;; cycle calculation:
        ;; - call:                         2
        ;; - init:                         1
        ;; - loop: (1000+1+2)*(count-1) (w-1)*1003 -> 3*(w-1) overhead
        ;; - last  (1000+2)             1002       -> 2 overhead
        ;; - return                        2
        ;; overhead is 4 + 3w µs, i.e. about 0,7% -> 0,3% overhead
        
        movwf count

d_ms    call _delay_1000
        decfsz count, 1
        goto d_ms

        return

; --------------------------------------------------------------------------
        end
