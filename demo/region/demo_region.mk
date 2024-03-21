DEMO_REGION :=\
  demo/region/simplex_2d_0_measure_and_centroid.txt\
  demo/region/quasi_cube_2d_0_measure_and_centroid.txt\

.PHONY: demo_region
demo_region: bin_region $(DEMO_REGION)

demo/region/simplex_2d_0_measure_and_centroid.txt:\
	  bin/simplex$(.EXE)\
	  demo/region/simplex_2d_0.txt
	$< < $(word 2, $^) > $@

demo/region/quasi_cube_2d_0_measure_and_centroid.txt:\
	  bin/quasi_cube$(.EXE)\
	  demo/region/quasi_cube_2d_0.txt
	$< < $(word 2, $^) > $@

.PHONY: demo_region_clean
demo_region_clean:
	-$(RM) $(DEMO_REGION)
