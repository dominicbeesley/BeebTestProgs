	.IFNDEF __HARDWARE_INC__
__HARDWARE_INC__:


sheila_MEM_CTL			:= $FE31
BITS_MEM_CTL_SWMOS		:= $01
BITS_MEM_CTL_SWMOS_DEBUG	:= $04
BITS_MEM_CTL_SWMOS_DEBUG_EN	:= $08
BITS_MEM_CTL_FLEX		:= $10
BITS_MEM_CTL_SWMOS_DEBUG_5C	:= $40
BITS_MEM_CTL_SWMOS_DEBUG_ACT	:= $80
sheila_MEM_DEBUG_SAVE		:= $FE32

sheila_MEM_TURBO2		:= $FE36
BITS_MEM_TURBO2_THROTTLE	:= $80

sheila_MEM_LOMEMTURBO		:= $FE37
sheila_ROM_THROTTLE_0		:= $FE33
sheila_ROM_THROTTLE_1		:= $FE35
sheila_ROM_AUTOHAZEL_0		:= $FE38
sheila_ROM_AUTOHAZEL_1		:= $FE39


sheila_ACIA_CTL		:=	$FE08
ACIA_RDRF		:=	$01
ACIA_TDRE		:=	$02

sheila_ACIA_DATA	:=	$FE09
sheila_SERIAL_ULA	:=	$FE10


; BLTCON is written in two passes with top bit clear i.e. not BLTCON_ACT_ACT
; the exec flags are first set
; then with top bit set the active flag, bit mode and cell flags are set
; BLTCON/ACT byte flags

BLITCON_ACT_ACT			:=	$80		; always set when setting act constants/execing  
BLITCON_ACT_CELL		:=	$40		; cell addressing used i.e. move one byte left adds 8 to address
							; moving one line down either adds 1 byte or STRIDE depending on whether 
							; line crosses an 8 line boundary
BLITCON_ACT_MODE_1BBP		:=	$00		; 1 bit per pixel mapping 2 colours
BLITCON_ACT_MODE_2BBP		:=	$10		; 2 bit per pixel mapping 4 colours
BLITCON_ACT_MODE_4BBP		:=	$20		; 4 bit per pixel mapping 16 colours
BLITCON_ACT_MODE_8BBP		:=	$30		; 8 bit per pixel mapping 256 colours
BLITCON_ACT_LINE		:=	$08		; draw a line
BLITCON_ACT_COLLISION		:=	$04		; gets reset for any non-zero D data (even in EXEC_D is clear)
BLITCON_ACT_WRAP		:=	$02		; wrap C/D addresses to fit between min/max

BLITCON_LINE_MAJOR_UPnRIGHT	:=	$10		; line draw major axis is up
BLITCON_LINE_MINOR_CCW		:=	$20		; minor axis is CCW to MAJOR i.e.:
							;  - left when maj up, up when maj right
							;  - otherwise, right when maj up, down when maj right

BLITCON_EXEC_A			:=	$01
BLITCON_EXEC_B			:=	$02
BLITCON_EXEC_C			:=	$04
BLITCON_EXEC_D			:=	$08
BLITCON_EXEC_E			:=	$10
BLITCON_CELL_B			:=	$20		; NEW

AERIS_CTL_ACT			:=	$80

; DMA controller control flags
DMACTL_ACT			:=	$80		; always set to initiate a transfer

DMACTL_EXTEND			:=	$20		; use extended functions from control2
DMACTL_HALT			:=	$10		; halt cpu during transfer
DMACTL_STEP_DEST_NONE		:=	$00		; do not step destination address
DMACTL_STEP_DEST_UP		:=	$04		; step destination up after transfer
DMACTL_STEP_DEST_DOWN		:=	$08		; step destination down after transfer
DMACTL_STEP_DEST_NOP		:=	$0C		; skip writes, do not increment address
DMACTL_STEP_SRC_NONE		:=	$00		; do not step destination address
DMACTL_STEP_SRC_UP		:=	$01		; step destination up after transfer
DMACTL_STEP_SRC_DOWN		:=	$02		; step destination down after transfer
DMACTL_STEP_SRC_NOP		:=	$03		; skip reads, do not incrememnt address

