package proxy

import (
	"encoding/json"
	"time"
)

func TransformRequestBody(provider string, openaiBody []byte) ([]byte, error) {
	// First, sanitize the request body (LiteLLM parity)
	sanitized, _ := sanitizeRequest(provider, openaiBody)
	openaiBody = sanitized

	switch provider {
	case "anthropic":
		return transformToAnthropic(openaiBody)
	case "gemini":
		return transformToGemini(openaiBody)
	default:
		return openaiBody, nil
	}
}

func sanitizeRequest(provider string, body []byte) ([]byte, error) {
	var payload map[string]interface{}
	if err := json.Unmarshal(body, &payload); err != nil {
		return body, err
	}

	// Remove unsupported params for specific providers
	unsupported := []string{"frequency_penalty", "presence_penalty", "logit_bias"}

	switch provider {
	case "anthropic", "gemini":
		for _, p := range unsupported {
			delete(payload, p)
		}
	}

	return json.Marshal(payload)
}

func transformToAnthropic(body []byte) ([]byte, error) {
	var input struct {
		Model    string `json:"model"`
		Messages []struct {
			Role    string `json:"role"`
			Content string `json:"content"`
		} `json:"messages"`
		Stream    bool `json:"stream"`
		MaxTokens int  `json:"max_tokens"`
	}
	if err := json.Unmarshal(body, &input); err != nil {
		return nil, err
	}

	if input.MaxTokens == 0 {
		input.MaxTokens = 4096
	}

	output := map[string]interface{}{
		"model":      input.Model,
		"messages":   input.Messages,
		"stream":     input.Stream,
		"max_tokens": input.MaxTokens,
	}
	return json.Marshal(output)
}

func TransformResponseBody(provider string, providerBody []byte) ([]byte, error) {
	switch provider {
	case "anthropic":
		return transformFromAnthropic(providerBody)
	case "gemini":
		return transformFromGemini(providerBody)
	default:
		return providerBody, nil
	}
}

func transformFromAnthropic(body []byte) ([]byte, error) {
	var input struct {
		Content []struct {
			Text string `json:"text"`
		} `json:"content"`
		Model string `json:"model"`
		ID    string `json:"id"`
	}
	if err := json.Unmarshal(body, &input); err != nil {
		return body, nil
	}

	text := ""
	if len(input.Content) > 0 {
		text = input.Content[0].Text
	}

	output := map[string]interface{}{
		"id":      input.ID,
		"object":  "chat.completion",
		"created": time.Now().Unix(),
		"model":   input.Model,
		"choices": []map[string]interface{}{
			{
				"index": 0,
				"message": map[string]string{
					"role":    "assistant",
					"content": text,
				},
				"finish_reason": "stop",
			},
		},
	}
	return json.Marshal(output)
}

func transformFromGemini(body []byte) ([]byte, error) {
	var input struct {
		Candidates []struct {
			Content struct {
				Parts []struct {
					Text string `json:"text"`
				} `json:"parts"`
			} `json:"content"`
		} `json:"candidates"`
	}
	if err := json.Unmarshal(body, &input); err != nil {
		return body, nil
	}

	text := ""
	if len(input.Candidates) > 0 && len(input.Candidates[0].Content.Parts) > 0 {
		text = input.Candidates[0].Content.Parts[0].Text
	}

	output := map[string]interface{}{
		"id":      "gemini-resp",
		"object":  "chat.completion",
		"created": time.Now().Unix(),
		"choices": []map[string]interface{}{
			{
				"index": 0,
				"message": map[string]string{
					"role":    "assistant",
					"content": text,
				},
				"finish_reason": "stop",
			},
		},
	}
	return json.Marshal(output)
}

func transformToGemini(body []byte) ([]byte, error) {
	var input struct {
		Messages []struct {
			Role    string `json:"role"`
			Content string `json:"content"`
		} `json:"messages"`
	}
	if err := json.Unmarshal(body, &input); err != nil {
		return nil, err
	}

	type GeminiPart struct {
		Text string `json:"text"`
	}
	type GeminiContent struct {
		Role  string       `json:"role"`
		Parts []GeminiPart `json:"parts"`
	}

	contents := make([]GeminiContent, 0)
	for _, m := range input.Messages {
		role := m.Role
		if role == "assistant" { role = "model" }
		contents = append(contents, GeminiContent{
			Role:  role,
			Parts: []GeminiPart{{Text: m.Content}},
		})
	}

	output := map[string]interface{}{
		"contents": contents,
	}
	return json.Marshal(output)
}
