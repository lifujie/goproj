package main

import "fmt"

type foo struct{}

func (foo) f() {
	fmt.Println("foo")
}
func main() {
	interface{ f() }.f(foo{})
}
