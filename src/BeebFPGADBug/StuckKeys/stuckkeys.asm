; MIT License
; 
; Copyright (c) 2025 Dossytronics
; https://github.com/dominicbeesley/blitter-65xx-code
; 
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
; 
; The above copyright notice and this permission notice shall be included in all
; copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.



		.include 	"oslib.inc"
		.include	"common.inc"
		.include	"hardware.inc"
		.include	"mosrom.inc"


SCREEN_START	:= $7C00

	.zeropage

zp_ptr:		.res	2
zp_ctr1:	.res	1
zp_ctr2:	.res	1
zp_ctr3:	.res	1

	.code

start:
		lda	#22
		jsr	OSWRCH

		lda	#7
		jsr	OSWRCH


		sei			; disable interrupts

		; disable keyboard scan


mulp:
		ldx	#<SCREEN_START
		stx	zp_ptr+0
		ldx	#>SCREEN_START
		stx	zp_ptr+1

		ldy	#0
		sty	zp_ctr1
sulp:		
		ldx	zp_ctr1
		jsr	_KEYBOARD_SCAN
		txa
		eor	#$80
		rol	A
		; carry contains 1 for key down
		php

		lda	#9		; steady
		sbc	#0
		sta	(zp_ptr),Y
		iny

		plp
		lda	#2		; green
		sbc	#0
		sta	(zp_ptr),Y
		iny
		lda	zp_ctr1
		lsr	A
		lsr	A
		lsr	A
		lsr	A
		jsr	Hex
		sta	(zp_ptr),Y
		iny
		lda	zp_ctr1
		jsr	Hex
		sta	(zp_ptr),Y
		iny

		inc	zp_ctr1		

		cpy	#40
		bne	sulp		

		clc	
		lda	#80
		adc	zp_ptr
		sta	zp_ptr
		lda	#0
		adc	zp_ptr+1
		sta	zp_ptr+1

		ldy 	#0

		lda	#6
		adc	zp_ctr1
		sta	zp_ctr1

		bpl	sulp

		inc	zp_ctr2
		lda	zp_ctr2
		cmp	#25
		bcc	mulp

		lda	#0
		sta	zp_ctr2

		inc	zp_ctr3

		lda	zp_ctr3
		and	#1
		asl	A
		asl	A
		asl	A
		ora	#6
		sta	sheila_SYSVIA_orb

		lda	zp_ctr3
		and	#2
		asl	A
		asl	A
		ora	#7
		sta	sheila_SYSVIA_orb


		jmp	mulp


Hex:		and	#$0F
		cmp	#10
		bcc	@1
		adc	#'A'-'9'-2
@1:		adc	#'0'
		rts



_KEYBOARD_SCAN:	lda	#$03				; stop Auto scan
		sta	sheila_SYSVIA_orb		; by writing to system VIA
		lda	#$7f				; set bits 0 to 6 of port A to input on bit 7
							; output on bits 0 to 6

		sta	sheila_SYSVIA_ddra		; 
		stx	sheila_SYSVIA_ora_nh		; write X to Port A system VIA
		ldx	sheila_SYSVIA_ora_nh		; read back &80 if key pressed (M set)
		rts