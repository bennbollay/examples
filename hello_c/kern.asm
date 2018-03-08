.export     _putstr
.autoimport on

; M.O.S. API defines (kernal) - OK for emulator, no changes

.define 	mos_StrPtr	$E0
.define		mos_CallPuts	$FFF3

.segment "KERN"

        .ORG $FE00

banner2:      .byte    "Hello World"
              .byte    $0d, $0a, $00

CHRIN:  lda $E000
        rts

CHROUT: sta $E000
        rts          

; this function was shamelessly ripped :-) from M.O.S. code (c) by Scott Chidester

.segment "KERN"

.proc _putstr: near

.segment "KERN"
        jsr     pushax
        sta    mos_StrPtr
        txa
        sta    mos_StrPtr+1
        jsr    mos_CallPuts
        ;jsr     incsp2
        rts

.endproc

STROUT:
        ldy #0                  ; Non-indexed variant starts at zero, of course
        lda mos_StrPtr+1        ; Save StrPtr so it isn't modified
        pha
PutsLoop:
        lda (mos_StrPtr),y      ; Get the next char in the string
        beq PutsDone            ; Zero means end of string
        jsr CHROUT              ; Otherwise put the char

    ; Update string pointer
        iny                     ; increment StrPtr-lo
        bne PutsLoop            ; No rollover? Loop back for next character
        inc mos_StrPtr+1        ; StrPtr-lo rolled over--carry hi byte
        jmp PutsLoop            ; Now loop back

PutsDone:
        pla
        sta mos_StrPtr+1            ; Restore StrPtr
        rts

.segment "VECT"

        .ORG $FFED

        jmp CHRIN
        jmp CHROUT
        jmp STROUT

;
;
; end of file
;
