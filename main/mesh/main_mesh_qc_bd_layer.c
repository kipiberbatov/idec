#include "mesh_qc.h"

void mesh_qc_bd_layer_0_1_nodes_file_print_raw(FILE * out, const mesh * m)
{
  jagged1 * m_bd_layer_0_hyperfaces;
  jagged1 * m_bd_layer_0_cells;
  jagged1 * m_bd_layer_0_1_nodes;
  
  m_bd_layer_0_hyperfaces = mesh_qc_bd_layer_0_hyperfaces(m);
  /* NULL pointer check */
  // jagged1_file_print_raw(out, m_bd_layer_0_hyperfaces);
  
  m_bd_layer_0_cells = mesh_qc_bd_layer_0_cells(m, m_bd_layer_0_hyperfaces);
  /* NULL pointer check */
  // jagged1_file_print_raw(out, m_bd_layer_0_cells);
  
  m_bd_layer_0_1_nodes = mesh_qc_bd_layer_0_1_nodes(m, m_bd_layer_0_cells);
  /* NULL pointer check */
  jagged1_file_print(out, m_bd_layer_0_1_nodes, "--raw");
  /* successful writing check */
  
  jagged1_free(m_bd_layer_0_1_nodes);
  jagged1_free(m_bd_layer_0_cells);
  jagged1_free(m_bd_layer_0_hyperfaces);
}

int main()
{
  mesh * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  /* NULL pointer and successful scanning check */
  m->fc = mesh_fc(m);
  /* NULL pointer and successful scanning check */
  mesh_qc_bd_layer_0_1_nodes_file_print_raw(out, m);
  /* successful writing check */
  mesh_free(m);
  return 0;
}
