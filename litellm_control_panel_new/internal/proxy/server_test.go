package proxy

import (
	"bytes"
	"context"
	"fmt"
	"io"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
	"time"

	"github.com/robertpelloni/freellm/internal/engine"
)

type mockTransport struct {
	roundTrip func(*http.Request) (*http.Response, error)
}

func (m *mockTransport) RoundTrip(req *http.Request) (*http.Response, error) {
	return m.roundTrip(req)
}

func TestGatewayQueueing(t *testing.T) {
	g := NewGateway(0, nil) // 0 workers to force queueing

	g.UpdateModels(engine.RankedModels{
		{ID: "test-model", Provider: "openrouter"},
	})

	req := httptest.NewRequest("POST", "/v1/chat/completions", bytes.NewBufferString(`{"model":"any", "messages":[{"role":"user","content":"hi"}]}`))
	ctx, cancel := context.WithTimeout(context.Background(), 100*time.Millisecond)
	defer cancel()
	req = req.WithContext(ctx)

	go g.ServeHTTP(httptest.NewRecorder(), req)

	select {
	case job := <-g.Queue:
		if job.Request.URL.Path != "/v1/chat/completions" {
			t.Errorf("Unexpected path: %s", job.Request.URL.Path)
		}
	case <-time.After(200 * time.Millisecond):
		t.Errorf("Job did not reach queue")
	}
}

func TestHealthChecks(t *testing.T) {
	g := &Gateway{}

	// Test Liveness
	req := httptest.NewRequest("GET", "/health/liveness", nil)
	w := httptest.NewRecorder()
	g.ServeHTTP(w, req)
	if w.Code != 200 {
		t.Errorf("Liveness failed: %d", w.Code)
	}

	// Test Readiness
	req = httptest.NewRequest("GET", "/health/readiness", nil)
	w = httptest.NewRecorder()
	g.ServeHTTP(w, req)
	if w.Code != 503 {
		t.Errorf("Readiness should fail: %d", w.Code)
	}

	g.UpdateModels(engine.RankedModels{{ID: "m1", Provider: "openrouter"}})
	w = httptest.NewRecorder()
	g.ServeHTTP(w, req)
	if w.Code != 200 {
		t.Errorf("Readiness should pass: %d", w.Code)
	}
}

func TestRoutingLogic(t *testing.T) {
	g := NewGateway(1, nil)
	g.PrimaryCount = 1 // Rotate after 1 failure

	g.UpdateModels(engine.RankedModels{
		{ID: "primary-fail", Provider: "openrouter"},
		{ID: "fallback-success", Provider: "openrouter"},
	})

	// Mock Transport to simulate rotation
	g.Client = &http.Client{
		Transport: &mockTransport{
			roundTrip: func(req *http.Request) (*http.Response, error) {
				body, _ := io.ReadAll(req.Body)
				if strings.Contains(string(body), "primary-fail") {
					return &http.Response{
						StatusCode: 500,
						Body:       io.NopCloser(bytes.NewBufferString(`{"error":"fail"}`)),
						Header:     make(http.Header),
					}, nil
				}
				if strings.Contains(string(body), "fallback-success") {
					return &http.Response{
						StatusCode: 200,
						Body:       io.NopCloser(bytes.NewBufferString(`{"choices":[{"message":{"content":"ok"}}]}`)),
						Header:     make(http.Header),
					}, nil
				}
				return nil, fmt.Errorf("unexpected request")
			},
		},
	}

	respChan := make(chan *ProxyResponse, 1)
	req := httptest.NewRequest("POST", "/v1/chat/completions", bytes.NewBufferString(`{"model":"any", "messages":[]}`))

	job := &RequestJob{
		Request:  req,
		Response: respChan,
		Ctx:      context.Background(),
	}

	// Manually process job (since we injected the client)
	go g.processJob(job)

	select {
	case resp := <-respChan:
		if resp.Err != nil {
			t.Errorf("Unexpected error: %v", resp.Err)
		}
		if resp.Status != 200 {
			t.Errorf("Expected 200, got %d", resp.Status)
		}
		if !strings.Contains(string(resp.Body), "ok") {
			t.Errorf("Unexpected body: %s", string(resp.Body))
		}
	case <-time.After(2 * time.Second):
		t.Errorf("Timeout waiting for response")
	}
}

func TestFallbackGroup(t *testing.T) {
	g := NewGateway(1, nil)
	g.PrimaryCount = 1

	g.UpdateModels(engine.RankedModels{
		{ID: "p1", Provider: "openrouter"},
		{ID: "f1", Provider: "openrouter"},
	})

	g.Client = &http.Client{
		Transport: &mockTransport{
			roundTrip: func(req *http.Request) (*http.Response, error) {
				body, _ := io.ReadAll(req.Body)
				if strings.Contains(string(body), "p1") {
					return &http.Response{StatusCode: 503, Body: io.NopCloser(bytes.NewBufferString("fail")), Header: make(http.Header)}, nil
				}
				return &http.Response{StatusCode: 200, Body: io.NopCloser(bytes.NewBufferString("ok")), Header: make(http.Header)}, nil
			},
		},
	}

	respChan := make(chan *ProxyResponse, 1)
	req := httptest.NewRequest("POST", "/v1/chat/completions", bytes.NewBufferString(`{"model":"any", "messages":[]}`))
	job := &RequestJob{Request: req, Response: respChan, Ctx: context.Background()}

	go g.processJob(job)

	select {
	case resp := <-respChan:
		if resp.Status != 200 {
			t.Errorf("Fallback failed with status %d", resp.Status)
		}
	case <-time.After(2 * time.Second):
		t.Errorf("Timeout")
	}
}
