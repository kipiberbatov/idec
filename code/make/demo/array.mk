DEMO_ARRAY :=\
  build/$(BUILD_TYPE)/demo/array/int_array_0_sorted.txt\
  build/$(BUILD_TYPE)/demo/array/int_array_0_curly.txt\
  build/$(BUILD_TYPE)/demo/array/jagged4_0_curly.txt\
  build/$(BUILD_TYPE)/demo/array/jagged4_1_curly.txt\
  build/$(BUILD_TYPE)/demo/array/cartesian_product_3_2_3.txt\
  build/$(BUILD_TYPE)/demo/array/combination_6_3.txt\

.PHONY: demo_array
demo_array: bin_array $(DEMO_ARRAY) | build/$(BUILD_TYPE)/demo/array

build/$(BUILD_TYPE)/demo/array: | build/$(BUILD_TYPE)/demo
	mkdir -p $@

build/$(BUILD_TYPE)/demo/array/int_array_0_sorted.txt:\
  build/$(BUILD_TYPE)/bin/array_indexed_merge_sort$(.EXE)\
  data/array/int_array_0.txt | build/$(BUILD_TYPE)/demo/array
	$< < $(word 2, $^) > $@

build/$(BUILD_TYPE)/demo/array/int_array_0_curly.txt:\
  build/$(BUILD_TYPE)/bin/jagged1$(.EXE)\
  data/array/int_array_0.txt | build/$(BUILD_TYPE)/demo/array
	$< < $(word 2, $^) > $@

build/$(BUILD_TYPE)/demo/array/jagged4_0_curly.txt:\
  build/$(BUILD_TYPE)/bin/jagged4$(.EXE)\
  data/array/jagged4_0.txt | build/$(BUILD_TYPE)/demo/array
	$< < $(word 2, $^) > $@

build/$(BUILD_TYPE)/demo/array/jagged4_1_curly.txt:\
  build/$(BUILD_TYPE)/bin/jagged4$(.EXE)\
  data/array/jagged4_1.txt | build/$(BUILD_TYPE)/demo/array
	$< < $(word 2, $^) > $@

build/$(BUILD_TYPE)/demo/array/cartesian_product_3_2_3.txt:\
  build/$(BUILD_TYPE)/bin/int_array_cartesian_product$(.EXE)\
  | build/$(BUILD_TYPE)/demo/array
	$< 3 2 3 > $@

build/$(BUILD_TYPE)/demo/array/combination_6_3.txt:\
  build/$(BUILD_TYPE)/bin/int_array_combination$(.EXE)\
  | build/$(BUILD_TYPE)/demo/array
	$< 6 3 > $@

.PHONY: demo_array_clean
demo_array_clean:
	-$(RM) $(DEMO_ARRAY)
	-$(RM) -r build/$(BUILD_TYPE)/demo/array
