#include <stdio.h>

void mesh_file_scan_tess_check_preamble(FILE * in, int * error);

int mesh_file_scan_tess_get_dimension(FILE * in, int * error);

void mesh_file_scan_tess_check_text_for_cell(FILE * in, int * error);

int mesh_file_scan_tess_get_number_of_maximal_cells(FILE * in, int * error);

void mesh_file_scan_tess_check_text_for_id(FILE * in, int * error);

void mesh_file_scan_tess_get_id(int * c, FILE * in, int * error, int cn_d);

void mesh_file_scan_tess_check_text_for_crysym(FILE * in, int * error);

void mesh_file_scan_tess_skip_seed(FILE * in, int * error, int cn_d,
  const int * c);

void mesh_file_scan_tess_check_text_for_ori(FILE * in, int * error);

void mesh_file_scan_tess_skip_ori(FILE * in, int * error, int cn_d);

void mesh_file_scan_tess_check_text_for_vertex(FILE * in, int * error);

void mesh_file_scan_tess_get_coordinates(double * coordinates, FILE * in,
  int * error, int d, int cn_0);

void mesh_file_scan_tess_check_text_for_edge(FILE * in, int * error);

void mesh_file_scan_tess_get_edges_to_nodes(int * edges_to_nodes, FILE * in,
  int * error, int cn_1);

void mesh_file_scan_tess_check_text_for_face(FILE * in, int * error);

void mesh_file_scan_tess_get_faces_number_of_sides(
  double * faces_number_of_sides, FILE * in, int * error, int cn_2);

void mesh_file_scan_tess_faces_to_subfaces(int * faces_to_subfaces, FILE * in,
  int * error);
