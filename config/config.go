package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"time"
)

/*
{
	"rtmp": {
		"ip": "127.0.0.1",
		"httpPort": "8080",
		"rtmpPort": "1936",
	}
	"proxy": {
		"httpPort": "9999"
		"rtmpPort": "1935"
	}
}
*/
type RtmpServer struct {
	Ip       string `json:"ip"`
	HttpPort string `json:"httpPort"`
	RtmpPort string `json:"rtmpPort"`
}

type ProxyServer struct {
	HttpPort string `json:"httpPort"`
	RtmpPort string `json:"rtmpPort"`
	Domain   string `json:"domain"`
	DashLoc  string `json:"dashlocation"`
	HlsLoc   string `json:"hlslocation"`
}

type Preload struct {
	Name     string `json:"name"`
	Path     string `json:"path"`
	DashPath string `json:"dashpath"`
}

type LifeCycle struct {
	Camera string `json:"camera"`
}

type ProxyCfg struct {
	RtmpServer RtmpServer  `json:"rtmp"`
	Proxy      ProxyServer `json:"proxy"`
	Pload      Preload     `json:"preload"`
	Lc         LifeCycle   `json:"lifecycle"`
}

var Proxy ProxyCfg

func LoadConfig(configfilename string) error {
	log.Printf("starting load configure file(%s)......", configfilename)
	data, err := ioutil.ReadFile(configfilename)
	if err != nil {
		log.Printf("ReadFile %s error:%v", configfilename, err)
		return err
	}
	log.Printf("loadconfig: \r\n%s", string(data))

	err = json.Unmarshal(data, &Proxy)
	if err != nil {
		log.Printf("json.Unmarshal error:%v", err)
		return err
	}
	log.Printf("get config json data:%v", Proxy)
	return nil
}

type PtrAA struct {
	aa *int
	bb int64
	cc int64
	//cc1 int64
	dd string
}

func main() {
	pa := &PtrAA{}
	LoadConfig("./proxy.conf")
	Duration, _ := time.ParseDuration(Proxy.Lc.Camera)
	log.Printf("duration: %v, %v\n", Duration, pa)
}
