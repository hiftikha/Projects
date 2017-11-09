; CompareVariables.asm - Chapter 5 example.




 include Irvine32.inc
 include Macros.inc

.data
Grade dword 0

.code
main proc

	call ReadInt
	mov Grade,eax

	cmp al,90
	jge L1
	cmp al,80
	jge L2
	cmp al,70
	jge L3
	cmp al,60
	jge L4
	cmp al,60
	jl L5
L1:
	mov al,'A'
	call WriteChar
	call Crlf
	call WaitMsg
L2:
	mov al,'B'
	call WriteChar
	call Crlf
	call WaitMsg
L3 :
	mov al,'C'
	call WriteChar
	call Crlf
	call WaitMsg
L4 :
	mov al,'D'
	call WriteChar
	call Crlf
	call WaitMsg
L5 :
	mov al,'E'
	call WriteChar
	call Crlf
	call WaitMsg


 invoke ExitProcess, 0
		
main endp
end main