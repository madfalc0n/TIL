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

### 2. add

`working directory` , 즉 작업공간에서 변경된 사항을 이력으로 저장하기 위해서는 반드시 `staging area`를 거쳐야 한다.

```bash
$ git add markdown.md # 특정 파일
$ git add images/ #특정 폴더
$ git add . # 현재 디렉토리
```

* `add` 전 상태

  ```bash
  $ git status
  On branch master
  
  No commits yet
  
  #track되고 있지 않는 파일들
  # => commit 이력에 한번도 담기지 않은 파일들
  Untracked files: 
  # commit 될 것(staging area)들에 포함시키려면 add 명령어를 사용하라
    (use "git add <file>..." to include in what will be committed)
          READMD.md
          git.md
          images/
  # 아직 commit 될 것들은 없으나
  # untracked files는 존재한다.
  nothing added to commit but untracked files present (use "git add" to track)
  ```

* `add` 후 상태

  ```bash
  $ git add images/
  
  student@M50417 MINGW64 ~/KMH/TIL (master)
  $ git status
  On branch master
  
  No commits yet
  #commit 될 변화들
  # staging area에 있는 파일들
  Changes to be committed:
    (use "git rm --cached <file>..." to unstage)
          new file:   "images/\354\235\264\353\257\270\354\247\2001.PNG"
  
  Untracked files:
    (use "git add <file>..." to include in what will be committed)
          READMD.md
          git.md
  
  
  ```

### 3. commit

commit은 이력을 확정짓는 명령어로, 해당 시점의 스냅샷을 기록한다.

커밋시에는 반드시 메시지를 작성 해야하며, 메시지는 변경사항을 알 수 있도록 명확하게 작성한다.

```bash
$ git commit -m "마크다운 및 git 정리"
[master (root-commit) 7d1d771] 마크다운 및 git 정리
 3 files changed, 141 insertions(+)
 create mode 100644 READMD.md
 create mode 100644 git.md
 create mode 100644 "images/\354\235\264\353\257\270\354\247\2001.PNG"

student@M50417 MINGW64 ~/KMH/TIL (master)
$ git log # 모든 git 로그 표시
commit 7d1d771a3bbe0f522ef1687e803a7de44498d359 (HEAD -> master) #각 commit 시 고유한 해쉬값을 가지고 있다. 
Author: madfalc0n <chadool116@naver.com>
Date:   Thu Dec 26 14:39:20 2019 +0900

    마크다운 및 git 정리

student@M50417 MINGW64 ~/KMH/TIL (master)
$ git log --oneline #로그들을 하나의 줄로 표시
7d1d771 (HEAD -> master) 마크다운 및 git 정리

student@M50417 MINGW64 ~/KMH/TIL (master)
$ git log -1 #로그들 중 최근 1개
commit 7d1d771a3bbe0f522ef1687e803a7de44498d359 (HEAD -> master)
Author: madfalc0n <chadool116@naver.com>
Date:   Thu Dec 26 14:39:20 2019 +0900

    마크다운 및 git 정리
```

커밋은 각각의 고유한 해시코드를 바탕으로 구분된다.



## 원격 저장소(remote repository) 활용하기

원격 저장소 기능을 제공하는 다양한 서비스 중에 github를 기준으로 설명한다.

### 0. 준비사항

* github에 repository 생성

### 1. 원격 저장소 등록

```bash
$ git add remote add origin [깃허브URL]
```

* 원격저장소(remote)로 `origin` 이라는 이름으로 `[깃허브URL]` 을 등록(`add`) 한다.
* 등록된 원격 저장소 목록을 보기 위해서는 아래의 명령어를 활용한다.

    ```bash
    $ git remote -v
    origin  https://github.com/madfalc0n/TIL.git (fetch)
    origin  https://github.com/madfalc0n/TIL.git (push)
    ```

### 2. `push` - 원격저장소 업로드

```bash
$ git push origin master
```

`origin` 으로 설정된 원격저장소에 `master` branch로 업로드(`push`)

이후 변경사항이 생길 때마다, `add` - `commit` , `push` 를 반복하면 된다.

그리고, 항상 모든 명령어 이후에 연관된 상태를 확인하자.

`status` , `log` , `remote -v` 

