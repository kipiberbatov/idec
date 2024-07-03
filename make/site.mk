.PHONY: site
site: website/index.html website/style.css website/main.pdf

website/index.html: html/index.html | website
	cp $< $|

website/style.css: css/style.css | website
	cp $< $|

website/main.pdf: docs/main.pdf | website
	cp $< $|

website:
	mkdir -p $@

.PHONY: site_fast
site_fast: website/index.html website/style.css docs_all_fast | website
	cp docs/main.pdf $|

.PHONY: site_clean
site_clean:
	-$(RM) -r website
