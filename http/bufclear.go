package main

import (
	"bytes"
	"log"
	"unsafe"

	_ "runtime"
)

//go:linkname memclrNoHeapPointers runtime.memclrNoHeapPointers
func memclrNoHeapPointers(p unsafe.Pointer, n uintptr)

func main() {
	buf := make([]byte, 100)
	buff := bytes.NewBuffer(buf)
	log.Printf("%v, len: %v, cap: %v\n", string(buf), len(buf), cap(buf))
	for i := 0; i < len(buf); i++ {
		buf[i] = byte(i)
	}

	log.Printf("%v\n", string(buf))
	buff.Reset()
	log.Printf("%v\n", string(buf))
	memclrNoHeapPointers(unsafe.Pointer(&buf[0]), uintptr(len(buf)+8))
	log.Printf("%v, len: %v, cap: %v\n", string(buf), len(buf), cap(buf))
}
