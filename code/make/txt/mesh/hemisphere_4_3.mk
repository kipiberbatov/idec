.PHONY: txt_mesh_hemisphere_4_3 txt_mesh_hemisphere_4_3_clean

_txt_mesh_hemisphere_4_3 :=\
  build/$(MODE)/txt/mesh/hemisphere_4_3.txt\

build/$(MODE)/txt/mesh/hemisphere_4_3.txt:\
  build/$(MODE)/bin/mesh_hemisphere$(.EXE) | build/$(MODE)/txt/mesh
	$< 4 3 > $@

txt_mesh_hemisphere_4_3: $(_txt_mesh_hemisphere_4_3)

txt_mesh_hemisphere_4_3_clean:
	-$(RM) $(_txt_mesh_hemisphere_4_3)
