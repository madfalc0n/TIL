# Python + tesseract를 이용해 문자검출하기



## 설치

1. https://github.com/tesseract-ocr/tesseract/wiki 에 접속해서 윈도우용 다운로드

2. 설치 후 파이썬 노트북에서 다음 입력

   - pip install pytesseract

     ``` bash
     (base) C:\Users\student>pip install pytesseract
     Collecting pytesseract
       Downloading https://files.pythonhosted.org/packages/a9/7c/9ed191f009dac30682c320d925d50dbc39ae621310218a95f970ee4ff5e5/pytesseract-0.3.1.tar.gz
     Requirement already satisfied: Pillow in c:\programdata\anaconda3\lib\site-packages (from pytesseract) (6.2.0)
     Building wheels for collected packages: pytesseract
       Building wheel for pytesseract (setup.py) ... done
       Created wheel for pytesseract: filename=pytesseract-0.3.1-py2.py3-none-any.whl size=13379 sha256=52b4b43f02dc5f4dbab6aacce77c395b18beb2209ff19a552faadc60b01c6cb8
       Stored in directory: C:\Users\student\AppData\Local\pip\Cache\wheels\01\84\d2\10729e740ad8f5c5d3b02d10c7f15afeaa390f7723bd59dbd7
     Successfully built pytesseract
     Installing collected packages: pytesseract
     Successfully installed pytesseract-0.3.1
     ```



## 사용하기

- import pytesseract

    ```python
    import pytesseract
    pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract' #테서렉트 설치경로

    print(pytesseract.image_to_string('out.png'))
    ```
    
    ![image-20200110101528406](images/image-20200110101528406.png)
    
    > 잘 검출이 안된다...





## 한글설정





## 주의사항

글자를 판독할 수 있도록 전처리 과정이 꼭필요하다.