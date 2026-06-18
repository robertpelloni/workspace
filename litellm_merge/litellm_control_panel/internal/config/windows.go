//go:build windows
package config

import (
	"fmt"
	"os"

	"golang.org/x/sys/windows/registry"
)

func SetStartWithWindows(enabled bool) error {
	key, err := registry.OpenKey(registry.CURRENT_USER, `Software\Microsoft\Windows\CurrentVersion\Run`, registry.SET_VALUE)
	if err != nil {
		return fmt.Errorf("failed to open registry key: %v", err)
	}
	defer key.Close()

	if enabled {
		exePath, err := os.Executable()
		if err != nil {
			return err
		}
		return key.SetStringValue("LiteLLMControlPanel", exePath)
	} else {
		return key.DeleteValue("LiteLLMControlPanel")
	}
}

func IsStartWithWindowsEnabled() bool {
	key, err := registry.OpenKey(registry.CURRENT_USER, `Software\Microsoft\Windows\CurrentVersion\Run`, registry.QUERY_VALUE)
	if err != nil {
		return false
	}
	defer key.Close()

	_, _, err = key.GetStringValue("LiteLLMControlPanel")
	return err == nil
}
