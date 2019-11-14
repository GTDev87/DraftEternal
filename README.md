# For Dev (mac instructions)

## Install Postgres
```
brew install postgres
```
## Install Elixir
```
brew install elixir
```
## Install Node
https://nodejs.org/en/download/
## Intall Yarn
```
brew install yarn
```
## Install Reason React
```
yarn add --global bs-platform
```

## set up env from secret 
```
# find greg
source dev-secret-config.env
```

## setup db local

```
psql -U gt -d postgres # use your superuser mine is gt

postgres=# alter user postgres superuser;
postgres=# exit
mix ecto.create

# exit

mix do event_store.create, event_store.init -e DraftEternalApi.EventStore  # need to add to remote setup
mix ecto.migrate --all
mix run apps/drafteternal_api/priv/repo/seeds.exs
```

## Run app

```
# backend in /api
mix deps.get
iex -S mix phx.server 

# frontend in /frontend
yarn install
yarn local-introspection
yarn start

```

# delete event store

```
mix event_store.drop -e DraftEternalApi.EventStore
```

# For Prod... ugh
## set
DRAFTETERNAL_GOOGLE_CLIENT_ID
DRAFTETERNAL_GOOGLE_CLIENT_SECRET
get secret env file
`secret-config.env`

## Run commands:

```
eval "$(docker-machine env default)"
docker-machine start default

docker-compose build
docker-compose up
```

check volume directory in docker-compose.yml
volumes

docker-compose

## dev setup

steps are included here https://gist.github.com/kevin-smets/b91a34cea662d0c523968472a81788f7

### install kompose,minikube,docker,virtualbox

OSX
```
curl -L https://github.com/kubernetes/kompose/releases/download/v1.1.0/kompose-darwin-amd64 -o kompose
brew update && brew install kubectl && brew cask install docker minikube virtualbox
```

### verify

```
docker --version                # Docker version 17.09.0-ce, build afdb6d4
docker-compose --version        # docker-compose version 1.16.1, build 6d1ac21
docker-machine --version        # docker-machine version 0.12.2, build 9371605
minikube version                # minikube version: v0.22.3
kubectl version --client        # Client Version: version.Info{Major:"1", Minor:"8", GitVersion:"v1.8.1", GitCommit:"f38e43b221d08850172a9a4ea785a86a3ffa3b3a", GitTreeState:"clean", BuildDate:"2017-10-12T00:45:05Z", GoVersion:"go1.9.1", Compiler:"gc", Platform:"darwin/amd64"}      

```

### tagging docker repos

```
docker tag frontend gtdev87/drafteternal-frontend
docker push gtdev87/drafteternal-frontend
```

### Start Minikube

```
minikube start
```

### Check kubernetes

```
kubectl get nodes
```

### Use minikube's built-in docker daemon

```
eval $(minikube docker-env)
```

note revert is `eval $(docker-machine env -u)`

### Build, deploy and run an image on your local k8s setup crete local registry

Run docker locally to build the image (include steps later)

```
docker run -d -p 5000:31500 --restart=always --name registry registry:2
```

```
cd frontend
docker build -t drafteternal-frontend . -f Dockerfile.dev
docker tag drafteternal-frontend gtdev87/drafteternal-frontend
docker push gtdev87/drafteternal-frontend

cd ../api
docker build -t drafteternal-api . -f Dockerfile.dev
docker tag drafteternal-api gtdev87/drafteternal-api
docker push gtdev87/drafteternal-api
```

### install docker-compose

### docker login

### install heroku
### login heroku

### run build and run kompose

```
export KUBECONFIG=/Users/GT/.secrets/clusters/drafteternal/auth/kubeconfig
docker-machine restart default
docker-machine env default
eval "$(docker-machine env default)"

make up
# is having docker login error https://github.com/docker/for-mac/issues/2131
```


### port forwarding

```
kubectl get pods
kubectl port-forward <pod> 8080:3000
kubectl exec -it <pod> mix ecto.create
kubectl exec -it <pod> mix ecto.migrate
```

to find use localhost:8080

### local dashboard

```
minikube dashboard
```

### stop kube
```
kompose down
minikube stop
minikube destroy
```

## To deploy to prod from local comp

### install terraform
### install kubectl

### instlall terraform for typhoon using the following steps (os version for me darwin)

```
# for me
wget https://github.com/poseidon/terraform-provider-ct/releases/download/v0.3.2/terraform-provider-ct-v0.3.2-darwin-amd64.tar.gz
tar xzf terraform-provider-ct-v0.3.2-darwin-amd64.tar.gz
mv terraform-provider-ct-v0.3.2-darwin-amd64/terraform-provider-ct ~/.terraform.d/plugins/terraform-provider-ct_v0.3.2


```


### configure .terraformrc



https://typhoon.psdn.io/cl/digital-ocean/


Add fingerprint to infra/clusters/terraform/providers.tf
```
ssh-keygen -E md5 -lf ~/.ssh/id_rsa.pub | awk '{print $2}'
```

`ssh_fingerprints = ["06:69:bc:6d:f6:fc:df:30:d7:ec:8a:2d:01:c6:35:6e"]`

### Add ssh agent

```
ssh-add ~/.ssh/id_rsa
ssh-add -L
```

```
cd infra/clusters/terraform/
terraform init
terraform plan
terraform apply
# this can take 10 mins
```

### To ssh into machne (optional)

```
ssh core@<machine-ip>
```

### setup kubernetes secret

```
export KUBECONFIG=/Users/GT/.secrets/clusters/drafteternal/auth/kubeconfig
```

### setup cluster

it may make sense to initially start with non existant volume

if so delete volume from digitalocean

```
cd ../kubernetes
kubectl create -f ./secret.yml

# if schema error https://stackoverflow.com/questions/55417410/kubernetes-create-deployment-unexpected-schemaerror

kubectl apply -f https://raw.githubusercontent.com/digitalocean/csi-digitalocean/master/deploy/kubernetes/releases/csi-digitalocean-v0.4.0.yaml
```

### clean repos
```
make clean
```

### install Virtual box

### Start up Boot2Dock

```
docker-machine create --driver virtualbox --virtualbox-disk-size "400000" default
```
or 
```
# if already created
make clean # clean folders
docker-machine restart default

# worst case
docker-machine rm default
docker-machine create --driver virtualbox --virtualbox-disk-size "400000" default

# restart laptop and do ^ super worst case
```

### Test and setup with

```
docker-machine env default
eval "$(docker-machine env default)"
```

### Docker registry dockerhub



```

cd ../../../ # root
kompose up --verbose
```

if pv doesn't spawn.  create volume manually on digital ocean


### See kubernetes cluster

```
kubectl get deployment,svc,pods,pvc
```

### expose app
```
kubectl create -R -f infra/clusters/kubernetes/typhoon/addons/nginx-ingress/digital-ocean/
kubectl create -f infra/clusters/kubernetes/staging-ingress-setup.yaml

``` 


### create domains for Type A
```
drafteternal-workers.dubcell.com
api.drafteternal-workers.dubcell.com
auth.drafteternal-workers.dubcell.com
```