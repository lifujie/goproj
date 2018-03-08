package main

import (
	"fmt"
	"time"
)

func main() {
	now := time.Now()
	time.Sleep(10 * time.Second)
	fmt.Println(int64(time.Now().Sub(now)) / 1000000000)
}
