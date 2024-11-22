.PHONY: website website_fast website_clean

build/website: | build
	mkdir -p $@

website: build/website/index.html build/website/style.css build/website/main.pdf

build/website/index.html: code/html/index.html | build/website
	cp $< $|

build/website/style.css: code/css/style.css | build/website
	cp $< $|

build/website/main.pdf: build/docs/main.pdf | build/website
	cp $< $|
	touch build/.website_fast

website_fast: build/.website_fast

build/.website_fast: build/website/index.html build/website/style.css\
  | build/docs build/website build/.docs_fast
	cp $(word 1, $|)/main.pdf $(word 2, $|)
	touch $@

.PHONY: website_clean
website_clean:
	-$(RM) -r build/website
	-$(RM) build/.website_fast
