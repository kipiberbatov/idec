.PHONY: docs docs_fast docs_clean

build/docs: | build
	mkdir -p $@

LATEX_COMPILER := TEXINPUTS=./code/latex/src: pdflatex -halt-on-error

docs: build/docs/main.pdf

build/.demo_pdf: $(_demo_pdf)
	touch $@

build/docs/main.pdf: code/latex/main.tex $(shell find code/latex -name "*.tex")\
  build/.demo_pdf | build/docs
	$(LATEX_COMPILER) -output-directory=$| $<
	$(LATEX_COMPILER) -output-directory=$| $<
	touch build/.docs_fast

docs_fast: build/.docs_fast

build/.docs_fast: code/latex/main.tex $(shell find code/latex -name "*.tex")\
  build/.demo_pdf | build/docs
	$(LATEX_COMPILER) -output-directory=$| $<
	touch $@

docs_clean:
	-$(RM) -r build/docs
	-$(RM) build/.docs_fast
