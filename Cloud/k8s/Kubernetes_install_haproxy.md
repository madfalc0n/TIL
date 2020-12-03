# Kubernetes Install HAproxy





## 0. Helm 설치

HAproxy를 설치하기 위해 Helm이라는 쿠버네티스의 패키지를 관리하는 패키지 매니저를 설치하자. [Helm](https://helm.sh/) 사이트 접속해서 다운로드 하자. 본인은 snap이 설치되어 있어서 snap을 이용하여 설치했다.

```
sudo snap install helm --classic
```



## 1. HAproxy 설치

[메뉴얼](https://www.haproxy.com/documentation/kubernetes/latest/installation/community/kubernetes/)을 참조하여 아래 명령어를 입력한다.

1. helm repo add haproxytech https://haproxytech.github.io/helm-charts

   ```bash
   madfalcon@madfalcon:~/my_tmp/component$ helm repo add haproxytech https://haproxytech.github.io/helm-charts
   "haproxytech" has been added to your repositories
   ```

2. helm repo update

   ```bash
   madfalcon@madfalcon:~/my_tmp/component$ helm repo update
   Hang tight while we grab the latest from your chart repositories...
   ...Successfully got an update from the "haproxytech" chart repository
   Update Complete. 뉸appy Helming!
   madfalcon@madfalcon:~/my_tmp/component$ 
   ```

3. helm install kubernetes-ingress haproxytech/kubernetes-ingress

   ```bash
   madfalcon@madfalcon:~/my_tmp/component$ helm install kubernetes-ingress haproxytech/kubernetes-ingress
   NAME: kubernetes-ingress
   LAST DEPLOYED: Wed Dec  2 16:31:07 2020
   NAMESPACE: default
   STATUS: deployed
   REVISION: 1
   TEST SUITE: None
   NOTES:
   HAProxy Kubernetes Ingress Controller has been successfully installed.
   
   Controller image deployed is: "haproxytech/kubernetes-ingress:1.4.9".
   Your controller is of a "Deployment" kind. Your controller service is running as a "NodePort" type.
   RBAC authorization is enabled.
   
   Service ports mapped are:
     - name: http
       containerPort: 80
       protocol: TCP
     - name: https
       containerPort: 443
       protocol: TCP
     - name: stat
       containerPort: 1024
       protocol: TCP
   
   Node IP can be found with:
     $ kubectl --namespace default get nodes -o jsonpath="{.items[0].status.addresses[1].address}"
   
   The following ingress resource routes traffic to pods that match the following:
     * service name: web
     * client's Host header: webdemo.com
     * path begins with /
   
     ---
     apiVersion: networking.k8s.io/v1beta1
     kind: Ingress
     metadata:
       name: web-ingress
       namespace: default
     spec:
       rules:
       - host: webdemo.com
         http:
           paths:
           - path: /
             backend:
               serviceName: web
               servicePort: 80
   
   In case that you are using multi-ingress controller environment, make sure to use ingress.class annotation and match it
   with helm chart option controller.ingressClass.
   
   For more examples and up to date documentation, please visit:
     * Helm chart documentation: https://github.com/haproxytech/helm-charts/tree/master/kubernetes-ingress
     * Controller documentation: https://www.haproxy.com/documentation/hapee/2-0r1/traffic-management/kubernetes-ingress-controller/
     * Annotation reference: https://github.com/haproxytech/kubernetes-ingress/tree/master/documentation
     * Image parameters reference: https://github.com/haproxytech/kubernetes-ingress/blob/master/documentation/controller.md
   madfalcon@madfalcon:~/my_tmp/component$ 
   ```

   1. 특정버전을 설치할 수 있다.

      1. helm search repo haproxy --versions

         ```bash
         # 설치가능한 버전 확인
         madfalcon@madfalcon:~/my_tmp/component$ helm search repo haproxy --versions
         NAME                            CHART VERSION   APP VERSION     DESCRIPTION                                       
         haproxytech/haproxy             1.1.1           2.2.4           A Helm chart for HAProxy on Kubernetes            
         haproxytech/haproxy             1.1.0           2.2.4           A Helm chart for HAProxy on Kubernetes            
         haproxytech/haproxy             1.0.1           2.2.4           A Helm chart for HAProxy on Kubernetes            
         haproxytech/kubernetes-ingress  1.8.2           1.4.9           A Helm chart for HAProxy Kubernetes Ingress Con...
         haproxytech/kubernetes-ingress  1.8.1           1.4.9           A Helm chart for HAProxy Kubernetes Ingress Con...
         haproxytech/kubernetes-ingress  1.8.0           1.4.9           A Helm chart for HAProxy Kubernetes Ingress Con...
         ```

      2. helm install kubernetes-ingress haproxytech/kubernetes-ingress --version 1.4.9



## 3. 설치 및 확인

1. kubectl get pods

   ```bash
   madfalcon@madfalcon:~/my_tmp/component$ kubectl get pods
   NAME                                                    READY   STATUS             RESTARTS   AGE
   kubernetes-ingress-75bd986f6c-dgnvr                     1/1     Running            0          15m
   kubernetes-ingress-75bd986f6c-lrzgq                     1/1     Running            0          15m
   kubernetes-ingress-default-backend-759ccc6c98-7hsnf     1/1     Running            0          15m
   kubernetes-ingress-default-backend-759ccc6c98-s72v2     1/1     Running            0          15m
   ```

2. kubectl get svc -A

   ```bash
   madfalcon@madfalcon:~/my_tmp/component$ kubectl get svc -A
   NAMESPACE     NAME                                   TYPE        CLUSTER-IP       EXTERNAL-IP   PORT(S)                                     AGE
   default       kubernetes                             ClusterIP   10.96.0.1        <none>        443/TCP                                     160m
   default       kubernetes-ingress                     NodePort    10.107.106.183   <none>        80:30251/TCP,443:31065/TCP,1024:31305/TCP   16m
   default       kubernetes-ingress-default-backend     ClusterIP   None             <none>        8080/TCP                                    16m
   kube-system   kube-dns                               ClusterIP   10.96.0.10       <none>        53/UDP,53/TCP,9153/TCP                      160m
   madfalcon@madfalcon:~/my_tmp/component$ 
   ```

3. kubectl get all --all-namespace

   ```bash
   madfalcon@madfalcon:~/my_tmp/component$ kubectl get all --all-namespaces                                
   NAMESPACE     NAME                                                      READY   STATUS    RESTARTS   AGE
   default       pod/kubernetes-ingress-75bd986f6c-2nwzq                   1/1     Running   0          15s
   default       pod/kubernetes-ingress-75bd986f6c-8b95m                   1/1     Running   0          15s
   default       pod/kubernetes-ingress-default-backend-759ccc6c98-cmnmb   1/1     Running   0          15s
   default       pod/kubernetes-ingress-default-backend-759ccc6c98-n9lpx   1/1     Running   0          15s
   kube-system   pod/coredns-f9fd979d6-chdsg                               1/1     Running   0          179m
   kube-system   pod/coredns-f9fd979d6-kqgmd                               1/1     Running   0          179m
   kube-system   pod/etcd-madfalcon.master.com                             1/1     Running   0          179m
   kube-system   pod/kube-apiserver-madfalcon.master.com                   1/1     Running   0          179m
   kube-system   pod/kube-controller-manager-madfalcon.master.com          1/1     Running   0          179m
   kube-system   pod/kube-flannel-ds-2gmtp                                 1/1     Running   0          167m
   kube-system   pod/kube-flannel-ds-wnpnb                                 1/1     Running   0          166m
   kube-system   pod/kube-proxy-rzc2j                                      1/1     Running   0          166m
   kube-system   pod/kube-proxy-td4c4                                      1/1     Running   0          179m
   kube-system   pod/kube-scheduler-madfalcon.master.com                   1/1     Running   0          179m
   
   NAMESPACE     NAME                                         TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)                                     AGE
   default       service/kubernetes                           ClusterIP   10.96.0.1       <none>        443/TCP                                     4m57s
   default       service/kubernetes-ingress                   NodePort    10.106.51.224   <none>        80:30308/TCP,443:32171/TCP,1024:32153/TCP   15s
   default       service/kubernetes-ingress-default-backend   ClusterIP   None            <none>        8080/TCP                                    15s
   kube-system   service/kube-dns                             ClusterIP   10.96.0.10      <none>        53/UDP,53/TCP,9153/TCP                      179m
   
   NAMESPACE     NAME                             DESIRED   CURRENT   READY   UP-TO-DATE   AVAILABLE   NODE SELECTOR            AGE
   kube-system   daemonset.apps/kube-flannel-ds   2         2         2       2            2           <none>                   167m
   kube-system   daemonset.apps/kube-proxy        2         2         2       2            2           kubernetes.io/os=linux   179m
   
   NAMESPACE     NAME                                                 READY   UP-TO-DATE   AVAILABLE   AGE
   default       deployment.apps/kubernetes-ingress                   2/2     2            2           15s
   default       deployment.apps/kubernetes-ingress-default-backend   2/2     2            2           15s
   kube-system   deployment.apps/coredns                              2/2     2            2           179m
   
   NAMESPACE     NAME                                                            DESIRED   CURRENT   READY   AGE
   default       replicaset.apps/kubernetes-ingress-75bd986f6c                   2         2         2       15s
   default       replicaset.apps/kubernetes-ingress-default-backend-759ccc6c98   2         2         2       15s
   kube-system   replicaset.apps/coredns-f9fd979d6                               2         2         2       179m
   ```

   

## 4. helm 명령어를 통한 설치한 컨트롤러 삭제

helm을 통해 설치한 컨트롤러 같은경우 삭제를 통해 쉽게 관리가 가능하다.

1. helm list --all

   ```bash
   # helm 통해 설치한 모듈 관리
   madfalcon@madfalcon:~/my_tmp/component$ helm list --all
   NAME                    NAMESPACE       REVISION        UPDATED                                 STATUS          CHART                           APP VERSION
   kubernetes-ingress      default         1               2020-12-02 17:05:58.775830711 +0000 UTC deployed        kubernetes-ingress-1.8.2        1.4.9      
   
   ```

2. helm del kubernetes-ingress

   ```bash
   # del 명령어를 통한 삭제
   madfalcon@madfalcon:~/my_tmp/component$ helm del kubernetes-ingress
   release "kubernetes-ingress" uninstalled
   madfalcon@madfalcon:~/my_tmp/component$ helm list --all            
   NAME    NAMESPACE       REVISION        UPDATED STATUS  CHART   APP VERSION
   
   #모듈 또한 완벽히 삭제됨
   madfalcon@madfalcon:~/my_tmp/component$ kubectl get all --all-namespaces
   NAMESPACE     NAME                                                      READY   STATUS        RESTARTS   AGE
   default       pod/kubernetes-ingress-75bd986f6c-2nwzq                   0/1     Terminating   0          2m1s
   default       pod/kubernetes-ingress-75bd986f6c-8b95m                   0/1     Terminating   0          2m1s
   default       pod/kubernetes-ingress-default-backend-759ccc6c98-cmnmb   0/1     Terminating   0          2m1s
   default       pod/kubernetes-ingress-default-backend-759ccc6c98-n9lpx   0/1     Terminating   0          2m1s
   kube-system   pod/coredns-f9fd979d6-chdsg                               1/1     Running       0          3h
   kube-system   pod/coredns-f9fd979d6-kqgmd                               1/1     Running       0          3h
   kube-system   pod/etcd-madfalcon.master.com                             1/1     Running       0          3h1m
   kube-system   pod/kube-apiserver-madfalcon.master.com                   1/1     Running       0          3h1m
   kube-system   pod/kube-controller-manager-madfalcon.master.com          1/1     Running       0          3h1m
   kube-system   pod/kube-flannel-ds-2gmtp                                 1/1     Running       0          169m
   kube-system   pod/kube-flannel-ds-wnpnb                                 1/1     Running       0          168m
   kube-system   pod/kube-proxy-rzc2j                                      1/1     Running       0          168m
   kube-system   pod/kube-proxy-td4c4                                      1/1     Running       0          3h
   kube-system   pod/kube-scheduler-madfalcon.master.com                   1/1     Running       0          3h1m
   
   NAMESPACE     NAME                 TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)                  AGE
   default       service/kubernetes   ClusterIP   10.96.0.1    <none>        443/TCP                  6m43s
   kube-system   service/kube-dns     ClusterIP   10.96.0.10   <none>        53/UDP,53/TCP,9153/TCP   3h1m
   
   NAMESPACE     NAME                             DESIRED   CURRENT   READY   UP-TO-DATE   AVAILABLE   NODE SELECTOR            AGE
   kube-system   daemonset.apps/kube-flannel-ds   2         2         2       2            2           <none>                   169m
   kube-system   daemonset.apps/kube-proxy        2         2         2       2            2           kubernetes.io/os=linux   3h1m
   
   NAMESPACE     NAME                      READY   UP-TO-DATE   AVAILABLE   AGE
   kube-system   deployment.apps/coredns   2/2     2            2           3h1m
   
   NAMESPACE     NAME                                DESIRED   CURRENT   READY   AGE
   kube-system   replicaset.apps/coredns-f9fd979d6   2         2         2       3h
   ```

   

## 참조

1. [Helm 공식 홈페이지](https://www.haproxy.com/documentation/kubernetes/latest/installation/community/kubernetes/)