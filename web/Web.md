# WEB

> HTTP는 간략하게 말하면 다운로드 서버다. 다운로드 완료 후 끊어버림

- 파이썬은 경량 web server를 위해 3가지의 방법을 제공한다.
  1. bash) python -m http 80
  2. 플라스크?
  3. 장고?



1. http://abc.dfe/[web context]
 - web context 앞 최상위는 root context라고 한다.
 - 웹서버는 요청한 파일을 다운로드 해주는 프로토콜

 

## 동작방식

클라이언트가 컨텐츠를 다운로드 할때..
 1. 파서가 먼저 문제없는지 체크
 2. 렌더러가 태그 추가
 3. 버튼같은거 누를 때 자바스크립트엔진이 처리

 

클라이언트가 데이터 요청시
1. GET 요청 보냄(http 규약 (header + body) )
 - header에는 요청자 정보 등의 메타 데이터 있다.
 - body에는 파라미터 값들이 있다.?
 - url 상에 바디값이 노출 되어 회원가입 또는 로그인으로 이용시 보안 위험잇다.
 - 헤더에 값이 노출?
 - 단순 페이지 요청 등(검색..등)에 사용


2. PUT 요청
 - 바디에 내용이 있다. 
 - 회원가입 , 로그인 등에 사용

 

web 1.0
1. 동기방식(전체페이지 갱신방식)
 - 서버 요청 후 갱신될 떄 까지 아무 동작 못함

2. 비동기 방식 
 - 서버 요청 후 갱신 중에도 기다리지 않고 다른 작업 가능
 - 구글 지도 굴릴때 부분 갱신?





## WEB Language

## HTML
 - Head() + body(클라이언트가 실제 보여지는 부분) 로 구성되어 있다.
 - 문서구조(layout) + 내용

HTML

Document Object Model

Cascading Style Sheet


Xpath

Javascript

HTTP







## 파이썬 소켓 프로그래밍을 통한 실습

> 소켓 프로그래밍을 시작하기 앞서 프로토콜 패밀리에 대해 숙지해야할 필요가 있다.
>
> [https://jjoreg.tistory.com/entry/%EC%97%B4%ED%98%88%EA%B0%95%EC%9D%98-TCPIP](https://jjoreg.tistory.com/entry/열혈강의-TCPIP)

**프로토콜 패밀리는 아래와 같은 종류가 있다.**

| **프로토콜 체계(Protocol Family)** | **정의**                               |
| ---------------------------------- | -------------------------------------- |
| **PF_INET**                        | **IPv4인터넷 프로토콜**                |
| **PF_INET6**                       | **IPv6인터넷 프로토콜**                |
| **PF_LOCAL**                       | **LOCAL 통신을 위한 UNIX 프로토콜**    |
| **PF_PACKET**                      | **Low level socket을 위한 인터페이스** |
| **PF_IPX**                         | **IPX 노벨 프로토콜**                  |

 **AF_INET는 주소 패밀리중 하나입니다. 종류는 아래와 같습니다.**

| **주소체계(Address Family)** | **정의**                                                     |
| ---------------------------- | ------------------------------------------------------------ |
| **AF_INET**                  | **IPv4인터넷 프로토콜**                                      |
| **AF_INET6**                 | **IPv6인터넷 프로토콜**                                      |
| **AF_LOCAL**                 | **LOCAL 통신을 위한 UNIX 프로토콜\**[출처]\** [PF_INET 와 AF_INET 의 차이점](http://blog.naver.com/l18400/60109296392)\|\**작성자\** [l18400](http://blog.naver.com/l18400)** |



**소켓을 만들 때는 소켓이 사용될 환경을 고려해 프로토콜을 설정해 주어야 합니다.**

**다시 말해 프로토콜 패밀리는 소켓을 생성할 때 이 소켓이 어떤 프로토콜을 사용해 통신을 할지 정해줍니다.**

**참고로 소켓은 네트워크 통신을 할때만 사용되는 것은 아닙니다.**

**유닉스 계열의 시스템에서 시스템 내부의 프로세스들끼리 통신을 하기 위해서도 사용됩니다.**

**자주 사용되는 PF_INET는 프로토콜 패밀리중 하나입니다.**





### 서버 코드

```python
import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#AF_INET는 주소 체계(주소 패밀리)중 하나
#AF_INET 은 IPv4 를 사용하겠다는 의미
#socket.SOCK_STREAM 타입 커넥션 기반 TCP protocol
#socket.SOCK_DGRAM 타입 데이터그램 기반 UDP protocol

server_socket.bind(('localhost', 12345)) # localhost : 12345 번 할당 
server_socket.listen(0) # 12345 포트로 listen 하고있겠다 -> 포트를 오픈하겠다.
print("listening")
client_socket, addr = server_socket.accept() #
print("accepting")

data = client_socket.recv(65535) 
print("data 수신: "+data.decode()) # 디코딩 처리, 한글코드같은 unicode를 인식하기 위함

client_socket.send(data) # 받은 데이터를 다시 보냄
print("클라이언트에게 받은 데이터를 다시 send")

client_socket.close()
print("소켓통신 close")
```



### 클라이언트 코드

```python
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect(('localhost', 12345))
print("서버 접속 성공")
sock.send('hello'.encode()) #서버에게 'hello' 보냄
print("send message")

data = sock.recv(65535) #byte 형식으로 데이터를 받으므로 디코딩이 필요하다
print("서버로 부터 데이터 수신: "+data.decode())
print("종료")
```



### 통신 결과

![image-20200211105330101](images/image-20200211105330101.png)







### 실습

- 실습

 

