# 🚀 Deployment Quick Start Guide

**Generated:** December 1, 2025  
**Status:** ✅ READY TO DEPLOY

---

## 📁 Files Generated

All deployment files have been created:

```
deployment/
├── k8s/
│   ├── deployment.yaml ✅
│   └── service.yaml ✅
├── monitoring/
│   ├── prometheus-config.yaml ✅
│   └── alerts.yaml ✅
└── ci-cd/
    └── deploy.yaml ✅

Dockerfile.production ✅
```

---

## 🚢 Quick Deploy Commands

### Option 1: Local Testing with Kind

```bash
# 1. Create local Kubernetes cluster
kind create cluster --name antigravity-jules

# 2. Build and load image
docker build -t antigravity-jules:latest -f Dockerfile.production .
kind load docker-image antigravity-jules:latest --name antigravity-jules

# 3. Deploy
kubectl apply -f deployment/k8s/

# 4. Port forward to test
kubectl port-forward svc/antigravity-jules-svc 8080:80

# 5. Test
curl http://localhost:8080/health
```

### Option 2: Production Deployment

```bash
# 1. Build and tag image
docker build -t antigravity-jules:latest -f Dockerfile.production .
docker tag antigravity-jules:latest ghcr.io/scarmonit/antigravity-jules:latest

# 2. Push to registry
docker push ghcr.io/scarmonit/antigravity-jules:latest

# 3. Update image in deployment.yaml
# Change: image: antigravity-jules:latest
# To: image: ghcr.io/scarmonit/antigravity-jules:latest

# 4. Deploy to Kubernetes
kubectl apply -f deployment/k8s/

# 5. Configure monitoring
kubectl apply -f deployment/monitoring/
```

### Option 3: GitHub Actions CI/CD

```bash
# 1. Copy workflow to .github/workflows/
mkdir -p .github/workflows
cp deployment/ci-cd/deploy.yaml .github/workflows/

# 2. Add secrets to GitHub repository
# Go to: Settings → Secrets and variables → Actions
# Add: KUBECONFIG (your cluster config)

# 3. Push to trigger deployment
git add .
git commit -m "feat: Add production deployment"
git push origin main
```

---

## 🔍 Verification Commands

### Check Deployment Status
```bash
# View pods
kubectl get pods -l app=antigravity-jules

# View service
kubectl get svc antigravity-jules-svc

# View deployment
kubectl get deployment antigravity-jules-deployment

# Check rollout status
kubectl rollout status deployment/antigravity-jules-deployment
```

### View Logs
```bash
# All pods
kubectl logs -l app=antigravity-jules --tail=100

# Specific pod
kubectl logs <pod-name> -f

# Previous container logs
kubectl logs <pod-name> --previous
```

### Test Endpoints
```bash
# Port forward
kubectl port-forward svc/antigravity-jules-svc 8080:80

# Health check
curl http://localhost:8080/health

# Ready check
curl http://localhost:8080/ready
```

---

## 📊 Monitoring Setup

### Add Prometheus Scrape Config

```bash
# If using Prometheus Operator
kubectl apply -f - <<EOF
apiVersion: v1
kind: ConfigMap
metadata:
  name: prometheus-server-conf
  namespace: monitoring
data:
  prometheus.yml: |
$(cat deployment/monitoring/prometheus-config.yaml | sed 's/^/    /')
EOF

# Apply alert rules
kubectl apply -f deployment/monitoring/alerts.yaml
```

### View Metrics

```bash
# Port forward to Prometheus
kubectl port-forward -n monitoring svc/prometheus 9090:9090

# Open browser
open http://localhost:9090
```

---

## 🔧 Troubleshooting

### Pods Not Starting

```bash
# Check events
kubectl describe pod <pod-name>

# Check logs
kubectl logs <pod-name>

# Check image pull
kubectl get events --sort-by='.lastTimestamp'
```

### Service Not Accessible

```bash
# Check endpoints
kubectl get endpoints antigravity-jules-svc

# Check service
kubectl describe svc antigravity-jules-svc

# Test internal connectivity
kubectl run test --rm -it --image=curlimages/curl -- curl http://antigravity-jules-svc/health
```

### High Memory/CPU Usage

```bash
# Check resource usage
kubectl top pods -l app=antigravity-jules

# View resource limits
kubectl describe pod <pod-name> | grep -A 5 "Limits"

# Scale if needed
kubectl scale deployment antigravity-jules-deployment --replicas=5
```

---

## 🎯 Next Steps

1. ✅ Files generated and ready
2. ⏳ Choose deployment method (local/production/CI-CD)
3. ⏳ Configure secrets and environment variables
4. ⏳ Deploy and verify
5. ⏳ Set up monitoring dashboards
6. ⏳ Configure alerts and notifications

---

## 📚 Additional Resources

- **Kubernetes Docs:** https://kubernetes.io/docs/
- **Prometheus Docs:** https://prometheus.io/docs/
- **GitHub Actions:** https://docs.github.com/en/actions

---

**Status:** ✅ ALL FILES GENERATED - READY TO DEPLOY

