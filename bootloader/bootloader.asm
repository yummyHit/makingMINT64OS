;
; BootLoader.asm
;
;  Created on: 2017. 7. 1.
;      Author: Yummy
;

[ORG 0x00]			; 코드의 시작 어드레스를 0x00으로 설정
[BITS 16]			; 이하의 코드는 16비트 코드로 설정

SECTION .text			; text 섹션(세그먼트)을 정의

jmp 0x07C0:START		; CS 세그먼트 레지스터에 0x07C0 복사, START 레이블로 이동

TOTALSECTORCNT:		dw 0x02	; 부트 로더를 제외한 OS 이미지의 크기. 최대 1152 섹터(0x90000byte)까지 가능
KERNEL32SECTORCNT:	dw 0x02	; 보호 모드 커널의 총 섹터 수
BOOTSTRAPPROCESSOR:	db 0x01	; Bootstrap Processor인지 여부
ISGRAPHICMODE:		db 0x01	; 그래픽 모드로 시작하는지 여부

; 코드 영역
START:
	mov ax, 0x07C0		; 부트 로더의 시작 어드레스(0x7C00)를 세그먼트 레지스터 값으로 변환
	mov ds, ax		; DS 세그먼트 레지스터에 설정

	; 스택을 0x0000:0000~0x0000:FFFF 영역에 64KB 크기로 생성
	mov ax, 0x0000		; 스택 세그먼트의 시작 어드레스(0x0000)를 세그먼트 레지스터 값으로 변환
	mov ss, ax		; SS 세그먼트 레지스터에 설정
	; 19.02.28 disk error
;	mov sp, 0xFFFF		; SP 레지스터의 어드레스를 0xFFFF로 설정
;	mov bp, 0xFFFF		; BP 레지스터의 어드레스를 0xFFFF로 설정
	mov sp, 0xFFFE		; SP 레지스터의 어드레스를 0xFFFE로 설정
	mov bp, 0xFFFE		; BP 레지스터의 어드레스를 0xFFFE로 설정

	; 19.02.27 BOOTDRIVE 를 통해 드라이브 번호 읽는 부분 추가
	mov byte [ BOOTDRIVE ], dl		; 부팅한 드라이브 번호를 메모리에 저장
	mov si,	0		; SI 레지스터(문자열 원본 인덱스 레지스터)를 초기화
	call MONITORCLEAR

	push LOADINGMSG
	push 0x1F		; 흰색
	push 1
	push 7
	call PRINTMSG
	add sp, 8

; 디스크를 리셋하는 코드의 시작
RESETDISK:
	; BIOS Reset Function 호출. 서비스 번호 0, 드라이브 번호(0 = Floppy)
	; 19.02.27 BOOTDRIVE 와 함께 주석처리
;	mov ah, 0x00
;	mov dl, 0
	call SKIPWITHHIT		; 19.02.28 disk error
	mov ah, 0
	mov dl, byte [ BOOTDRIVE ]
	int 0x13
	; 에러가 발생하면 에러 처리로 이동
	jc HANDLEDISKERR

	; 19.02.27 디스크 파리미터 읽는 부분 추가
	call SKIPWITHLOAD		; 19.02.28 disk error
	mov ah, 0x08					; BIOS 서비스 번호 8(Read Disk Parameters)
	mov dl, byte [ BOOTDRIVE ]		; 읽을 드라비브 번호(USB Flash Drive) 설정
	int 0x13						; 인터럽트 서비스 수행
	jc HANDLEDISKERR				; 에러가 발생하면 에러 처리로 이동

	mov byte [ LASTHEAD ], dh		; 헤드 정보 메모리에 저장
	mov al, cl						; 섹터와 트랙 정보를 AL 레지스터에 저장
	and al, 0x3F					; 섹터 정보(하위 6비트) 추출해 AL 레지스터에 저장
	mov byte [ LASTSECTOR ], al		; 섹터 정보 메모리에 저장
	mov byte [ LASTTRACK ], ch		; 트랙 정보 중 하위 8비트 메모리에 저장

	; 디스크에서 섹터 읽음. 디스크의 내용을 메모리로 복사할 어드레스(ES:BX)를 0x10000으로 설정
	mov si, 0x1000			; OS 이미지를 복사할 어드레스(0x10000)를 세그먼트 레지스터 값으로 변환
					; SS레지스터에 0x1000을 설정하면 영역은 0x10000 ~ 0x1FFFF 가 된다는 것 기억!
	mov es, si			; ES 세그먼트 레지스터에 값 설정
	mov bx, 0x0000			; BX 레지스터에 0x0000을 설정하여 복사할 어드레스를 0x1000:0000(0x10000)으로 최종 설정

