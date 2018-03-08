package main

import (
	"fmt"
	"log"
	"os"
	"runtime/pprof"
)

func fib() int {
	a, b := 0, 1
	for i := 0; i < 2000; i++ {
		a, b = b, a+b
	}
	return a
}

func main() {
	f, err := os.Create("test.pprof")
	if err != nil {
		log.Fatal(err)
	}
	pprof.StartCPUProfile(f)
	defer pprof.StopCPUProfile()
	fmt.Println("vim-go")
	for i := 0; i < 2000; i++ {
		fib()
	}
}
