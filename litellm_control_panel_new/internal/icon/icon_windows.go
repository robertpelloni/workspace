//go:build windows

package icon

import _ "embed"

//go:embed green.ico
var Green []byte

//go:embed gray.ico
var Gray []byte

//go:embed red.ico
var Red []byte

//go:embed yellow.ico
var Yellow []byte