;	19.02.23 package 추가와 함께 주석처리
;	mov di, word [ TOTALSECTORCNT ] ; 복사할 OS 이미지의 섹터 수를 DI 레지스터에 설정
	mov di, 1146		; OS 이미지 뒤에 패키지 파일을 로딩하기 위해 573KB(1146섹터)까지 읽도록 설정

.READDATA:
	; 모든 섹터를 다 읽었는지 확인
	cmp di, 0			; 복사할 OS 이미지 섹터 수를 0과 비교
	je .READEND			; 복사할 섹터 수가 0이라면 다 복사 했으므로 .READEND로 이동
	sub di, 0x1			; 복사할 섹터 수를 1 감소

	; BIOS Read Function 호출
	call SKIPWITHGUI		; 19.02.28 disk error
	mov ah, 0x02			; BIOS 서비스 번호 2(Read Sector)
	mov al, 0x1			; 읽을 섹터 수는 1
	mov ch, byte [ TRACKNUM ]	; 읽을 트랙 번호 설정
	mov cl, byte [ SECTORNUM ]	; 읽을 섹터 번호 설정
	mov dh, byte [ HEADNUM ]	; 읽을 헤드 번호 설정
	; 19.02.27 Only floppy  에서 드라이브 번호 가져와 설정하는 것으로 변경
;	mov dl, 0x00			; 읽을 드라이브 번호(0=Floppy) 설정
	mov dl, byte [ BOOTDRIVE ]	; 읽을 드라이브 번호 설정
	int 0x13			; 인터럽트 서비스 수행
	jc HANDLEDISKERR		; 에러가 발생했다면 HANDLEDISKERR로 이동

	; 복사할 어드레스와 트랙, 헤드, 섹터 어드레스 계산
	add si, 0x0020			; 512(0x200)바이트만큼 읽었으므로, 이를 세그먼트 레지스터 값으로 변환
	mov es, si			; ES세그먼트 레지스터에 더해서 어드레스를 한 섹터만큼 증가

	; 한 섹터를 읽었으므로 섹터 번호를 증가시키고 마지막 섹터(18)까지 읽었는지 판단
	; 마지막 섹터가 아니면 섹터 읽기로 이동해서 다시 섹터 읽기 수행
	mov al, byte [ SECTORNUM ]	; 섹터 번호를 AL 레지스터에 설정
	add al, 0x01			; 섹터 번호를 1 증가
	mov byte [ SECTORNUM ], al	; 증가시킨 섹터 번호를 SECTORNUM에 다시 설정
	; 19.02.27 Only floppy 에서 읽은 섹터에 따라 수행토록 변경
;	cmp al, 19			; 증가시킨 섹터 번호를 19와 비교
;	jl .READDATA			; 섹터 번호가 19 미만이라면 리드로 이동
	cmp al, byte [ LASTSECTOR ]		; 증가시킨 섹터 번호를 마지막 섹터 번호와 비교
	jbe .READDATA					; 섹터 번호가 마지막 섹터 이하면 리드로 이동

	; 마지막 섹터까지 읽었으면(섹터 번호가 19이면) 헤드를 토글(0->1, 1->0) 하고, 섹터 번호 1로 설정
	; 19.02.27 헤드가 2개이던 플로피와 다르게 얼마나 있을지 모르므로 add 형식으로 변경
;	xor byte [ HEADNUM ], 0x01	; 헤드 번호를 0x01과 XOR하여 토글
	add byte [ HEADNUM ], 0x01	; 헤드 번호 1 증가
	mov byte [ SECTORNUM ], 0x01	; 섹터 번호를 다시 1로 설정

	; 만약 헤드가 1->0 으로 바뀌었으면 양쪽 헤드를 모두 읽은 것이므로 아래로 이동하여 트랙 번호 1 증가
	; 19.02.27 섹터->헤드->트랙 증가하는 구문 수정
