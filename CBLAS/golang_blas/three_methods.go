package main

import (
	"math/rand"
	"time"

	"gonum.org/v1/gonum/mat"
)

type Matrix struct {
	Rows, Cols int
	Data       [][]float64
}

type CSRMatrix struct {
	Rows, Cols int
	RowPtr     []int
	ColIdx     []int
	Data       []float64
}

// NewMatrix initializes a matrix with the given dimensions and density.
// If isSparse is true, it initializes a sparse matrix, otherwise it initializes a dense matrix.
func NewMatrix(rows, cols int, density float64, isSparse bool) *Matrix {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	data := make([][]float64, rows)
	for i := range data {
		data[i] = make([]float64, cols)
		for j := range data[i] {
			if isSparse {
				if r.Float64() < density {
					data[i][j] = float64(r.Intn(100) + 1) // generate a positive integer
				}
			} else {
				if r.Float64() >= density {
					data[i][j] = float64(r.Intn(100) + 1) // generate a positive integer
				}
			}
		}
	}
	return &Matrix{Rows: rows, Cols: cols, Data: data}
}

// Multiply multiplies the matrix with another matrix.
// StandardMultiply multiplies the matrix with another matrix using the standard method.
func (m *Matrix) StandardMultiply(n *Matrix) *Matrix {
	if m.Cols != n.Rows {
		panic("the number of columns of the first matrix must be equal to the number of rows of the second matrix")
	}

	result := NewMatrix(m.Rows, n.Cols, 0, false)
	for i := 0; i < m.Rows; i++ {
		for j := 0; j < n.Cols; j++ {
			for k := 0; k < m.Cols; k++ {
				result.Data[i][j] += m.Data[i][k] * n.Data[k][j]
			}
		}
	}

	return result
}

// BlockMultiply multiplies the matrix with another matrix using the block method.
// blockSize is the size of the blocks.
func (m *Matrix) BlockMultiply(n *Matrix, blockSize int) *Matrix {
	if m.Cols != n.Rows {
		panic("the number of columns of the first matrix must be equal to the number of rows of the second matrix")
	}

	result := NewMatrix(m.Rows, n.Cols, 0, false)
	for ii := 0; ii < m.Rows; ii += blockSize {
		for jj := 0; jj < n.Cols; jj += blockSize {
			for kk := 0; kk < m.Cols; kk += blockSize {
				for i := ii; i < min(ii+blockSize, m.Rows); i++ {
					for j := jj; j < min(jj+blockSize, n.Cols); j++ {
						for k := kk; k < min(kk+blockSize, m.Cols); k++ {
							result.Data[i][j] += m.Data[i][k] * n.Data[k][j]
						}
					}
				}
			}
		}
	}

	return result
}

// min returns the smaller of two integers.
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// NewCSRMatrix initializes a CSR matrix from a dense matrix.
func NewCSRMatrix(m *Matrix) *CSRMatrix {
	rowPtr := make([]int, m.Rows+1)
	colIdx := make([]int, 0)
	data := make([]float64, 0)

	for i := range m.Data {
		rowPtr[i] = len(data)
		for j, val := range m.Data[i] {
			if val != 0 {
				colIdx = append(colIdx, j)
				data = append(data, val)
			}
		}
	}
	rowPtr[m.Rows] = len(data)

	return &CSRMatrix{Rows: m.Rows, Cols: m.Cols, RowPtr: rowPtr, ColIdx: colIdx, Data: data}
}

// NewCSRMatrixFromDense initializes a CSR matrix from a gonum/mat.Dense matrix.
func NewCSRMatrixFromDense(m *mat.Dense) *CSRMatrix {
	rows, cols := m.Dims()
	rowPtr := make([]int, rows+1)
	colIdx := make([]int, 0)
	data := make([]float64, 0)

	for i := 0; i < rows; i++ {
		rowPtr[i] = len(data)
		for j := 0; j < cols; j++ {
			val := m.At(i, j)
			if val != 0 {
				colIdx = append(colIdx, j)
				data = append(data, val)
			}
		}
	}
	rowPtr[rows] = len(data)

	return &CSRMatrix{Rows: rows, Cols: cols, RowPtr: rowPtr, ColIdx: colIdx, Data: data}
}

// SparseMultiply multiplies the CSR matrix with another CSR matrix.
func (m *CSRMatrix) SparseMultiply(n *CSRMatrix) *CSRMatrix {
	if m.Cols != n.Rows {
		panic("the number of columns of the first matrix must be equal to the number of rows of the second matrix")
	}

	rowPtr := make([]int, m.Rows+1)
	colIdx := make([]int, 0)
	data := make([]float64, 0)

	for i := 0; i < m.Rows; i++ {
		rowPtr[i] = len(data)
		row := make(map[int]float64)
		for j := m.RowPtr[i]; j < m.RowPtr[i+1]; j++ {
			for k := n.RowPtr[m.ColIdx[j]]; k < n.RowPtr[m.ColIdx[j]+1]; k++ {
				row[n.ColIdx[k]] += m.Data[j] * n.Data[k]
			}
		}
		for j, val := range row {
			colIdx = append(colIdx, j)
			data = append(data, val)
		}
	}
	rowPtr[m.Rows] = len(data)

	return &CSRMatrix{Rows: m.Rows, Cols: n.Cols, RowPtr: rowPtr, ColIdx: colIdx, Data: data}
}
