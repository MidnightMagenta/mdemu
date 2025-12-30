    .org $8000

start:
    lda #$FF

; pad to end of ROM minus vectors
    .res $FFFC - *, $00

; reset vector
    .word start
; IRQ/BRK vector
    .word start