;	cmp byte [ HEADNUM ], 0x00	; 헤드 번호를 0x00과 비교
;	jne .READDATA			; 헤드 번호가 0이 아니면 리드로 이동
	mov al, byte [ LASTHEAD ]		; 마지막 헤드 번호를 AL 레지스터에 설정
	cmp byte [ HEADNUM ], al		; 헤드 번호를 마지막 헤드 번호와 비교
	jg .ADDTRACK					; 마지막 헤드 번호보다 크면 트랙 번호 1 증가
	jmp .READDATA

.ADDTRACK
	; 트랙을 1 증가시킨 후 다시 섹터 읽기로 이동
	; 19.02.27 섹터->헤드->트랙 증가하는 구문 수정
	mov byte [ HEADNUM ], 0x00	; 헤드 번호 0 으로 설정
	add byte [ TRACKNUM ], 0x01	; 트랙 번호 1 증가
	jmp .READDATA

.READEND:
	; OS 이미지가 완료되었다는 메시지 출력
	push HITMSG			; 출력할 메시지의 어드레스를 스택에 삽입
	push 0x1A			; 초록색
	push 1				; 화면 Y 좌표(1)를 스택에 삽입
	push 57				; 화면 X 좌표(57)를 스택에 삽입
	call PRINTMSG			; PRINTMSG 함수 호출
	add sp, 8			; 삽입한 파라미터 제거

	; VBE 기능 번호 0x4F01을 호출해 그래픽 모드에 대한 모드 정보 블록 구함
	mov ax, 0x4F01		; VBE 기능 번호를 AX 레지스터에 저장
	mov cx, 0x117		; 1024 * 768 해상도에 16비트(R(5):G(6):B(5)) 색 모드 지정
	mov bx, 0x07E0		; BX 레지스터에 0x07E0 저장
	mov es, bx		; ES 세그먼트 레지스터에 BX 값 설정하고
	mov di, 0x00		; DI 레지스터에 0x00을 설정해 0x07E0:0000 어드레스에 모드 정보 블록 저장
	int 0x10		; 인터럽트 서비스 수행
	cmp ax, 0x004F		; 에러가 발생했다면 VBEERR로 이동
	jne .VBEERR

	; VBE 기능 번호 0x4F02를 호출해 그래픽 모드로 전환. 부트 로더의 그래픽 모드 전환 플래그를 확인해 1일 때만 전환
	cmp byte [ ISGRAPHICMODE ], 0x00	; 그래픽 모드 시작하는지 여부를 0x00과 비교
	je .PROTECTMODE		; 0x00과 같다면 바로 보호 모드로 전환

	mov ax, 0x4F02		; VBE 기능 번호를 AX 레지스터에 저장
	mov bx, 0x4117		; 1024 * 768 해상도에 16비트(R(5):G(6):B(5)) 색 사용하는 선형 프레임 버퍼 모드 지정.
				; VBE 모드 번호(비트 0~8) = 0x117, 버퍼 모드(비트 14) = 1(선형 프레임 버퍼 모드)
	int 0x10		; 인터럽트 서비스 수행
	cmp ax, 0x004F		; 에러가 발생했다면 VBEERR로 이동
	jne .VBEERR

	; 그래픽 모드로 전환되었다면 보호 모드 커널로 이동
	jmp .PROTECTMODE

.VBEERR:
	; 예외 처리. 그래픽 모드 전환이 실패했다는 메시지 출력
	push GRAPHICERRMSG
	push 0x1F
	push 1
	push 7
	call PRINTMSG
	add sp, 8
	call HANDLEDISKERR

.PROTECTMODE:
	; 로딩한 가상 OS 이미지 실행
	jmp 0x1000:0x0000

; 디스크 에러를 처리하는 함수
HANDLEDISKERR:			; 에러 처리 코드
	push ERRMSG		; 에러 문자열의 어드레스를 스택에 삽입
	push 0x1C		; 빨간색
;	push 1			; 화면 Y 좌표(1)를 스택에 삽입
;	push 57			; 화면 X 좌표(57)를 스택에 삽입
	push 10			; 화면 Y 좌표(10)를 스택에 삽입
	push 33			; 화면 X 좌표(35)를 스택에 삽입
	call PRINTMSG		; PRINTMSG 함수 호출
	add sp, 8
	jmp $			; 현재 위치에서 무한 루프 수행

