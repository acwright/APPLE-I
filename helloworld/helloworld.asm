;-----------------------;
; Apple I Hello, World! ;
;-----------------------;

.include "../apple1.inc"
.segment "CODE"
 
; Start
Start:
  lda #$0D            ; CR
  jsr ECHO            ; Write char to output device

  ldx #0
Print:
  lda Message,x
  beq @PrintEnd
  jsr ECHO            ; Write char to output device
  inx
  jmp Print
@PrintEnd:
  lda #$0D            ; CR
  jsr ECHO            ; Write char to output device

Done:
  jmp MONRST          ; Jump back to Wozmon

; Message
Message:
  .asciiz "HELLO, APPLE I!"