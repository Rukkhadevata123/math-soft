package main

import (
	"flag"
	"fmt"
	"math/big"
)

func main() {
	iterations := flag.Int("i", 120000, "Number of iterations")
	precision := flag.Int("p", 120000, "Precision of the calculation")
	flag.Parse()

	result := big.NewFloat(1.0).SetPrec(uint(*precision))
	sqrt := big.NewFloat(2).SetPrec(uint(*precision)).Sqrt(big.NewFloat(2).SetPrec(uint(*precision)))
	for i := 0; i < *iterations; i++ {
		result.Mul(result, big.NewFloat(2).SetPrec(uint(*precision)).Quo(big.NewFloat(2).SetPrec(uint(*precision)), sqrt))
		sqrt = big.NewFloat(2).SetPrec(uint(*precision)).Add(big.NewFloat(2).SetPrec(uint(*precision)), sqrt).Sqrt(big.NewFloat(2).SetPrec(uint(*precision)).Add(big.NewFloat(2).SetPrec(uint(*precision)), sqrt))
	}
	finalResult := big.NewFloat(2).SetPrec(uint(*precision)).Mul(big.NewFloat(2).SetPrec(uint(*precision)), result)
	fmt.Println(finalResult.Text('f', *precision))
}
