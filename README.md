# iot-TCP-IP-2025
IoT 개발자 TCP/IP

## 1일차

### 가상환경 설치

1. VMware Download 검색
2. VMware 홈페이지 접속
    - [VMware](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion)
    - 회원가입 및 로그인
3. VMware Workstation Pro for PC - [DOWNLOAD NOW](https://support.broadcom.com/group/ecx/downloads)
    - My Downloads > Free Software Downloads available [HEAR](https://support.broadcom.com/group/ecx/free-downloads)
    - VMware Workstation Pro > VMware Workstation Pro 17.0 for Windows > Release 17.6.3
    - 구름 아이콘 클릭하기 전 약관 동의 후 주소 및 인적사항 입력
    - 이후 구름 아이콘 클릭 후 다운로드
4. VMware-workstation-full-17.6.3-24583834.exe 설치

### Ubuntu

#### Ubuntu 설치
1. [Ubuntu](https://ubuntu.com/) 홈페이지 접속
2. Download Ubuntu 메뉴 > [Download Ubuntu Desktop](https://ubuntu.com/download/desktop)
    - Ubuntu 24.04.2 LTS - Intel or AMD 64-bit architecture 다운로드
3. VMware Workstation Pro 열기
    - Create a New Virtual Machine > New Virtual Machine Wizard
        - Custom > Next > Installer disc image file (다운받은 ubuntu-24.04.2-desktop-amd64.iso 경로지정)
        - Personalize Linux : 모두 `ubuntu` 로 입력
        - Virtual machine name 기본값
        - CPU 4/1, RAM 4 GB, Disk Size 20GB and Single file

#### Ubuntu 공유폴더
1. cp -r /home/ubuntu/Work /mnt/hgfs/Shared_Ubuntu

#### Ubuntu 명령어
1. clear : 터미널 화면 지움
2. uname -a : 정보확인
3. cd(change directory) : 폴더이동
4. cd .. : 전단계로 이동
5. ls(list) : 현재 폴더를 보여줌
6. pwd : 현재위치
7. mkdir : 폴더생성
8. rm -fr (remove) : 파일/폴더 삭제
9. mv(move) : 파일이동
10. cp(copy) : 파일복사
11. touch : 빈파일 생성
12. nano : 파일 수정
13. cat : 화면에 출력
14. gcc *.c : C파일 컴파일 (기본적으로 컴파일 후 a.out 파일생성)
15. gcc *.c -o * : *파일이름으로 컴파일 생성
16. ./* : 컴파일 실행명령
17. sudo nano /etc/nanorc : nano 설정
18. / : 루트폴더
19. ./ : 현재폴더
20. ../ : 상위폴더
21. sudo apt install gcc : gcc컴파일러 설치
22. chmod 774 * : 파일 권한 변경 (change mode)

### PuTTY 설치
1. PuTTY Download 검색 - [홈페이지](https://www.putty.org/)
2. Download PuTTY > 64-bit x86 > [putty-64bit-0.83-installer.msi](https://the.earth.li/~sgtatham/putty/latest/w64/putty-64bit-0.83-installer.msi)
    - putty-64bit-0.83-installer.msi 클릭 후 설치
3. Ubuntu에서 터미널 열기
    - sudo apt install net-tools 설치
    - sudo apt install openssh-server 설치
    - ifconfig > inet 아이피주소 복사
4. PuTTY 열기
    - Host Name (or IP address)에 ubuntu inet 아이피 입력 후 Save > Open
    - Accept > ubuntu 계정 이름 및 비밀번호 입력
    - sudo apt update > sudo apt upgrade
5. PuTTY 설정
    - 상단바 마우스 오른쪽 클릭 > Change Settings...
    - Window > Appearance > Font settings > Change... > 폰트 및 사이즈 설정 후 확인
    - Session > ubuntu 클릭 > Close window on exit: Always 클릭 후 Save > Apply

### TCP/IP 소켓통신

#### 서버의 통신 과정
1. 소켓생성 - socket()
2. 소켓연결 - bind()
    - 소켓 주소 할당
3. 연결요청 대기 - listen()
4. 연결허용 - accept()
5. 데이터 송/수신 - read()/write()
6. 종료 - close()

#### 클라이언트의 통신 과정
1. 소켓 생성 - socket()
2. 연결요청 대기 - connect()
3. 데이터 송/수신 - read()/write()
4. 종료 - close

#### C언어 관련
1. open(const char* name, int flags) : `#include <fcntl.h>`
    - O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_RRUNC, O_APPEND
    - 읽기전용, 쓰기전용, 읽기쓰기, 생성
    - file descript : 파일의 번호 1, 2번은 OS에서 사용(3번부터 시작)
2. write(int fd, const void* buf, size_t nbytes) : `#include <unistd>`
    - 파일번호, 데이터타입(버퍼), 데이터사이즈
3. read(int fd, void* buf, size_t count) : `#include <unistd.h>`
    - 파일번호, 데이터타입(버퍼), 데이터사이즈
4. close() : `#include <unistd.h>`
    - 파일닫기
5. perror(const char*)
    - 오류시 명령어
6. Little Endian - 작은주소에 작은값 저장
7. Big Endian - 작은주소에 큰값 저장

#### 프로토콜 체계
1. PF_INET
    - IPv4 인터넷 프로토콜 체계
2. PF_INET6
    - IPv6 인터넷 프로토콜 체계

#### IPv4 인터넷 주소의 체계
1. 클래스 A
    - 네트워크ID(1) + 호스트ID(3)
    - 0 ~ 127이하 (0)
2. 클래스 B
    - 네트워크ID(2) + 호스트ID(2)
    - 128 ~ 191 (10)
3. 클래스 C
    - 네트워크ID(3) + 호스트ID(1)
    - 192 ~ 223 (110)
4. 클래스 D

#### 소켓의 타입(전송방식)
1. TCP(연결지향형 소켓)
    - SOCK_STREAM
2. UDP(비연결지향형 소켓)
    - SOCK_DGRAM

## 2일차

### TCP/IP 소켓통신

#### C언어 관련함수
1. inet_addr()
    - `아이피 주소`로 된 문자열을 정수형태로 변환시켜줌

#### 소켓
- 소켓은 2개로 이루어짐
- 소켓은 큐 구조

1. 서브 소켓
    - 연결유무 확인 후 끊김

2. 연결 소켓
    - 클라이언트 소켓

## 3일차


## 4일차

