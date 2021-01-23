# Docker option manual

도커를 사용하기 위해 필요한 옵션을 정리해놓았다. 자세한 내용은 [Docker docs](https://docs.docker.com/)에서 확인 가능하다.



##  User 권한 설정

리눅스에서 docker 명령을 사용시 **root** 권한으로 실행되기 때문에 항상 **sudo**를 붙힌 후 docker 명령을 실행해야 함. 아래 명령어를 통해 **sudo** 없이도 사용가능하도록 설정 가능

 - `sudo usermod -a -G docker [userID]`
   - sudo 없이 docker 명령어 사용 가능하도록 권한 변경, 로그아웃 후 다시 로그인 해야 함



## 1. Image 관련

`Docker image pull/push`

 - sudo docker pull [이미지:버전] 
   - 원격 Repository에서 이미지를 가져옴
   - ex) `sudo docker pull ubuntu:18.04`
 - sudo docker push [이미지:버전]

   - 내가 가지고 있는 docker image를 **원격 repository에 upload 함**

### 1.1 Docker image 조회 및 삭제

 - image 조회 : `docker images`

```bash
madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        2 weeks ago         109MB
	madfalcon/node-web-app    latest              77f343714c04        2 weeks ago         109MB
	node                      alpine3.10          fac3d6a8e034        2 weeks ago         106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB
```

 - image 삭제 : `docker image rm [이미지명:버전]`
   - TIP : image 삭제 전 관련된 컨테이너들을 삭제 해주어야 함

```bash
madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        2 weeks ago         109MB
	madfalcon/node-web-app    latest              77f343714c04        2 weeks ago         109MB
	node                      alpine3.10          fac3d6a8e034        2 weeks ago         106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB

madfalcon@test_madfalcon_server:~$ docker image rm madfalcon/node-web-app:latest 
	Untagged: madfalcon/node-web-app:latest

madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        2 weeks ago         109MB
	node                      alpine3.10          fac3d6a8e034        2 weeks ago         106MB
	myoung_test               1.0                 fac3d6a8e034        2 weeks ago         106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB
```

 - image 태깅(이름지정) : `docker image tag [기존이미지명:버전] [새로지정이미지명:버전]` Image를 개인 private registry에 올릴때 사용

```bash
madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        2 weeks ago         109MB
	madfalcon/node-web-app    latest              77f343714c04        2 weeks ago         109MB
	node                      alpine3.10          fac3d6a8e034        2 weeks ago         106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB

madfalcon@test_madfalcon_server:~$ docker image tag node:alpine3.10 myoung_test:1.0
madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        2 weeks ago         109MB
	madfalcon/node-web-app    latest              77f343714c04        2 weeks ago         109MB
	myoung_test               1.0                 fac3d6a8e034        2 weeks ago         106MB
	node                      alpine3.10          fac3d6a8e034        2 weeks ago         106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB
```

### 1.2 Docker image push 및 pull 명령어를 이용해 Image upload 및 download

 - Image download : `docker push [회원가입ID/생성한이미지파일]`
   - Dockerhub 또는 private registry에 업로드 되어있는 Image 다운가능

```bash
madfalcon@test_madfalcon_server:~$ docker push chadool116/node-web-app
	The push refers to repository [docker.io/chadool116/node-web-app]
	83a088502ffd: Pushed 
	4c66dc201393: Pushed 
	f845fd53498a: Pushed 
	f7eb0a63edef: Pushed 
	20d6ac69de87: Mounted from library/node 
	15b7d94033f5: Mounted from library/node 
	4322be3f308a: Mounted from library/node 
	77cae8ab23bf: Mounted from library/node 
	latest: digest: sha256:c591c96e1864d2685a6690daa8e053012c3958197ac70cc4abdbd1637447aa18 size: 1990
madfalcon@test_madfalcon_server:~$
```

 - Image upload : `docker pull [업로드한 이미지]`
   - Dockerhub 또는 private registry에 Image 업로드 가능

```bash
madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY               TAG                 IMAGE ID            CREATED             SIZE
	madfalcon/node-web-app   latest              77f343714c04        8 days ago          109MB
	node                     alpine3.10          fac3d6a8e034        9 days ago          106MB
	hello-world              latest              fce289e99eb9        11 months ago       1.84kB

madfalcon@test_madfalcon_server:~$ docker pull chadool116/node-web-app
	Using default tag: latest
	latest: Pulling from chadool116/node-web-app
	Digest: sha256:c591c96e1864d2685a6690daa8e053012c3958197ac70cc4abdbd1637447aa18
	Status: Downloaded newer image for chadool116/node-web-app:latest
	docker.io/chadool116/node-web-app:latest

madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        8 days ago          109MB
	madfalcon/node-web-app    latest              77f343714c04        8 days ago          109MB
	node                      alpine3.10          fac3d6a8e034        9 days ago          106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB
```

