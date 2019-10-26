# create ingress for digital ocean
This comes from https://github.com/poseidon/typhoon/tree/master/addons/nginx-ingress/digital-ocean :


```
kubectl create -R -f typhoon/addons/nginx-ingress/digital-ocean/
kubectl create -f ingress-setup.yaml

```

# undo 

```
kubectl delete namespace/ingress  clusterrolebinding.rbac.authorization.k8s.io/ingress clusterrole.rbac.authorization.k8s.io/ingress ingress.extensions/frontend
```
