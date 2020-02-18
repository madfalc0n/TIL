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















