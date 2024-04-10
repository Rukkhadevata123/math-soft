package main

import (
	"flag"
	"fmt"
	"log"
	"time"
)

func main() {
	// Define command line arguments
	size := flag.Int("size", 160, "The number of rows and columns in the matrix")
	density := flag.Float64("density", 0.1, "The density of the matrix (percentage of non-zero elements)")
	isSparse := flag.Bool("sparse", true, "Whether the matrix is sparse")
	blockSize := flag.Int("blockSize", 16, "The block size for block multiplication")

	// Parse command line arguments
	flag.Parse()

	// Check if size is divisible by blockSize
	if *size%*blockSize != 0 {
		log.Fatal("Size must be divisible by blockSize")
	}

	// Initialize two sparse matrices
	m1 := NewMatrix(*size, *size, *density, *isSparse)
	m2 := NewMatrix(*size, *size, *density, *isSparse)

	// Convert the dense matrices to CSR matrices
	csrM1 := NewCSRMatrix(m1)
	csrM2 := NewCSRMatrix(m2)

	// Standard multiplication
	start := time.Now()
	m1.StandardMultiply(m2)
	fmt.Printf("Standard multiplication took %v\n", time.Since(start))

	// Block multiplication
	start = time.Now()
	m1.BlockMultiply(m2, *blockSize)
	fmt.Printf("Block multiplication took %v\n", time.Since(start))

	// Sparse multiplication
	start = time.Now()
	csrM1.SparseMultiply(csrM2)
	fmt.Printf("Sparse multiplication took %v\n", time.Since(start))
}