; disk error 없애기 위한 3가지 함수.
; 1. MSG 문자가 있으나 없으나 disk error
; 2. 하나의 함수를 3번 call 하면 그 또한 disk error
; 3. 아래와 같이 3개 함수로 나누면 ok
; 4. boot option 에서 usb 인식을 하여 부트로더를 찾으면 ok
SKIPWITHHIT:
	push HITMSG	
	push 0x1F
	push 7			; 화면 Y 좌표(9)를 스택에 삽입
	push 35			; 화면 X 좌표(35)를 스택에 삽입
	call PRINTMSG		; PRINTMSG 함수 호출
	add sp, 8

SKIPWITHLOAD:
	push LOADINGMSG	
	push 0x1F
	push 8			; 화면 Y 좌표(9)를 스택에 삽입
	push 35			; 화면 X 좌표(35)를 스택에 삽입
	call PRINTMSG		; PRINTMSG 함수 호출
	add sp, 8

SKIPWITHGUI:
	push GRAPHICERRMSG
	push 0x1F
	push 9			; 화면 Y 좌표(9)를 스택에 삽입
	push 35			; 화면 X 좌표(35)를 스택에 삽입
	call PRINTMSG		; PRINTMSG 함수 호출
	add sp, 8

; 메시지를 출력하는 함수
; PARAM : x 좌표, y 좌표, 문자열
PRINTMSG:
	push bp				; 베이스 포인터 레지스터(BP)를 스택에 삽입
	mov bp, sp			; 베이스 포인터 레지스터(BP)에 스택 포인터 레지스터(SP)의 값을 설정
					; 베이스 포인터 레지스터(BP)를 이용해서 파라미터에 접근할 목적
	push es				; ES 세그먼트 레지스터부터 DX 레지스터까지 스택에 삽입
	push si				; 함수에서 임시로 사용하는 레지스터로 함수의 마지막 부분에서
	push di				; 스택에 삽입된 값을 꺼내 원래 값으로 복원
	push ax
	push cx
	push dx

	; ES 세그먼트 레지스터에 비디오 모드 어드레스 설정
	mov ax, 0xB800		; 비디오 메모리 시작 어드레스(0x0B8000)를 세그먼트 레지스터 값으로 변환
	mov es, ax		; ES 세그먼트 레지스터에 설정

	; Y 좌표를 이용해서 먼저 라인 어드레스를 구함
	mov ax, word [ bp + 6 ]	; 파라미터 2(화면 좌표 Y)를 AX 레지스터에 설정
	mov si, 160		; 한 라인의 바이트 수(2 * 80 컬럼)를 SI 레지스터에 설정
	mul si			; AX 레지스터와 SI 레지스터를 곱하여 화면 Y 어드레스 계산
	mov di, ax		; 계산된 화면 Y 어드레스를 DI 레지스터에 설정

	; X 좌표를 이용해서 2를 곱한 후 최종 어드레스를 구함
	mov ax, word [ bp + 4 ]	; 파라미터 1(화면 좌표 X) AX 레지스터에 설정
	mov si, 2		; 한 문자를 나타내는 바이트 수(2)를 SI 레지스터에 설정
	mul si			; AX 레지스터와 SI 레지스터를 곱하여 화면 X 어드레스를 계산
	add di, ax		; 화면 Y 어드레스와 계산된 X 어드레스를 더해서 실제 비디오 메모리 어드레스 계산

	; 출력할 문자열의 어드레스
	mov bl, byte [ bp + 8 ]	; 파라미터 3(배경과 글자 색을 지정)을 BL 비트에 설정
	mov si, word [ bp + 10 ]

