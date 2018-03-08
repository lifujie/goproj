package main

import (
	"fmt"
	"os/exec"
)

func main() {
	ls := exec.Command("ls", "./")
	out, _ := ls.Output()
	fmt.Println(string(out))
}
