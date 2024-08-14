DEMO_REGION :=\
  build/$(BUILD_MODE)/demo/region/simplex_2d_0_measure_and_centroid.txt\
  build/$(BUILD_MODE)/demo/region/quasi_cube_2d_0_measure_and_centroid.txt\

.PHONY: demo_region
demo_region: bin_region $(DEMO_REGION) | build/$(BUILD_MODE)/demo/region

build/$(BUILD_MODE)/demo/region: | build/$(BUILD_MODE)/demo
	mkdir -p $@

build/$(BUILD_MODE)/demo/region/simplex_2d_0_measure_and_centroid.txt:\
  build/$(BUILD_MODE)/bin/simplex$(.EXE)\
  data/region/simplex_2d_0.txt | build/$(BUILD_MODE)/demo/region
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/region/quasi_cube_2d_0_measure_and_centroid.txt:\
  build/$(BUILD_MODE)/bin/quasi_cube$(.EXE)\
  data/region/quasi_cube_2d_0.txt | build/$(BUILD_MODE)/demo/region
	$< < $(word 2, $^) > $@

.PHONY: demo_region_clean
demo_region_clean:
	-$(RM) $(DEMO_REGION)
	-$(RM) -r build/$(BUILD_MODE)/demo/region
