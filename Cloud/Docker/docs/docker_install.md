# Docker install manual

따라만 한다면 쉬운 Docker install manual 이다.



## 0.Docker 설치 전 구성환경

나는 VMware를 이용하여 Ubuntu를 먼저 셋팅하였고 환경은 다음과 같다.

- OS: Ubuntu 18.04 LTS
- CPU : 2 Core 이상(1 GB여도 상관없으나 추후 K8s 구성을 위함)
- RAM : 2 GB 이상(1 GB여도 상관없으나 추후 K8s 구성을 위함)



## 1.Docker 설치

- docker 에는 enterprise(기업용) 버전과 community(일반용) 버전이 있다. 우리는 community 용을 사용한다.

### Repository를 이용한 설치

Ubuntu bash 쉘에서 아래의 절차대로 진행하자

1. apt 패키지 업데이트

   ```bash
   $ sudo apt-get update
   ```

2. HTTPS 를 통해 repository를 이용할 수 있도록 설치
   	

   ```bash
   $ sudo apt-get install \
   	apt-transport-https \
   	ca-certificates \
   	curl \
   	gnupg-agent \
   	software-properties-common
   ```


3. Docker의 official GPG key 추가 및 fingerprint 학인:

   ```bash
    $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
    $ sudo apt-key fingerprint 0EBFCD88
   ```

4. stable repository 설정

   ```bash
    $ sudo add-apt-repository \
      "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
      $(lsb_release -cs) \
      stable"
   ```

5. apt 패키지 업데이트 후 Docker 설치:

   ```bash
    $ sudo apt-get update
    $ sudo apt-get install docker-ce docker-ce-cli containerd.io
   ```

6. Docker 버전 확인 및 `hello-world` image 실행:

   ```bash
    $ sudo docker --version
    $ sudo docker run hello-world
   ```



## 참고

- [Docker 공식문서](https://docs.docker.com/install/linux/docker-ce/ubuntu/)
- [참고자료(동영상)](https://www.youtube.com/watch?v=W7BvS942UZA)

