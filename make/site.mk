.PHONY: site
site: website/index.html website/style.css website/main.pdf

website/index.html: html/index.html | website
	cp $< website

website/style.css: css/style.css | website
	cp $< website

website/main.pdf: docs/main.pdf | website
	cp $< website

website:
	mkdir -p $@

.PHONY: site_clean
site_clean:
	-$(RM) -r website
