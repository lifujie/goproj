package main

import (
	"fmt"
	"strings"
)

func ExtStartPos(path string) (int, bool) {
	for i := len(path) - 1; i >= 0 && path[i] != '/'; i-- {
		if path[i] == '.' {
			return i, true
		}
	}
	return 0, false
}

func main() {
	pathstr := "/live/stream.m3u8"
	pathstr = strings.TrimLeft(pathstr, "/")
	index, err := ExtStartPos(pathstr)
	if err {
		key := pathstr[:index]
		fmt.Println(key)
	}
}
