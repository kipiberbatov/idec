DEMO_ARRAY :=\
  demo/array/int_array_0_sorted.txt\
  demo/array/int_array_0_curly.txt\
  demo/array/jagged4_0_curly.txt\
  demo/array/jagged4_1_curly.txt\
  demo/array/cartesian_product_3_2_3.txt\
  demo/array/combination_6_3.txt\

.PHONY: demo_array
demo_array: bin_array $(DEMO_ARRAY)

demo/array/int_array_0_sorted.txt:\
	  bin/array_indexed_merge_sort$(.EXE)\
	  demo/array/int_array_0.txt
	$< < $(word 2, $^) > $@

demo/array/int_array_0_curly.txt:\
	  bin/jagged1$(.EXE)\
	  demo/array/int_array_0.txt
	$< < $(word 2, $^) > $@

demo/array/jagged4_0_curly.txt:\
	  bin/jagged4$(.EXE)\
	  demo/array/jagged4_0.txt
	$< < $(word 2, $^) > $@

demo/array/jagged4_1_curly.txt:\
	  bin/jagged4$(.EXE)\
	  demo/array/jagged4_1.txt
	$< < $(word 2, $^) > $@

demo/array/cartesian_product_3_2_3.txt:\
	  bin/int_array_cartesian_product$(.EXE)
	$< 3 2 3 > $@

demo/array/combination_6_3.txt:\
	  bin/int_array_combination$(.EXE)
	$< 6 3 > $@

.PHONY: demo_array_clean
demo_array_clean:
	-$(RM) $(DEMO_ARRAY)
