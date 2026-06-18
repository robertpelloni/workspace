package engine

import (
	"testing"
)

func TestCalculateScore(t *testing.T) {
	b := NewBenchmarker(nil, 100, nil)

	// Test case 1: Large model, low latency
	score1 := b.CalculateScore(405, 0.1, 128000)

	// Test case 2: Small model, high latency
	score2 := b.CalculateScore(7, 2.0, 4096)

	if score1 <= score2 {
		t.Errorf("Expected score1 (%f) to be greater than score2 (%f)", score1, score2)
	}
}

func TestExtractParameters(t *testing.T) {
	b := NewBenchmarker(nil, 100, nil)

	tests := []struct {
		id       string
		expected int
	}{
		{"meta-llama/llama-3.1-405b-instruct", 405},
		{"groq/llama3-70b-8192", 70},
		{"mistralai/mixtral-8x7b-v0.1", 7},
		{"no-numbers-here", 0},
	}

	for _, tt := range tests {
		got := b.ExtractParameters(tt.id, "", "")
		if got != tt.expected {
			t.Errorf("ExtractParameters(%s) = %d; want %d", tt.id, got, tt.expected)
		}
	}
}
