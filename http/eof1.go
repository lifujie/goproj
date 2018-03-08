package main

import (
	"fmt"
	"net"
	"os"
)

func die(msg string, s interface{}) {
	fmt.Printf("%s crashed: %v\n", msg, s)
	os.Exit(1)
}

func main() {
	fd, err := net.Dial("tcp", "baidu.com:80")
	if err != nil {
		die("dial", err)
	}

	req := []byte("GET /intl/en/privacy/ HTTP/1.0\r\nHost: www.baidu.com\r\n\r\n")
	_, err = fd.Write(req)
	if err != nil {
		die("dial write", err)
	}

	buf := make([]byte, 20)
	var nr int = 1
	for nr > 0 {
		nr, err = fd.Read(buf)
		if err != nil {
			die("dial read", err)
		}
		fmt.Printf("read %d\n", nr)
	}
}
