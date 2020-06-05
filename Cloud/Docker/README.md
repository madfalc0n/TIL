# Docker

## Manual List

1. [What is Docker?](docker.md)
2. [Docker install](docker_install.md)
3. [Docker private registry for dockerhub](docker_private_registry_for_dockerhub.md)
4. [Docker node web build](docker_node_web_build.md)
5. [Docker mysql manual](docker_mysql_manual.md)
6. [Docker user manual](docker_user_manual.md)





## 기타

```
docker \
  run \
  --detach \
  --env MYSQL_ROOT_PASSWORD=default \
  --env MYSQL_DATABASE=madfalcon_db \
  --name m_mysql \
  --publish 3306:3306 \
  --rm \
mysql;



docker \
  run \
  --name python_test \
  -it \
  -p 7000-7009:7000-7009 \
  --rm \
  -v "/home/madfalcon/m_tmp/python:/usr/django/app" \
python:3.6 /bin/bash 





FROM python:3.6
  
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        postgresql-client \
    && rm -rf /var/lib/apt/lists/*

COPY . /app
RUN chmod 755 /app/start.sh
WORKDIR /app
RUN pip install django

EXPOSE 7000
ENTRYPOINT ["/app/start.sh"]


start.sh
#!/bin/bash

python manage.py makemigrations
python manage.py migrate

python manage.py runserver 0.0.0.0:7000



이미지 빌드
docker build -t dockerdjango .



docker run -it --rm -d -p 7000:7000 --name m_web dockerdjango:1.0  
```