DMACTL2_IF			:=	$80		; interrupt occurred
DMACTL2_IE			:=	$02		; interrupt enable, interrupt after transfer
DMACTL2_SZ_BYTE			:=	$00
DMACTL2_SZ_WORD			:=	$04
DMACTL2_SZ_WORDSWAPDEST		:=	$08
DMACTL2_SZ_WORDSWAPSRC		:=	$0C
DMACTL2_PAUSE			:=	$01

; Sound Status / control bits
SND_CTL_ACT			:=	$80
SND_CTL_REPEAT			:=	$01


;;; NEW little-endian Word aligned API

CS_BLIT_base			:=	0	; base JIM offset
CS_BLIT_BLITCON_offs		:=	0
CS_BLIT_FUNCGEN_offs		:=	$1
CS_BLIT_MASK_FIRST_offs		:=	$2	; 
CS_BLIT_MASK_LAST_offs		:=	$3
CS_BLIT_WIDTH_offs		:=	$4	; 8 bit
CS_BLIT_HEIGHT_offs		:=	$5	; 8 bit 
CS_BLIT_SHIFT_A_offs		:=	$6	; shift for A data poking this will poke SHIFT_B
						; spare
CS_BLIT_STRIDE_A_offs		:=	$8	; 16 bit little endian
CS_BLIT_STRIDE_B_offs		:=	$A	; 16 bit little endian
CS_BLIT_STRIDE_C_offs		:=	$C	; 16 bit little endian - writing this also writes STRIDE_D for convenience
						; 16 spare
CS_BLIT_ADDR_A_offs		:=	$10	; 24 bit
CS_BLIT_DATA_A_offs		:=	$13
CS_BLIT_ADDR_B_offs		:=	$14	; 24 bit
CS_BLIT_DATA_B_offs		:=	$17
CS_BLIT_ADDR_C_offs		:=	$18	; 24 bit writing this also writes ADDR_D for convenience
CS_BLIT_DATA_C_offs		:=	$1B
CS_BLIT_ADDR_E_offs		:=	$1C
						; spare
CS_BLIT_ADDR_D_MIN_offs		:=	$20	; 24 bit
						; spare
CS_BLIT_ADDR_D_MAX_offs		:=	$24	; 24 bit
						; spare
CS_BLIT_STRIDE_D_offs		:=	$28	; 16 bit little endian
CS_BLIT_SHIFT_B_offs		:=	$2A	
						; spare
CS_BLIT_ADDR_D_offs		:=	$2C	; 24 bit


;;; NEW little-endian Word aligned API

CS_SND_base			:=      $80
CS_SND_SEL_offs			:=	$80
CS_SND_MA_VOL_offs		:=	$81
CS_SND_DATA_offs		:=	$82
CS_SND_PEAK_offs		:=	$83
CS_SND_REPOFF_offs		:=	$84
CS_SND_VOL_offs			:=	$86
CS_SND_STATUS_offs		:=	$87
CS_SND_LEN_offs			:=	$88
CS_SND_PERIOD_offs		:=	$8A
CS_SND_ADDR_offs		:=	$8C

;;; NEW little-endian Word aligned API

CS_DMA_base			:=      $90
CS_DMA_SRC_ADDR_offs		:=	$90
CS_DMA_DEST_ADDR_offs		:=	$94
CS_DMA_COUNT_offs		:=	$98
CS_DMA_DATA_offs		:=	$9A
CS_DMA_CTL_offs			:=	$9C
CS_DMA_CTL2_offs		:=	$9D
CS_DMA_PAUSE_VAL_offs		:=	$9E
CS_DMA_SEL_offs			:=	$9F



CS_AERIS_base			:=      $B0
CS_AERIS_CTL_offs		:=	$B0
CS_AERIS_PROGBASE_offs		:=	$B4
CS_AERIS_PC_offs		:=	$B8


CS_I2C_offs			:=	$D0

jim_page_CHIPSET		:=	$FEFE

jim_page_VERSION		:=	$FC00

jim_offs_VERSION_API_level	:=	$80
jim_offs_VERSION_Board_level	:=	$81
jim_offs_VERSION_API_sublevel	:=	$82
jim_offs_VERSION_cfg_bits	:=	$84
jim_offs_VERSION_cap_bits	:=	$88

