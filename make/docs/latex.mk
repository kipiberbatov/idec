.PHONY: docs_all
docs_all: docs/main.pdf

docs:
	mkdir -p $@

docs/main.pdf: latex/main.tex | docs
	pdflatex -output-directory=$| $<
	pdflatex -output-directory=$| $<

.PHONY: docs_all_fast
docs_all_fast: latex/main.tex | docs
	pdflatex -output-directory=$| $<

.PHONY: docs_clean
docs_clean:
	rm -r docs
