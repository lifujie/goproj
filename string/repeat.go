package main

import (
	"fmt"
	"strings"
)

func Decode(seg string) {
	if l := len(seg) % 4; l > 0 {
		fmt.Printf("%v\n", strings.Repeat("=", 4-l))
		seg += strings.Repeat("=", 4-l)
	}
	fmt.Printf("%v\n", seg)
}

func main() {
	Decode("vim-go.aaaaa")
}
