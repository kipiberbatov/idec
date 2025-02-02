txt_array :=\
  build/$(MODE)/txt/array/int_array_0_sorted.txt\
  build/$(MODE)/txt/array/int_array_0_curly.txt\
  build/$(MODE)/txt/array/jagged4_0_curly.txt\
  build/$(MODE)/txt/array/jagged4_1_curly.txt\
  build/$(MODE)/txt/array/cartesian_product_3_2_3.txt\
  build/$(MODE)/txt/array/combination_6_3.txt\

.PHONY: txt_array
txt_array: bin_array $(txt_array) | build/$(MODE)/txt/array

build/$(MODE)/txt/array: | build/$(MODE)/txt
	mkdir -p $@

build/$(MODE)/txt/array/int_array_0_sorted.txt:\
  build/$(MODE)/bin/array_indexed_merge_sort$(.EXE)\
  data/array/int_array_0.txt | build/$(MODE)/txt/array
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/array/int_array_0_curly.txt:\
  build/$(MODE)/bin/jagged1$(.EXE)\
  data/array/int_array_0.txt | build/$(MODE)/txt/array
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/array/jagged4_0_curly.txt:\
  build/$(MODE)/bin/jagged4$(.EXE)\
  data/array/jagged4_0.txt | build/$(MODE)/txt/array
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/array/jagged4_1_curly.txt:\
  build/$(MODE)/bin/jagged4$(.EXE)\
  data/array/jagged4_1.txt | build/$(MODE)/txt/array
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/array/cartesian_product_3_2_3.txt:\
  build/$(MODE)/bin/int_array_cartesian_product$(.EXE)\
  | build/$(MODE)/txt/array
	$< 3 2 3 > $@

build/$(MODE)/txt/array/combination_6_3.txt:\
  build/$(MODE)/bin/int_array_combination$(.EXE)\
  | build/$(MODE)/txt/array
	$< 6 3 > $@

.PHONY: txt_array_clean
txt_array_clean:
	-$(RM) $(txt_array)
	-$(RM) -r build/$(MODE)/txt/array
