package main

import (
	"flag"
	"fmt"
	"math/big"
)

var arr []*big.Float

func init() {
	arr = make([]*big.Float, 0, 1000)
	arr = append(arr, big.NewFloat(2).SetPrec(1000).Sqrt(big.NewFloat(2).SetPrec(1000)))
	for i := 1; i < 1000; i++ {
		arr = append(arr, big.NewFloat(2).SetPrec(1000).Add(big.NewFloat(2).SetPrec(1000), arr[i-1]).Sqrt(big.NewFloat(2).SetPrec(1000).Add(big.NewFloat(2).SetPrec(1000), arr[i-1])))
	}
}

func main() {
	iterations := flag.Int("iterations", 1000, "Number of iterations, less than 1000")
	flag.Parse()
	if *iterations > 1000 {
		fmt.Println("Number of iterations must be less than 1000")
		return
	}
	result := big.NewFloat(1.0).SetPrec(1000)
	for i := 0; i < *iterations; i++ {
		result.Mul(result, big.NewFloat(2).SetPrec(1000).Quo(big.NewFloat(2).SetPrec(1000), arr[i]))
	}
	fmt.Println(big.NewFloat(2).SetPrec(1000).Mul(big.NewFloat(2).SetPrec(1000), result))
}
