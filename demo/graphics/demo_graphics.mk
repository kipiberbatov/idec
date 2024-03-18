.PHONY: demo_graphics
demo_graphics: bin demo_gtk

DEMO_GTK := \
  demo/graphics/gtk_fill.log \
  demo/graphics/gtk_spacetime_pde.log \
  demo/graphics/diffusion.pdf

.PHONY: demo_gtk
demo_gtk: $(DEMO_GTK)

demo/graphics/gtk_fill.log: bin/gtk_fill 
	$<
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/gtk_spacetime_pde.log: bin/gtk_spacetime_pde \
	  demo/mesh/mesh_brick_2d_2_forman.txt \
	  demo/mesh/mesh_brick_2d_2_forman_spacetime_pde_2.txt
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/diffusion.pdf: bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_2_forman.txt \
	  demo/mesh/mesh_brick_2d_2_forman_spacetime_pde_2.txt
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) $@
