DEMO_REGION :=\
  build/$(MODE)/demo/region/simplex_2d_0_measure_and_centroid.txt\
  build/$(MODE)/demo/region/quasi_cube_2d_0_measure_and_centroid.txt\

.PHONY: demo_region
demo_region: bin_region $(DEMO_REGION) | build/$(MODE)/demo/region

build/$(MODE)/demo/region: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/region/simplex_2d_0_measure_and_centroid.txt:\
  build/$(MODE)/bin/simplex$(.EXE)\
  data/region/simplex_2d_0.txt | build/$(MODE)/demo/region
	$< < $(word 2, $^) > $@

build/$(MODE)/demo/region/quasi_cube_2d_0_measure_and_centroid.txt:\
  build/$(MODE)/bin/quasi_cube$(.EXE)\
  data/region/quasi_cube_2d_0.txt | build/$(MODE)/demo/region
	$< < $(word 2, $^) > $@

.PHONY: demo_region_clean
demo_region_clean:
	-$(RM) $(DEMO_REGION)
	-$(RM) -r build/$(MODE)/demo/region