;; FC 0088	
BLCAPS_0_CHIPSET		:= $01
BLCAPS_0_DMA			:= $02
BLCAPS_0_BLITTER		:= $04
BLCAPS_0_AERIS			:= $08
BLCAPS_0_I2C			:= $10
BLCAPS_0_PAULA_SOUND		:= $20
BLCAPS_0_HDMI_FRAMEBUFFER	:= $40
BLCAPS_0_T65			:= $80
;;FC 0089	
BLCAPS_1_CPU_65C02		:= $01
BLCAPS_1_CPU_6800		:= $02
BLCAPS_1_CPU_80188		:= $04
BLCAPS_1_CPU_65816		:= $08
BLCAPS_1_CPU_6x09		:= $10
BLCAPS_1_CPU_Z80		:= $20
BLCAPS_1_CPU_68008		:= $40
BLCAPS_1_CPU_680x0		:= $80
;;FC 008A	
BLCAPS_2_CPU_ARM2		:= $01
BLCAPS_2_CPU_Z180		:= $02
BLCAPS_2_GFOOT_SS		:= $04

; Mk.2/1 option switches - note in API level >1 the sense of these is reversed!
BLT_MK2_CFG0_T65		:=	$01
BLT_MK2_CFG0_CPU_6502A_2M	:=	$00
BLT_MK2_CFG0_CPU_65C02_4M	:=	$02
BLT_MK2_CFG0_CPU_65C02_8M	:=	$04
BLT_MK2_CFG0_CPU_6x09_2M	:=	$08
BLT_MK2_CFG0_CPU_6309_4M	:=	$0A
BLT_MK2_CFG0_CPU_Z80_8M		:=	$0C
BLT_MK2_CFG0_CPU_68008		:=	$0E
BLT_MK2_CFG0_SWROMX		:=	$10
BLT_MK2_CFG0_BUGBTN		:=	$80

BLT_MK2_CFG1_MEMI		:=	$01
BLT_MK2_CFG1_BUGOUT		:=	$02

; Mk.3 switches from PORTF/G
BLT_MK3_CFG0_T65		:=	$08
BLT_MK3_CFG0_SWROMX		:=	$10
BLT_MK3_CFG0_MEMI		:=	$40


jim_CS_BLIT_BLITCON		:= 	$FD00 + CS_BLIT_BLITCON_offs
jim_CS_BLIT_FUNCGEN		:= 	$FD00 + CS_BLIT_FUNCGEN_offs
jim_CS_BLIT_MASK_FIRST		:= 	$FD00 + CS_BLIT_MASK_FIRST_offs
jim_CS_BLIT_MASK_LAST		:= 	$FD00 + CS_BLIT_MASK_LAST_offs
jim_CS_BLIT_WIDTH		:= 	$FD00 + CS_BLIT_WIDTH_offs
jim_CS_BLIT_HEIGHT		:= 	$FD00 + CS_BLIT_HEIGHT_offs
jim_CS_BLIT_SHIFT_A		:= 	$FD00 + CS_BLIT_SHIFT_A_offs
jim_CS_BLIT_STRIDE_A		:= 	$FD00 + CS_BLIT_STRIDE_A_offs
jim_CS_BLIT_STRIDE_B		:= 	$FD00 + CS_BLIT_STRIDE_B_offs
jim_CS_BLIT_STRIDE_C		:= 	$FD00 + CS_BLIT_STRIDE_C_offs
jim_CS_BLIT_ADDR_A		:= 	$FD00 + CS_BLIT_ADDR_A_offs
jim_CS_BLIT_DATA_A		:= 	$FD00 + CS_BLIT_DATA_A_offs
jim_CS_BLIT_ADDR_B		:= 	$FD00 + CS_BLIT_ADDR_B_offs
jim_CS_BLIT_DATA_B		:= 	$FD00 + CS_BLIT_DATA_B_offs
jim_CS_BLIT_ADDR_C		:= 	$FD00 + CS_BLIT_ADDR_C_offs
jim_CS_BLIT_DATA_C		:= 	$FD00 + CS_BLIT_DATA_C_offs
jim_CS_BLIT_ADDR_E		:= 	$FD00 + CS_BLIT_ADDR_E_offs
jim_CS_BLIT_ADDR_D_MIN		:= 	$FD00 + CS_BLIT_ADDR_D_MIN_offs
jim_CS_BLIT_ADDR_D_MAX		:= 	$FD00 + CS_BLIT_ADDR_D_MAX_offs
jim_CS_BLIT_STRIDE_D		:= 	$FD00 + CS_BLIT_STRIDE_D_offs
jim_CS_BLIT_SHIFT_B		:= 	$FD00 + CS_BLIT_SHIFT_B_offs
jim_CS_BLIT_ADDR_D		:= 	$FD00 + CS_BLIT_ADDR_D_offs


