package main

import (
	"flag"
	"fmt"
	"math/big"
)

func main() {
	iterations := flag.Int("iterations", 10000000, "Number of iterations")
	flag.Parse()
	pi := new(big.Float).SetFloat64(4.0 / 3.0)
	for i := 2; i < *iterations; i++ {
		mul := new(big.Float).SetFloat64(4.0 * float64(i*i))
		div := new(big.Float).SetFloat64((2*float64(i) + 1) * (2*float64(i) - 1))
		pi.Mul(pi, mul)
		pi.Quo(pi, div)
	}
	pi.Mul(pi, new(big.Float).SetFloat64(2))
	fmt.Println(pi)
}
