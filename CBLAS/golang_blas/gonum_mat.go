package main

import (
	"fmt"

	"gonum.org/v1/gonum/mat"
)

func Gonum_mat() {
	// Initialize two matrices.
	a := mat.NewDense(2, 2, []float64{4, 0, 0, 4})
	b := mat.NewDense(2, 2, []float64{1, 2, 3, 4})

	// Create a new dense matrix for the result.
	r := mat.NewDense(2, 2, nil)

	// Perform matrix multiplication.
	r.Mul(a, b)

	// Print the result.
	fa := mat.Formatted(r, mat.Prefix("    "), mat.Squeeze())
	fmt.Printf("r = %v\n", fa)
}
