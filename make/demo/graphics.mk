DEMO_GTK :=\
  demo/graphics/log/fill_gtk.log\
  demo/graphics/log/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature_gtk.log\

DEMO_PDF :=\
  demo/graphics/pdf/fill.pdf\
  demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.pdf\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.pdf\

DEMO_GRAPHICS := $(DEMO_GTK) $(DEMO_PDF)

.PHONY: demo_graphics
demo_graphics: bin_graphics $(DEMO_GRAPHICS) | demo/graphics

demo/graphics: | demo
	mkdir -p $@

.PHONY: demo_gtk
demo_gtk: bin_graphics $(DEMO_GTK) | demo/graphics/log

demo/graphics/log: | demo/graphics
	mkdir -p $@

demo/graphics/log/fill_gtk.log: bin/gtk_fill | demo/graphics/log
	$<
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/log/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature_gtk.log:\
	  bin/gtk_diffusion\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature_gtk.log:\
	  bin/gtk_diffusion\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature_gtk.log:\
	  bin/gtk_diffusion\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/log/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature_gtk.log:\
	  bin/gtk_diffusion\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

.PHONY: demo_pdf
demo_pdf: bin_graphics $(DEMO_PDF) | demo/graphics/pdf

demo/graphics/pdf: | demo/graphics
	mkdir -p $@

demo/graphics/pdf/fill.pdf: bin/pdf_fill | demo/graphics/pdf
	$< 100 $@

demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.pdf:\
	  bin/pdf_mesh_2d_colored_one_cochain_sequence\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.pdf:\
	  bin/pdf_diffusion\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.pdf:\
	  bin/pdf_diffusion\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.pdf:\
	  bin/pdf_mesh_2d_colored_one_cochain_sequence\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@


.PHONY: demo_graphics_clean
demo_graphics_clean:
	-$(RM) $(DEMO_GRAPHICS)
	-$(RM) -r demo/graphics/pdf
	-$(RM) -r demo/graphics/log
	-$(RM) -r demo/graphics
