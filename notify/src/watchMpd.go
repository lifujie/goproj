package main

import(
	"github.com/howeyc/fsnotify"
	"log"
)

func main(){
	mon, err := fsnotify.NewWatcher()
	if err != nil{
		return
	}
	mon.Watch("/tmp/dash/test.mpd")
	go func(){
		for{
			select{
			case w := <-mon.Event:
				log.Printf("get a event")
				if w.IsModify(){
					log.Printf("file is modify\n")
				}
			}
		}
	}()

	
	select{}
}