.MSGLOOP:			; 메시지 출력 루프
	mov cl, byte [ si ]	; SI 레지스터가 가리키는 문자열 위치에서 한 문자를 CL 레지스터에 복사
				; CL 레지스터는 CX 레지스터의 하위 1바이트를 의미
				; 문자열은 1바이트면 충분하므로 CX 레지스터의 하위 1바이트만 사용

	cmp cl, 0		; 복사된 문자와 0을 비교
	je .MSGEND		; 복사한 문자의 값이 0이면 문자열이 종료되었음을 의미하므로 .MSGEND로 이동하여 문자 출력 종료

	mov byte [ es : di ], cl		; 0이 아니라면 비디오 메모리 어드레스 0xB800:di에 문자를 출력
	mov byte [ es : di + 1 ], bl

	add si, 1		; SI 레지스터에 1을 더하여 다음 문자열로 이동
	add di, 2		; DI 레지스터에 2를 더하여 비디오 메모리의 다음 문자 위치로 이동 비디오 메모리는 (문자, 속성)의 쌍으로 구성되므로 문자만 출력하려면 2를 더해야 함

	jmp .MSGLOOP		; 메시지 출력 루프로 이동해 다음 문자 출력

.MSGEND:
	pop dx			; 함수에서 사용이 끝난 DX 레지스터에서 ES 레지스터까지를 스택에
	pop cx			; 삽입된 값을 이용해서 복원
	pop ax			; 스택은 가장 마지막에 들어간 데이터가 가장 먼저 나오는
	pop di			; 자료구조이므로 삽입의 역순으로 제거해야 함
	pop si
	pop es
	pop bp			; 베이스 포인터 레지스터(BP) 복원
	ret			; 함수를 호출한 다음 코드의 위치로 복귀

; 데이터 영역
MONITORCLEAR:
	push bp
	mov bp, sp
	
	push es
	push si
	push di
	push ax
	push cx
	push dx

	mov ax, 0xB800
	mov es, ax

.MONITORCLEARLOOP:	; 화면을 지우는 루프
	mov byte [ es: si ], 0		; 비디오 메모리의 문자가 위치하는 어드레스에 0을 복사하여 문자 삭제
	mov byte [ es: si + 1 ], 0x1F	; 비디오 메모리의 속성이 위치하는 어드레스에 0x1F(검은 바탕에 밝은 녹색)을 복사
	add si, 2			; 문자와 속성을 설정했으니 다음 위치로 이동
	cmp si, 80 * 25 * 2		; 화면의 전체 크기는 80문자 * 25라인
					; 출력한 문자의 수를 의미하는 SI 레지스터와 비교
	jl .MONITORCLEARLOOP		; SI 레지스터가 80*25*2보다 작다면 아직 지우지 못한 영역이 있으니 다시 위로 이동
	pop dx
	pop cx
	pop ax
	pop di
	pop si
	pop es
	pop bp
	ret

; 19.02.27 파티션 테이블 read 를 위해 메세지 부분 최소화
;ERRMSG:	db '[  ERR  ]', 0
;LOADINGMSG:	db 'OS image Loading .................................', 0
;HITMSG:	db '[  Hit  ]', 0
;GRAPHICERRMSG : db 'Change Graphic Mode ..............................', 0
ERRMSG:	db 'Disk Read Error', 0
LOADINGMSG:	db '', 0
HITMSG:	db '', 0
GRAPHICERRMSG : db '', 0

; 디스크 읽기에 관련된 변수들
SECTORNUM:	db 0x02		; OS 이미지가 시작하는 섹터 번호를 저장하는 영역
HEADNUM:	db 0x00		; OS 이미지가 시작하는 헤드 번호를 저장하는 영역
TRACKNUM:	db 0x00		; OS 이미지가 시작하는 트랙 번호를 저장하는 영역

; 디스크 파라미터 관련 변수들
BOOTDRIVE:	db 0x00		; 부팅 드라이브 번호 저장 영역
LASTSECTOR:	db 0x00		; 드라미브 마지막 섹터 번호 -1 저장 영역
LASTHEAD:	db 0x00		; 드라이브 마지막 헤드 번호 저장 영역
LASTTRACK:	db 0x00		; 드라이브 마지막 트랙 번호 저장 영역

times 510 - ( $ - $$ )	db	0x00	; $ : 현재 라인의 어드레스
					; $$ : 현재 섹션의 시작 어드레스
					; $ - $$ : 현재 섹션을 기준으로 하는 오프셋
					; 510 - ( $ - $$ ) : 현재부터 어드레스 510까지
					; db 0x00 : 1바이트를 선언하고 값은 0x00
					; time : 반복 수행
					; 현재 위치에서 어드레스 510까지 0x00으로 채움

dw 0xAA55			; 어드레스 511, 512에 0x55, 0xAA를 써서 부트 섹터로 표기(little endian)

