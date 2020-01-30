# Linux command

## 프로세스 관련

- **`ps` **

  - `-e`: 모든 프로세스 리스트 조회
  - `-f`: 프로세스 시작시간, PID, 등등 다양한 정보 출력
    - 사용예시
  
```bash
  lab03@ip-172-31-40-104:~$ ps -ef
  UID        PID  PPID  C STIME TTY          TIME CMD
  root         1     0  0 14:45 ?        00:00:02 /sbin/init
  .
  .
  lab05     3232  3210  4 14:59 pts/10   00:00:00 /home/ubuntu/anaconda3/bin/python /home/ubuntu/anaconda3/bin/jupyter-notebook --ip 0.0.0.0 --port 8894
  lab04     3258  2320 30 15:00 pts/0    00:00:00 /home/ubuntu/anaconda3/bin/python /home/ubuntu/anaconda3/bin/jupyter-notebook --ip 0.0.0.0 --port 8893
  lab04     3260  3258  0 15:00 pts/0    00:00:00 /home/ubuntu/anaconda3/bin/python /home/ubuntu/anaconda3/bin/conda info --json
  lab03     3264  3100  0 15:00 pts/9    00:00:00 ps -ef
  lab03@ip-172-31-40-104:~$
  
  ```
  
- 프로세스 죽이는 명령어

  - **`kill [번호] [PID값]`** 을 이용해 강제로 프로세스를 죽일수 있다. 좀비 프로세스를 죽일 때 유용하다.
    - kill -9 1911
      - 프로세스 ID가 `1911`인 놈에 대해서 강제종료(-9) 



  ## 사용포트 확인

- **`fuser [옵션] [포트번호/프로토콜(TCP또는UDP)]`**

  - `-u` 옵션 사용시 접속중인 유저정보를 포함해 반환

    - 예시
    ```bash
    lab03@ip-172-31-40-104:~$ fuser -u 8892/tcp
    8892/tcp:             2720(lab03)
    ```



## 압축해제

- **`unzip [압축파일]`**

  - `-d` 옵션 추가시 압축파일 명 디렉토리에 압축해제가 된다.

    - 예시

      ```bash
      
      lab03@ip-172-31-40-104:~/myoung_snow_unzip$ unzip -d myoung_snow_unzip myoung_snowman.zip
      ```

      

## 조건식 출력

- **`grep`**을 통해 특정 문자 포함된 것만 출력
  - 응용으로 **`egrep`** 과 `-v` 옵션을 통해 특정 문자가 제외된 문자만 출력 할 수 있다. 

```bash
#grep 을 통해 'lab03' 문자가 포함된 행 출력
lab03@ip-172-31-40-104:~$ ps -ef | grep 'lab03'
root      2426  1772  0 14:47 ?        00:00:00 sshd: lab03 [priv]
lab03     2429     1  0 14:47 ?        00:00:00 /lib/systemd/systemd --user
lab03     2430  2429  0 14:47 ?        00:00:00 (sd-pam)

#egrep 을 통해 'lab03' 과 'lab04' 문자가 포함된 행 출력
lab03@ip-172-31-40-104:~$ ps -ef | egrep 'lab03|lab04'
root      2426  1772  0 14:47 ?        00:00:00 sshd: lab03 [priv]
lab03     2429     1  0 14:47 ?        00:00:00 /lib/systemd/systemd --user
lab03     2430  2429  0 14:47 ?        00:00:00 (sd-pam)
lab04    32213 32170  0 16:07 ?        00:00:00 sshd: lab04@pts/1
lab04    32214 32213  0 16:07 pts/1    00:00:00 -bash
lab04    33715 32214 75 16:08 pts/1    00:05:04 ./darknet detector train /home/lab04/dog/darknet.data /home/lab04/dog/darknet-yolov3.cfg /home/lab04/dog/darknet53.conv.74
lab03    37205 26154  0 16:15 pts/22   00:00:00 ps -ef
lab03    37206 26154  0 16:15 pts/22   00:00:00 grep -E --color=auto lab03|lab04

#-v 를 통해 'lab03' 이 포함된 행은 제외하고 나머지 출력
lab03@ip-172-31-40-104:~$ ps -ef | grep -v 'lab03'
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0 14:45 ?        00:00:02 /sbin/init
root         2     0  0 14:45 ?        00:00:00 [kthreadd]
.
.
.
```



- **`awk`**을 통해 검색된 프로세스의 두번째 필드를 출력한다.(ps -ef, ps aux 둘 다 두번째 필드는 PID)

```
lab03@ip-172-31-40-104:~$ ps -ef | awk '{print $2}'
PID
1
2
.
.
.
```



## 실시간 상태 출력

- **`watch -n [숫자] [상태확인명령어]`** 를 통해 실시간으로 상태가 업데이트 되는 것을 확인 할 수 있다.

```bash
#nvidia-smi 명령어를 통해 2초 주기로 GPU 사용량 상태 확인
lab03@ip-172-31-40-104:~$ watch -n 2 nvidia-smi
```

<img src="images/image-20200130162806719.png" alt="image-20200130162806719" style="zoom:50%;" />



## 실시간 로그 출력

- **`tail -f [실시간으로업로드되는로그파일]`** 을 이용하여 실시간으로 로그 출력을 할 수 있음

```bash
lab03@ip-172-31-40-104:~/myoung_snow_unzip$ tail -f snowman.log
darknet-yolov3
```