### 1.3 Docker image 실행

 - Image 실행 : `docker run [이미지명:버전]`

#### Docker run option

- `-name` : 컨테이너에 이름을 지정해줌
- `-v` : 컨테이너와 호스트의 경로를 공유하는 옵션
- `-e` : 컨테이너 내에서 사용할 환경변수
- `-d` : 백그라운드로 동작 하도록 설정
- `-p` : 외부에 포트를 개방
- `-rm` : 해당 프로세스 종료시 자동으로 컨테이너 제거
- `-it` : 프로세스 실행 후 터미널 접속, `/bin/bash` 명령어를 입력하여 쉘모드로 진입할 수 있음  

```bash
madfalcon@test_madfalcon_server:~$ docker run chadool116/node-web-app

> madfalcon_docker_web_app@1.0.0 start /usr/src/my_first_app
> node server.js

Running on http://localhost:8080


'-d'와 '-p' 옵션을 사용할 경우
madfalcon@test_madfalcon_server:~$ docker run -d -p 80:8080 chadool116/node-web-app
15007674f945a68ad93bef4af5abcd6e27eb69790ceea2172a8db6756199cbc7
madfalcon@test_madfalcon_server:~$ docker ps
    CONTAINER ID        IMAGE                     COMMAND                  CREATED             STATUS              PORTS                            NAMES
    15007674f945        chadool116/node-web-app   "docker-entrypoint.s   5 seconds ago       Up 2 seconds        80/tcp, 0.0.0.0:80->8080/tcp   inspiring_chaplygin
외부에서 8080 포트접속시 80 서비스로 포워딩
	
```



## 2 docker container 관련

 - 컨테이너 조회 : `docker container [-a]`
   - TIP : '-a' 옵션은 모든 컨테이너를 조회, 기존은 실행중인 컨테이너만 조회, '-q' 옵션은 IMAGE 또는 container ID만 조회
   - TIP : 실행중인 모든 컨테이너 작동 중지 : "docker container stop $(docker container ls -aq)"

```bash
madfalcon@test_madfalcon_server:~$ docker container ls -a
	CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                   PORTS               NAMES
	8dcfd1f159d2        hello-world         "/hello"            3 weeks ago         Exited (0) 3 weeks ago                       nifty_gates

madfalcon@test_madfalcon_server:~$ docker container ls -a -q
	8dcfd1f159d2
```

 - 컨테이너 실행 :  `docker container run [이미지:버전]`
   - TIP : 실행되었던 컨테이너를 다시 시작할 경우 "docker container start(또는 restart) [컨테이너ID 또는 Name]

```bash
madfalcon@test_madfalcon_server:~$ docker images
	REPOSITORY                TAG                 IMAGE ID            CREATED             SIZE
	chadool116/node-web-app   latest              77f343714c04        2 weeks ago         109MB
	myoung_test               1.0                 fac3d6a8e034        2 weeks ago         106MB
	myoung_test               1.1                 fac3d6a8e034        2 weeks ago         106MB
	myoung_test               1.2                 fac3d6a8e034        2 weeks ago         106MB
	myoung_test               1.3                 fac3d6a8e034        2 weeks ago         106MB
	node                      alpine3.10          fac3d6a8e034        2 weeks ago         106MB
	hello-world               latest              fce289e99eb9        11 months ago       1.84kB
madfalcon@test_madfalcon_server:~$ docker container run hello-world

	Hello from Docker!
	This message shows that your installation appears to be working correctly.

	To generate this message, Docker took the following steps:
	 1. The Docker client contacted the Docker daemon.
	 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
		(amd64)
	 3. The Docker daemon created a new container from that image which runs the
		executable that produces the output you are currently reading.
	 4. The Docker daemon streamed that output to the Docker client, which sent it
		to your terminal.

	To try something more ambitious, you can run an Ubuntu container with:
	 $ docker run -it ubuntu bash

	Share images, automate workflows, and more with a free Docker ID:
	 https://hub.docker.com/

	For more examples and ideas, visit:
	 https://docs.docker.com/get-started/
```



