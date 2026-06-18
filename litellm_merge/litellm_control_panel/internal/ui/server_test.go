package ui

import (
	"net/http"
	"net/http/httptest"
	"testing"

	"github.com/robertpelloni/litellm_control_panel/internal/engine"
)

func TestHandleRankings(t *testing.T) {
	s := NewUIServer(nil, nil, nil)
	s.UpdateModels(engine.RankedModels{
		{ID: "test-model", Provider: "test-provider", Score: 100},
	})

	req, _ := http.NewRequest("GET", "/api/rankings", nil)
	rr := httptest.NewRecorder()
	handler := http.HandlerFunc(s.handleRankings)

	handler.ServeHTTP(rr, req)

	if status := rr.Code; status != http.StatusOK {
		t.Errorf("handler returned wrong status code: got %v want %v", status, http.StatusOK)
	}

	expected := `[{"id":"test-model","provider":"test-provider","parameters":0,"context_length":0,"latency":0,"score":100,"last_benchmark":"0001-01-01T00:00:00Z","prompt_price":0,"completion_price":0}]`
	if rr.Body.String() != expected + "\n" && rr.Body.String() != expected {
		t.Errorf("handler returned unexpected body: got %v want %v", rr.Body.String(), expected)
	}
}
