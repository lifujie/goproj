package main

import (
	"fmt"
	"github.com/coreos/go-iptables/iptables"
)

func main() {
	var t *iptables.T = &iptables.T{}
	iptables.TestRules(t)
	fmt.Println("vim-go")
}
