.PHONY: website
website: build/website/index.html build/website/style.css build/website/main.pdf

build/website/index.html: code/html/index.html | build/website
	cp $< $|

build/website/style.css: code/css/style.css | build/website
	cp $< $|

build/website/main.pdf: build/docs/main.pdf | build/website
	cp $< $|

build/website: | build
	mkdir -p $@

.PHONY: website_fast
website_fast: docs_fast build/website/index.html build/website/style.css\
  | build/docs build/website
	cp $(word 1, $|)/main.pdf $(word 2, $|)

.PHONY: site_clean
website_clean:
	-$(RM) -r build/website
