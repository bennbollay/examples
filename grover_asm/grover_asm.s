; test program #11
; address: $0b00
; perform Grover's search on $0f00 to $0fff
; store result in $0bff
;
GINIT:		clq
		ldy #$0c
 		lda #$00
		seq
		cln
		clv
		haa
GITER:		seq
		sez
		cmp #$64
		qzz
		haa
		clz
		haa
 		clq
 		dey
		bne GITER
		cmp #$64
		bne GINIT
		stx $0bff
		brk

; > $1f $a0 $0c $a9 $00 $3f $2f $b8 $02 $3f $2b $c9 $64 $f7 $02 $47
; < $02 $1f $88 $d0 $f4 $c9 $64 $d0 $e7 $8e $ff $0b $00
