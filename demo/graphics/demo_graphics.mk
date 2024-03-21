DEMO_GRAPHICS := \
  demo/graphics/fill.pdf \
  demo/graphics/fill_gtk.log \
  demo/graphics/mesh_brick_2d_2_forman_diffusion_gtk.log \
  demo/graphics/mesh_brick_2d_2_forman_diffusion.pdf \
  demo/graphics/mesh_brick_2d_5_forman_diffusion_gtk.log \
  demo/graphics/mesh_brick_2d_5_forman_diffusion.pdf

.PHONY: demo_graphics
demo_graphics: bin_graphics $(DEMO_GRAPHICS)

demo/graphics/fill_gtk.log: bin/gtk_fill 
	$<
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/fill.pdf: bin/pdf_fill 
	$< 100 $@

demo/graphics/mesh_brick_2d_2_forman_diffusion_gtk.log: bin/gtk_diffusion \
	  demo/mesh/mesh_brick_2d_2_forman.txt \
	  demo/mesh/mesh_brick_2d_2_forman_spacetime_pde_2.txt
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/mesh_brick_2d_2_forman_diffusion.pdf: bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_2_forman.txt \
	  demo/mesh/mesh_brick_2d_2_forman_spacetime_pde_2.txt
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) $@

demo/graphics/mesh_brick_2d_5_forman_diffusion_gtk.log: bin/gtk_diffusion \
	  demo/mesh/mesh_brick_2d_5_forman.txt \
	  demo/mesh/mesh_brick_2d_5_forman_spacetime_pde_2.txt
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/mesh_brick_2d_5_forman_diffusion.pdf: bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_5_forman.txt \
	  demo/mesh/mesh_brick_2d_5_forman_spacetime_pde_2.txt
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

.PHONY: demo_graphics_clean
demo_graphics_clean:
	-$(RM) $(DEMO_GRAPHICS)
