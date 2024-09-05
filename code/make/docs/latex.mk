.PHONY: docs
docs: build/docs/main.pdf

build/docs: | build
	mkdir -p $@

LATEX_COMPILER := TEXINPUTS=./code/latex/src: pdflatex -halt-on-error

build/docs/main.pdf: code/latex/main.tex $(shell find code/latex -name "*.tex")\
  | build/docs
	$(LATEX_COMPILER) -output-directory=$| $<
	$(LATEX_COMPILER) -output-directory=$| $<

.PHONY: docs_fast
docs_fast: code/latex/main.tex $(shell find code/latex -name "*.tex")\
  | build/docs
	$(LATEX_COMPILER) -output-directory=$| $<

.PHONY: docs_clean
docs_clean:
	-$(RM) -r build/docs