jim_CS_SND_SEL			:= 	$FD00 + CS_SND_SEL_offs
jim_CS_SND_MA_VOL		:= 	$FD00 + CS_SND_MA_VOL_offs
jim_CS_SND_DATA			:= 	$FD00 + CS_SND_DATA_offs
jim_CS_SND_PEAK			:= 	$FD00 + CS_SND_PEAK_offs
jim_CS_SND_REPOFF		:= 	$FD00 + CS_SND_REPOFF_offs
jim_CS_SND_VOL			:= 	$FD00 + CS_SND_VOL_offs
jim_CS_SND_STATUS		:= 	$FD00 + CS_SND_STATUS_offs
jim_CS_SND_LEN			:= 	$FD00 + CS_SND_LEN_offs
jim_CS_SND_PERIOD		:= 	$FD00 + CS_SND_PERIOD_offs
jim_CS_SND_ADDR			:= 	$FD00 + CS_SND_ADDR_offs

jim_CS_DMA_SRC_ADDR		:=	$FD00 + CS_DMA_SRC_ADDR_offs
jim_CS_DMA_DEST_ADDR		:=	$FD00 + CS_DMA_DEST_ADDR_offs
jim_CS_DMA_COUNT		:=	$FD00 + CS_DMA_COUNT_offs
jim_CS_DMA_DATA			:=	$FD00 + CS_DMA_DATA_offs
jim_CS_DMA_CTL			:=	$FD00 + CS_DMA_CTL_offs
jim_CS_DMA_CTL2			:=	$FD00 + CS_DMA_CTL2_offs
jim_CS_DMA_PAUSE_VAL		:=	$FD00 + CS_DMA_PAUSE_VAL_offs
jim_CS_DMA_SEL			:=	$FD00 + CS_DMA_SEL_offs

jim_CS_AERIS_CTL		:=	$FD00 + CS_AERIS_CTL_offs
jim_CS_AERIS_PROGBASE		:=	$FD00 + CS_AERIS_PROGBASE_offs
jim_CS_AERIS_PPC		:=	$FD00 + CS_AERIS_PC_offs


jim_I2C_BASE			:= 	$FD00 + CS_I2C_offs
jim_I2C_STAT			:= 	jim_I2C_BASE
jim_I2C_DATA			:= 	jim_I2C_BASE + 1

I2C_BUSY	:= $80
I2C_NACK	:= $40
I2C_STOP	:= $04
I2C_START	:= $02
I2C_RNW		:= $01

sheila_sim_control		:=	$FEFF
sheila_reg_debug		:=	$FEFF

fred_JIM_PAGE_HI2		:=	$FCFC		; note ignored Blitter/Paula
fred_JIM_PAGE_HI		:=	$FCFD
fred_JIM_PAGE_LO		:=	$FCFE
fred_JIM_DEVNO			:=	$FCFF

jim_base			:=	$FD00
JIM				:=	jim_base

SHEILA_ROMCTL_SWR	:=	$FE30
SHEILA_ROMCTL_MOS	:=	$FE31

SHEILA_ROMCTL_SWR_ELK	:=	$FE05


ROMCTL_BITS_FLEX	:=	$10

ROMCTL_MOS_JIMEN	:=	$02
ROMCTL_MOS_SWMOS	:=	$01

	
SHEILA_NULA_CTLAUX	:=	$FE22
SHEILA_NULA_PALAUX	:=	$FE23

SHEILA_DEBUG		:=	$FEFF


