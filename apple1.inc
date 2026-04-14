;=============================================================
; apple1.inc — Apple 1 Definitions for ca65
;=============================================================

;-------------------------------------------------------------
; PIA (Motorola 6821) I/O Registers
;-------------------------------------------------------------
KBD         = $D010     ; Keyboard data — bit 7 set when key latched
KBDCR       = $D011     ; Keyboard control — bit 7 = new key ready
DSP         = $D012     ; Display data — write ASCII char here
DSPCR       = $D013     ; Display control

;-------------------------------------------------------------
; Woz Monitor ROM Entry Points  ($FF00–$FFFF)
;-------------------------------------------------------------
MONRST      = $FF00     ; Cold-start / re-enter Woz Monitor
ECHO        = $FFEF     ; Print char in A (7-bit ASCII) to display

;-------------------------------------------------------------
; Woz Monitor Zero Page  ($24–$2B reserved by monitor)
;-------------------------------------------------------------
XAML        = $24       ; "Examine" address, low byte
XAMH        = $25       ; "Examine" address, high byte
STL         = $26       ; Store address, low byte
STH         = $27       ; Store address, high byte
HEXL        = $28       ; Hex value buffer, low byte
HEXH        = $29       ; Hex value buffer, high byte
YSAV        = $2A       ; Y register save (used by monitor)
MODE        = $2B       ; Monitor mode: $00=XAM, $7F=STORE, $AE=BLOCK XAM

;-------------------------------------------------------------
; Memory Map
;-------------------------------------------------------------
ZP          = $0000     ; Zero page start
STACK       = $0100     ; 6502 hardware stack ($0100–$01FF)
MON_IN      = $0200     ; Woz Monitor input buffer ($0200–$027F)
USER_RAM    = $0280     ; First byte available to user programs
IO_BASE     = $D010     ; Start of I/O address space
ROM_BASE    = $FF00     ; Start of Woz Monitor ROM

;-------------------------------------------------------------
; ASCII Control Characters
;-------------------------------------------------------------
BS          = $08       ; Backspace
CR          = $0D       ; Carriage return (newline on Apple 1)
ESC         = $1B       ; Escape

;-------------------------------------------------------------
; Macro: PUTC  — print a literal character
;   PUTC 'A'
;-------------------------------------------------------------
.macro PUTC char
    lda  #char
    jsr  ECHO
.endmacro

;-------------------------------------------------------------
; Macro: NEWLINE  — print a carriage return
;-------------------------------------------------------------
.macro NEWLINE
    lda  #CR
    jsr  ECHO
.endmacro

;-------------------------------------------------------------
; Macro: PUTS  — print a null-terminated string by address
;   PUTS my_string
;   Clobbers: A, Y
;-------------------------------------------------------------
.macro PUTS addr
    .local @loop, @done
    ldy  #$00
@loop:
    lda  addr,y
    beq  @done
    jsr  ECHO
    iny
    bne  @loop
@done:
.endmacro

;-------------------------------------------------------------
; Macro: GETKEY  — wait for a keypress, result in A (7-bit)
;   Clobbers: A
;-------------------------------------------------------------
.macro GETKEY
    .local @wait
@wait:
    lda  KBDCR
    bpl  @wait          ; loop until bit 7 set (key ready)
    lda  KBD            ; read key (bit 7 is set by hardware)
    and  #$7F           ; strip bit 7 → standard 7-bit ASCII
.endmacro
