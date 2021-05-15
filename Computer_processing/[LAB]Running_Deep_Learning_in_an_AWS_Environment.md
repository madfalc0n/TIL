# AWS 이용방법

## Jupyter Notebook 이용하기

### 0. ssh 를 통해 쉘 접속

- AWS 할당받은 IP와 ppk 파일을 통해 쉘 접속

### 1. conda activate 활성

```bash
#쉘 접속 후 activate
lab03@ip-172-31-40-104:~$ conda activate tensorflow_p36
```

### 2. jupyter notebook install and config

```bash
#프로젝트 폴더 생성
(tensorflow_p36) lab03@ip-172-31-40-104:~$ mkdir detection
(tensorflow_p36) lab03@ip-172-31-40-104:~$ cd detection/

#jupyter notebook 생성
(tensorflow_p36) lab03@ip-172-31-40-104:~/detection$ jupyter notebook --generate-config
Writing default config to: /home/lab03/.jupyter/jupyter_notebook_config.py

#파이선 접속
(tensorflow_p36) lab03@ip-172-31-40-104:~/detection$ python
Python 3.6.5 |Anaconda, Inc.| (default, Apr 29 2018, 16:14:56)
[GCC 7.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.

#접속용 암호 생성
>>> from notebook.auth import passwd # 암호를 통해 접속 허용 설정
>>> passwd()
Enter password: 비밀번호 입력
Verify password: 비밀번호 재입력
'sha1:51d2ebfdf7b8:efb8df2872e01648fbe56dbbdd1571546084c18c' # 주피터 노트북 접속용 토큰 값
>>>

(tensorflow_p36) lab03@ip-172-31-40-104:~/.jupyter$ vi jupyter_notebook_config.py
# 아래의 명령어를 복사 및 붙여넣기
c.NotebookApp.password = u'sha1:51d2ebfdf7b8:efb8df2872e01648fbe56dbbdd1571546084c18c'
```

### 3. jupyter notebook start

```bash
#jupyter-notebook --ip [들여보낼ip] --port [포트번호] 입력
(tensorflow_p36) lab03@ip-172-31-40-104:~/detection$ jupyter-notebook --ip 0.0.0.0 --port 8892
[I 09:39:31.970 NotebookApp] [nb_conda_kernels] enabled, 26 kernels found
[I 09:39:31.978 NotebookApp] Writing notebook server cookie secret to /run/user/1004/jupyter/notebook_cookie_secret
[I 09:39:32.135 NotebookApp] Loading IPython parallel extension
[I 09:39:32.156 NotebookApp] JupyterLab beta preview extension loaded from /home/ubuntu/anaconda3/envs/tensorflow_p36/lib/python3.6/site-packages/jupyterlab
[I 09:39:32.156 NotebookApp] JupyterLab application directory is /home/ubuntu/anaconda3/envs/tensorflow_p36/share/jupyter/lab
[I 09:39:32.296 NotebookApp] [nb_conda] enabled
[I 09:39:32.298 NotebookApp] Serving notebooks from local directory: /home/lab03/detection
[I 09:39:32.298 NotebookApp] 0 active kernels
[I 09:39:32.298 NotebookApp] The Jupyter Notebook is running at:
[I 09:39:32.298 NotebookApp] http://ip-172-31-40-104:8892/
[I 09:39:32.298 NotebookApp] Use Control-C to stop this server and shut down all kernels (twice to skip confirmation).
[W 09:39:32.299 NotebookApp] No web browser found: could not locate runnable browser.
```

### 4. connect jupyter notebook

- 웹에서 aws 주소:포트번호 입력 후 접속

  <img src="images/image-20200129094403515.png" alt="image-20200129094403515" style="zoom:50%;" />

  <img src="images/image-20200129094427137.png" alt="image-20200129094427137" style="zoom:33%;" />







## Darknet 와 기존 YOLO를 통해 학습된 Weights 로 테스트 해보기

1. `git clone https://github.com/pjreddie/darknet.git` 입력 후 clone 받기

2. `cd darknet` 후 `vi Makefile` 입력 후 다음과 같이 설정 변경

   ```
   CUDA 사용 GPU=1
   opencv 사용 OPENCV=1
   ```

3. `make` 입력 후 설정 컴파일 진행

4. `wget https://pjreddie.com/media/files/yolov3.weights` 입력 후 학습이 적용된 weight 파일 다운로드

5. `./darknet detect cfg/yolov3.cfg yolov3.weights data/dog.jpg` 입력 후  테스트 진행









## Darknet 과 YOLO를 통해 object detection 해보기

### 사전 셋팅

- `Darknet`이 설치 되어 있어야 함



- 다음 명령어를 통해 train 및 test 진행
  - ./darknet detector train [data파일] [YOLO 컨피그파일] [darknet network 파일 ] > [로그기록할파일명]

```bash
lab03@ip-172-31-40-104:~/darknet$ ./darknet detector train ~/myoung_snow_unzip/darknet.data ~/myoung_snow_unzip/darknet-yolov3.cfg ~/myoung_snow_unzip/darknet53.conv.74 > ~/myoung_snow_unzip/snowman.log
layer     filters    size              input                output
    0 conv     32  3 x 3 / 1   416 x 416 x   3   ->   416 x 416 x  32  0.299 BFLOPs
    1 conv     64  3 x 3 / 2   416 x 416 x  32   ->   208 x 208 x  64  1.595 BFLOPs
    2 conv     32  1 x 1 / 1   208 x 208 x  64   ->   208 x 208 x  32  0.177 BFLOPs
                                         .
                                         .
  104 conv    256  3 x 3 / 1   104 x 104 x 128   ->   104 x 104 x 256  6.380 BFLOPs
  105 conv     18  1 x 1 / 1   104 x 104 x 256   ->   104 x 104 x  18  0.100 BFLOPs
  106 yolo
Loading weights from /home/lab03/myoung_snow_unzip/darknet53.conv.74...Done!
```

- 로그파일 확인

```bash
lab03@ip-172-31-40-104:~/myoung_snow_unzip$ cat snowman.log
darknet-yolov3
Learning Rate: 0.001, Momentum: 0.9, Decay: 0.0005
Resizing
384
Loaded: 0.091182 seconds
Region 82 Avg IOU: 0.219281, Class: 0.531767, Obj: 0.530265, No Obj: 0.572117, .5R: 0.222222, .75R: 0.000000,  count: 9
Region 94 Avg IOU: 0.342721, Class: 0.062154, Obj: 0.898800, No Obj: 0.495300, .5R: 0.000000, .75R: 0.000000,  count: 1
Region 106 Avg IOU: -nan, Class: -nan, Obj: -nan, No Obj: 0.612533, .5R: -nan, .75R: -nan,  count: 0
Region 82 Avg IOU: 0.269220, Class: 0.574327, Obj: 0.628691, No Obj: 0.572319, .5R: 0.200000, .75R: 0.000000,  count: 5
Region 94 Avg IOU: 0.011954, Class: 0.749137, Obj: 0.728491, No Obj: 0.495370, .5R: 
                                         .
                                         .
lab03@ip-172-31-40-104:~/myoung_snow_unzip$                              
lab03@ip-172-31-40-104:~/myoung_snow_unzip$ cat snowman.log | grep 'avg'
1: 3968.200195, 3968.200195 avg, 0.000000 rate, 2503.904047 seconds, 64 images
2: 3961.218994, 3967.502197 avg, 0.000000 rate, 2536.935550 seconds, 128 images

```

