package main

import (
	"fmt"
	"log"
	"net/http"
	"net/http/httptest"
	"net/http/httputil"
)

const body = "Go is a general-purpose language designed with systems programming in mind."

func handler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Date", "Wed, 19 Jul 1972 19:00:00 GMT")
	fmt.Fprintln(w, body)
}

func main() {
	ts := httptest.NewServer(http.HandlerFunc(handler))
	defer ts.Close()

	resp, err := http.Get(ts.URL)
	if err != nil {
		log.Fatal(err)
	}
	defer resp.Body.Close()

	dump, err := httputil.DumpResponse(resp, true)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("%v, %q", len(body), dump)

}
