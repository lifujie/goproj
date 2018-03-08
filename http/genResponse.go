package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"strings"
)

type stream struct {
	Url        string `json:"playableUrl"`
	DevID      string `json:"deviceName"`
	StreamType string `json:"streamType"`
}

func generResponse(url, streamType string) []byte {
	serUrl := strings.Split(url, "/")
	st := stream{
		Url: "http://" + configure.Proxy.Proxy.Domain + ":" +
		configure.Proxy.Proxy.HttpPort + "/" + serUrl[2] +
			"/" + serUrl[3],
		DevID:      serUrl[3],
		StreamType: streamType,
	}
	js, err := json.Marshal(st)
	if err != nil {
		return nil
	}
	t := &http.Response{
		Status:        "200 OK",
		StatusCode:    200,
		Proto:         "HTTP/1.1",
		ProtoMajor:    1,
		ProtoMinor:    1,
		Body:          ioutil.NopCloser(bytes.NewBuffer(js)),
		ContentLength: int64(len(js)),
		Header:        make(http.Header, 5),
	}
	t.Header.Set("Content-Type", "application/json")
	buff := bytes.NewBuffer(nil)
	t.Write(buff)
	w := buff.Bytes()
	return w
}

func main() {
	w := generResponse("/which/dash/camera6cb13dc3d91bbbfe23d2kt1.mpd", "dash")
	fmt.Printf("%v\n", string(w))
}
