package leaky_bucket

import(
	"fmt"
	"time"
)

var(
	rate float64
	burst float64
	refreshTime time.Time
	water float64
)

func initLeakyBucket(){
	rate = 0.5
	burst = 3.0
	refreshTime = time.Now()
	water = 0 
}

func getTimeNow() time.Time{
	return time.Now()
}

func getMax(first, second float64) float64{
	if first > second{
		return first
	} 

	return second
	
}

func refreshWater(){
	now := getTimeNow()

	water = getMax(0, water - float64(int64(now.Sub(refreshTime)) / 1000000000) * rate)
	refreshTime  = now
}

func permissionGranted() bool{
	refreshWater()
	if water < burst{
		water++
		return true
	} 
	return false
}

func main_test(){
	initLeakyBucket()
	//for{
		for i := 0; i < 10; i++{
			pg := permissionGranted()
			time.Sleep(1 * time.Second)
			if pg{
				fmt.Printf("the req %v get permission\n", i)
			} else{
				fmt.Printf("the req %v not get permission\n", i)
			}
		}
	//}
}