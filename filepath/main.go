package main

import(
	"os"
	"path/filepath"
	//"fmt"
	"log"
	"strings"
	"os/exec"
)

const dir string = "/Users/l00277880/selfcode/go/goproj/filepath/aa"
const dst string = "/Users/l00277880/selfcode/go/goproj/filepath/bb/"

func main(){
	paths := make([]string, 0)
    filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
        if !info.IsDir() {
            paths = append(paths, path)
        }
        return nil
    })

    // 遍历文件路径，修改文件名
    /*for _, path := range paths {
		_,  file := filepath.Split(path)
		//fmt.Printf("%v ,%v\n",dir,file)
		afterReplace := strings.Replace(file, "default", "deviceid", -1)
		//fmt.Printf("%v\n", afterReplace)
		newPath := dst+afterReplace
        os.Rename(path, newPath)
	}*/
	
	bash, err := exec.LookPath("cp")
	if err != nil{
		log.Printf("please install bash \n")
	}
	log.Printf("%v\n", bash)
	for _, path := range paths {
		_,  file := filepath.Split(path)
		//fmt.Printf("%v ,%v\n",dir,file)
		afterReplace := strings.Replace(file, "default", "deviceid", -1)
		//fmt.Printf("%v\n", afterReplace)
		newPath := dst+afterReplace
		log.Printf("%v, %v", path, newPath)
		cmd := exec.Command(bash, path, newPath)
		cmd.Run()
	}
}