;***********************************************************************
;* System VIA                                                          *
;***********************************************************************
sheila_SYSVIA_orb			:= $FE40
sheila_SYSVIA_ora			:= $FE41
sheila_SYSVIA_ddrb			:= $FE42
sheila_SYSVIA_ddra			:= $FE43
sheila_SYSVIA_t1cl			:= $FE44
sheila_SYSVIA_t1ch			:= $FE45
sheila_SYSVIA_t1ll			:= $FE46
sheila_SYSVIA_t1lh			:= $FE47
sheila_SYSVIA_t2cl			:= $FE48
sheila_SYSVIA_t2ch			:= $FE49
sheila_SYSVIA_sr			:= $FE4A
sheila_SYSVIA_acr			:= $FE4B
sheila_SYSVIA_pcr			:= $FE4C
sheila_SYSVIA_ifr			:= $FE4D
sheila_SYSVIA_ier			:= $FE4E
sheila_SYSVIA_ora_nh			:= $FE4F

;***********************************************************************
;* SYS VIA - slow data bus RTC                                         *
;***********************************************************************

	.IFDEF MACH_CHIPKIT
BITS_RTC_AS_ON	:=		$88			; PB7
BITS_RTC_AS_OFF :=		$08			;
BITS_RTC_CS	:=		$04			; latch
BITS_RTC_DS	:=		$02			; latch
BITS_RTC_RnW	:=		$01			; latch
BITS_LAT_ON	:=		$08			; latch

RTC_REG_SECONDS	:=		$0
RTC_REG_MINUTES	:=		$2
RTC_REG_HOURS	:=		$4
RTC_REG_DOW	:=		$6
RTC_REG_DAY	:=		$7
RTC_REG_MONTH	:=		$8
RTC_REG_YEAR	:=		$9
	.ENDIF


;***********************************************************************
;* User VIA                                                            *
;***********************************************************************
sheila_USRVIA_orb			:= $FE60
sheila_USRVIA_ora			:= $FE61
sheila_USRVIA_ddrb			:= $FE62
sheila_USRVIA_ddra			:= $FE63
sheila_USRVIA_t1cl			:= $FE64
sheila_USRVIA_t1ch			:= $FE65
sheila_USRVIA_t1ll			:= $FE66
sheila_USRVIA_t1lh			:= $FE67
sheila_USRVIA_t2cl			:= $FE68
sheila_USRVIA_t2ch			:= $FE69
sheila_USRVIA_sr			:= $FE6A
sheila_USRVIA_acr			:= $FE6B
sheila_USRVIA_pcr			:= $FE6C
sheila_USRVIA_ifr			:= $FE6D
sheila_USRVIA_ier			:= $FE6E
sheila_USRVIA_ora_nh			:= $FE6F

;***********************************************************************
;*  VIA constants                                                      *
;***********************************************************************

VIA_IFR_BIT_ANY				:= $80
VIA_IFR_BIT_T1				:= $40
VIA_IFR_BIT_T2				:= $20
VIA_IFR_BIT_CB1				:= $10
VIA_IFR_BIT_CB2				:= $08
VIA_IFR_BIT_SR				:= $04
VIA_IFR_BIT_CA1				:= $02
VIA_IFR_BIT_CA2				:= $01

VIA_ACR_SHIFTMODE_0			:= $00
VIA_ACR_SHIFTMODE_1			:= $04
VIA_ACR_SHIFTMODE_2			:= $08
VIA_ACR_SHIFTMODE_3			:= $0C
VIA_ACR_SHIFTMODE_4			:= $10
VIA_ACR_SHIFTMODE_5			:= $14
VIA_ACR_SHIFTMODE_6			:= $18
VIA_ACR_SHIFTMODE_7			:= $1C

VIA_ACR_T1_MASK				:= $C0
VIA_ACR_T1_CONT				:= $40


;***********************************************************************
;* BBC B/B+ WD177x                                                     *
;***********************************************************************

sheila_1770_dcontrol			:=	$FE80
sheila_1770_wdc_cmd			:=	$FE84
sheila_1770_wdc_trk			:=	$FE85
sheila_1770_wdc_sec			:=	$FE86
sheila_1770_wdc_dat			:=	$FE87

W1770_DRVSEL_BIT_SEL0			:= $01
W1770_DRVSEL_BIT_SEL1			:= $02
W1770_DRVSEL_BIT_SIDE1			:= $04
W1770_DRVSEL_BIT_nDDEN			:= $08
W1770_DRVSEL_BIT_nMR			:= $20


;***********************************************************************
;* NEW API JIM DEVICE NOs                                              *
;***********************************************************************


JIM_DEVNO_HOG1MPAULA			:= $D0
JIM_DEVNO_BLITTER			:= $D1

	.ENDIF