package main

import (
	"bytes"
	"fmt"
	"io"
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

	buf := make([]byte, 24)
	var nr int64 = 1
	var buff *bytes.Buffer = bytes.NewBuffer(buf)
	for nr > 0 {
		nr, err = io.Copy(buff, fd)
		bufff := buff.Bytes()
		if err != nil {
			die("dial read", err)
		}
		fmt.Printf("read %d\n", len(bufff))
	}
}
