mov BP, 0xA0  ; CGA base address

; print 'binary: '
mov [0x00], 0x62    ; b
mov [0x01], 0x69    ; i
mov [0x02], 0x6E    ; n
mov [0x03], 0x61    ; a
mov [0x04], 0x72    ; r
mov [0x05], 0x79    ; y
mov [0x06], 0x3A    ; :
mov [0x07], 0x20    ; (space)

int 21h ; print string

mov [0x00], 0x68    ; h
mov [0x01], 0x65    ; e
mov [0x02], 0x6C    ; l
mov [0x03], 0x6C    ; l
mov [0x04], 0x6F    ; o
mov [0x05], 0x20    ; (space)
mov [0x06], 0x77    ; w
mov [0x07], 0x6F    ; o
mov [0x08], 0x72    ; r
mov [0x09], 0x6C    ; l
mov [0x0A], 0x64    ; d

int 21h

;mov AX, 0302h
;not AL
