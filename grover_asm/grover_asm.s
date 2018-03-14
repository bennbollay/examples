; test program #11
; address: $0b00
; perform Grover's search on $0f00 to $0fff
; store result in $0bff
;
GINIT:	clq
		ldy #$08
 		lda #$00
		adc #$00 	;clear flags
		haa
GITER:	seq
		sez
		clc
		cmp #$64
		haa
		qzz
		clz
		haa
		clq
		dey
		bne GITER
		cmp #$64
		bne GINIT
		sta $0bff
		brk

; < $1f $a0 $0c $a9 $00 $69 $00 $02 $3f $2b $18 $c9 $64 $02 $f7 $47
; > $02 $1f $88 $d0 $f3 $c9 $64 $d0 $e7 $81 $ff $0b $00 
; < $02 $1f $88 $d0 $f3 $c9 $64 $d0 $e7 $8d $ff $0b $00 $00 $00 $00
