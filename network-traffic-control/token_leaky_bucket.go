package main

import(
	"fmt"
	"time"
)

var(
	rateLimiter float64 //产生token的速率
	storedPermits float64 //过去多久没有使用token
	waitTime float64  //下个请求的等待时间
	slope float64 
)

func doSetRate()

func main(){
}