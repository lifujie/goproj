package main

import (
	"bufio"
	"bytes"
	"crypto/tls"
	"crypto/x509"
	"errors"
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"net/http/httputil"
)

func GetTCPAddr(addrStr string) *net.TCPAddr {
	addr, err := net.ResolveTCPAddr("tcp", addrStr)
	if err != nil {
		log.Fatalf("[ERROR] Addr %v", err.Error())
	}
	return addr
}

type myhandler struct{}

func (mh *myhandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	rbuf := make([]byte, 100*1024*1024)
	var nread int = 1
	server := GetTCPAddr("localhost:8081")
	ssconn, err := net.DialTCP("tcp", nil, server)
	if err != nil {
		log.Fatal("[ERROR] handleReqCamera create link %v", err.Error())
	}

	log.Printf("ssconn %v\n", ssconn)

	buf, _ := httputil.DumpRequest(r, true)
	_, err = ssconn.Write(buf)
	if err != nil {
		log.Fatal("[ERROR] trasfer to nginx")
	}
	for {
		nread, err = ssconn.Read(rbuf)
		log.Printf("%v, %v\n", nread, string(rbuf[:nread]))
		if nread > 0{
			reader := bytes.NewReader(rbuf[:nread])
			breader := bufio.NewReader(reader)
			res, _ := http.ReadResponse(breader, nil)
			responseCopy(w, res)
			break
		}
		if err != nil {
			if err != EOF {
				//log.Fatal("[ERROR] read from nginx")
				log.Printf("%v\n", err.Error())
			}
			break
		}
	}
	fmt.Println(string(buf))
}

func responseCopy(w http.ResponseWriter, res *http.Response){
	buf := make([]byte, 20 * 1024 * 1024)
	for k, v := range res.Header{
		w.Header().Set(k, v[0])
		for i := 1; i < len(v); i++{
			w.Header().Set(k, v[i])
		}
	}
	w.WriteHeader(res.StatusCode)
	n, _ := res.Body.Read(buf)
	defer res.Body.Close()
	w.Write(buf[:n])
	
}

var EOF = errors.New("EOF")

func main() {
	pool := x509.NewCertPool()
	caCertPath := "ca.crt"

	caCrt, err := ioutil.ReadFile(caCertPath)
	if err != nil {
		fmt.Println("ReadFile err:", err)
	}

	pool.AppendCertsFromPEM(caCrt)

	s := &http.Server{
		Addr:    ":8082",
		Handler: &myhandler{},
		TLSConfig: &tls.Config{
			ClientCAs:  pool,
			ClientAuth: tls.RequireAndVerifyClientCert,
		},
	}

	err = s.ListenAndServeTLS("server.crt", "server.key")
	if err != nil {
		fmt.Printf("ListenAndServeTLS err:", err)
	}
}
