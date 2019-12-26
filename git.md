# Git

> Git은 분산형 버전 관리 시스템(DVCS)이다.
>
> 소스코드의 버전 및 이력을 관리할 수 있다. 

## 준비하기

윈도우에서 git을 활용하기 위해서 [gitforwindows](https://gitforwindows.org/) 를 설치한다.

git을 활용하기 위해서 GUI 툴인 `source tree`, `github desktop` 등을 활용할 수도 있다.

초기 설치를 완료한 이후에 컴퓨터에 `author` 정보를 입력한다. 이메일 정보를 github에 가입된 이메일로 일치시켜야 커밋 이력들이 관리된다.

```bash
git config --global user.name madfalc0n
git config --global user.email chadool116@naver.com
```

## 로컬 저장소(repository) 활용하기

### 1. 저장소 초기화 

```bash
$ git init
Initialized empty Git repository in C:/Users/student/KMH/TIL/.git/
```

* `.git` 폴더가 생성되며, 여기에 git과 관련된 모든 정보(파일들에 대한 수정 이력)가 저장된다.
* git bash에 `(master)` 라고 표현되는데, 이는 `master`  branch에 있다는 뜻이다.