package main

import (
	"encoding/json"
	"log"
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

type DevidSt struct {
	Devid string `json:"devid"`
}

const serUrl string = "p2p.tuyacn.com"

func main() {
	pro := profile{Status: "ok",
		Result: profileResult{Rtmp:"rtmp://" + serUrl + ":9090/dash/",
			Url:"http://" + serUrl + ":9090/dash/" + ".mpd",
			AppId:"1234567890",
			Token:"0987654321"}}
	log.Printf("pro %v\n", pro)
	js, err := json.Marshal(pro)
	if err != nil {
		return
	}
	var proAfter profile
	err = json.Unmarshal(js, &proAfter)
	log.Printf("%v\n", string(js))
	log.Printf("%v\n", proAfter)
}
