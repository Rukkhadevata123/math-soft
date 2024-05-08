.PHONY: all clean

all: report.pdf

report.pdf: report.tex references.bib
	xelatex report.tex
	bibtex report
	xelatex report.tex
	xelatex report.tex

clean:
	rm -f *.aux *.bbl *.blg *.log *.out *.pdf
