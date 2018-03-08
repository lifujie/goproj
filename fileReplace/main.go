package main

import (
	"strings"
	"log"
	"os"
	"bufio"
)

func replaceDefaultToDevID(path string) {
	f, err := os.OpenFile(path, os.O_RDWR, 0)
	if err != nil {
		log.Printf("preload file mpd is not exist\n")
	}

	br := bufio.NewReader(f)
	var fileBuff = make([]byte, 32*1024) //需要改成可配置的
	//for {
		nread, _ := br.Read(fileBuff)
		if nread > 0{
			mpdCont := string(fileBuff[:nread])
			mpdCont1 := strings.Replace(mpdCont, "default", "devID", -1)
			log.Printf(mpdCont1)
			log.Printf("len %v\n", len(mpdCont))
			f.Truncate(int64(len(mpdCont1) - 10))
			f.WriteAt([]byte(mpdCont1), 0)
		}
		//log.Printf(string(fileBuff[:nread]))
	//}

}

func main(){
	replaceDefaultToDevID("aa.mpd")
}
