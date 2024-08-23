.PHONY: docs
docs: build/docs/main.pdf

build/docs: | build
	mkdir -p $@

build/docs/main.pdf: code/latex/main.tex | build/docs
	pdflatex -halt-on-error -output-directory=$| $<
	pdflatex -halt-on-error -output-directory=$| $<

.PHONY: docs_fast
docs_fast: code/latex/main.tex | build/docs
	pdflatex -output-directory=$| $<

.PHONY: docs_clean
docs_clean:
	-$(RM) -r build/docs
