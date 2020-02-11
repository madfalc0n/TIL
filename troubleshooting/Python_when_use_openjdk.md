# Python에 openjdk 연동시





```bash
(base) C:\Windows\system32>pip uninstall jpype1
Uninstalling JPype1-0.7.1:
  Would remove:
    c:\programdata\anaconda3\lib\site-packages\_jpype.cp37-win_amd64.pdb
    c:\programdata\anaconda3\lib\site-packages\_jpype.cp37-win_amd64.pyd
    c:\programdata\anaconda3\lib\site-packages\jpype1-0.7.1.dist-info\*
    c:\programdata\anaconda3\lib\site-packages\jpype\*
Proceed (y/n)? y
  Successfully uninstalled JPype1-0.7.1
ERROR: Exception:
Traceback (most recent call last):
  File "C:\ProgramData\Anaconda3\lib\shutil.py", line 398, in _rmtree_unsafe
    os.unlink(fullname)
PermissionError: [WinError 5] 액세스가 거부되었습니다: 'C:\\Users\\student\\AppData\\Local\\Temp\\pip-uninstall-ys_07f4a\\_jpype.cp37-win_amd64.pyd'

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\cli\base_command.py", line 188, in main
    status = self.run(options, args)
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\commands\uninstall.py", line 78, in run
    uninstall_pathset.commit()
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\req\req_uninstall.py", line 444, in commit
    self._moved_paths.commit()
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\req\req_uninstall.py", line 284, in commit
    save_dir.cleanup()
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\utils\temp_dir.py", line 83, in cleanup
    rmtree(self.path)
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_vendor\retrying.py", line 49, in wrapped_f
    return Retrying(*dargs, **dkw).call(f, *args, **kw)
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_vendor\retrying.py", line 212, in call
    raise attempt.get()
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_vendor\retrying.py", line 247, in get
    six.reraise(self.value[0], self.value[1], self.value[2])
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_vendor\six.py", line 693, in reraise
    raise value
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_vendor\retrying.py", line 200, in call
    attempt = Attempt(fn(*args, **kwargs), attempt_number, False)
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\utils\misc.py", line 166, in rmtree
    onerror=rmtree_errorhandler)
  File "C:\ProgramData\Anaconda3\lib\shutil.py", line 516, in rmtree
    return _rmtree_unsafe(path, onerror)
  File "C:\ProgramData\Anaconda3\lib\shutil.py", line 400, in _rmtree_unsafe
    onerror(os.unlink, fullname, sys.exc_info())
  File "C:\ProgramData\Anaconda3\lib\site-packages\pip\_internal\utils\misc.py", line 178, in rmtree_errorhandler
    func(path)
PermissionError: [WinError 5] 액세스가 거부되었습니다: 'C:\\Users\\student\\AppData\\Local\\Temp\\pip-uninstall-ys_07f4a\\_jpype.cp37-win_amd64.pyd'

(base) C:\Windows\system32>pip uninstall jpype1
Uninstalling JPype1-0.7.0:
  Would remove:
    c:\programdata\anaconda3\lib\site-packages\jpype1-0.7.0.dist-info\*
Proceed (y/n)? y
  Successfully uninstalled JPype1-0.7.0

(base) C:\Windows\system32>cd ..

(base) C:\Windows>cd ..

(base) C:\>cd Users

(base) C:\Users>cd student

(base) C:\Users\student>cd Downloads

(base) C:\Users\student\Downloads>pip install JPype1-0.7.1-cp37-cp37m-win_amd64.whl
Processing c:\users\student\downloads\jpype1-0.7.1-cp37-cp37m-win_amd64.whl
Installing collected packages: JPype1
Successfully installed JPype1-0.7.1



(base) C:\Users\student\Downloads>python
Python 3.7.4 (default, Aug  9 2019, 18:34:13) [MSC v.1915 64 bit (AMD64)] :: Anaconda, Inc. on win32
Type "help", "copyright", "credits" or "license" for more information.

>>> from konlpy.tag import Okt
>>> okt = Okt()

Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "C:\Users\student\AppData\Roaming\Python\Python37\site-packages\konlpy\tag\_okt.py", line 91, in __init__
    jvm.init_jvm(jvmpath, max_heap_size)
  File "C:\Users\student\AppData\Roaming\Python\Python37\site-packages\konlpy\jvm.py", line 55, in init_jvm
    jvmpath = jvmpath or jpype.getDefaultJVMPath()
  File "C:\ProgramData\Anaconda3\lib\site-packages\jpype\_core.py", line 345, in getDefaultJVMPath
    return finder.get_jvm_path()
  File "C:\ProgramData\Anaconda3\lib\site-packages\jpype\_jvmfinder.py", line 184, in get_jvm_path
    .format(self._libfile))
jpype._jvmfinder.JVMNotFoundException: No JVM shared library file (jvm.dll) found. Try setting up the JAVA_HOME environment variable properly.
>>>             
## 오픈JDK 설치가 필요하다.(설치 + 환경변수 설정후 다시 적용)

```

