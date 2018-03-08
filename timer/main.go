package main

import (
	"net"
	"time"
)

type Peer struct {
	time.Timer
	Conn   net.Conn
	Ip     string
	GetReq int
	DeviID string
}

//ip -> is get req?
var IpReq map[string]int

func main() {
	fmt.Println("vim-go")
}
