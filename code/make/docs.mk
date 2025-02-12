.PHONY: docs docs_fast docs_clean

build/docs: | build
	mkdir -p $@

LATEX_COMPILER := TEXINPUTS=./code/latex/src: pdflatex -halt-on-error

docs: build/docs/main.pdf

build/.pdf: $(_pdf_mesh) $(_pdf_diffusion_steady_state)\
  $(_pdf_diffusion_transient)
	echo $^ > $@

build/docs/main.pdf: code/latex/main.tex $(shell find code/latex -name "*.tex")\
  build/.pdf | build/docs
	$(LATEX_COMPILER) -output-directory=$| $<
	$(LATEX_COMPILER) -output-directory=$| $<
	touch build/.docs_fast

docs_fast: build/.docs_fast

build/.docs_fast: code/latex/main.tex $(shell find code/latex -name "*.tex")\
  build/.pdf | build/docs
	$(LATEX_COMPILER) -output-directory=$| $<
	echo $^ > $@

docs_clean:
	-$(RM) -r build/docs
	-$(RM) build/.docs_fast
