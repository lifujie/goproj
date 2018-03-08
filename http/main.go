package main

import (
	"encoding/json"
	"log"
	"net/http"
)

type profileResult struct {
	Rtmp  string `json:"rtmp"`
	Url   string `json:"url"`
	AppId string `json:"appId"`
	Token string `json:"token"`
}
type profile struct {
	Status string        `json:"status"`
	Result profileResult `json:"result"`
}

func main() {
	http.HandleFunc("/", handleRtmpAllocate)
	log.Fatal(http.ListenAndServe(":3000", nil))
}

type DevidSt struct {
	Devid string `json:"devid"`
}

const serUrl string = "p2p.tuyacn.com"

func handleRtmpAllocate(w http.ResponseWriter, r *http.Request) {
	pro := profile{Status: "ok",
		Result: profileResult{Rtmp: "rtmp://" + serUrl + ":9090/dash/",
			Url:   "http://" + serUrl + ":9090/dash/" + ".mpd",
			AppId: "1234567890",
			Token: "0987654321"}}
	log.Printf("pro %v\n", pro)
	js, err := json.Marshal(pro)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	log.Printf("%v\n", string(js))
	w.Header().Set("Content-Type", "application/json")
	w.Write(js)
}
