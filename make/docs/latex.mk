.PHONY: docs_all
docs_all: docs/main.pdf

docs:
	mkdir -p $@

docs/main.pdf: latex/main.tex | docs
	pdflatex -output-directory=docs $<

.PHONY: docs_clean
docs_clean:
	rm -r docs
