//int mesh_file_scan_tess_ignore_begin(FILE * in);
void mesh_file_scan_tess_ignore_format(FILE * in);
int mesh_file_scan_tess_dimension(FILE * in);
int mesh_file_scan_tess_number_of_maximal_cells(FILE * in);
void mesh_file_scan_tess_ignore_ids_of_maximal_cell(FILE * in);
void mesh_file_scan_tess_ignore_crystal_type(FILE * in);
void mesh_file_scan_tess_ignore_seed(FILE * in);
void mesh_file_scan_tess_ignore_orientation(FILE * in);

int mesh_file_scan_tess_vertices_total(FILE * in);
/* allocate memory for coordinates: d * cn_0 */
void mesh_file_scan_tess_coordinates(FILE * in, double * coordinates, int cn_0);

int mesh_file_scan_tess_edges_total(FILE * in);
/* allocate memory for edges: 2 * cn_1 */
void  mesh_file_scan_tess_edges_nodes(FILE * in, int * nodes, int cn_1);

/*
Compares the initial $n characters of a string $s with the $n characters
following in a file $in.
Returns 0 if they are the same, 1 (respectively, -1), if at the first one that
they differ in has a higher (respectively, lower), -2 if EOF occurs*/
int string_compare_with_file(FILE * in, int n, const char * s)
{
  int c, i = 0;

  while (i < n)
  {
    c = fgetc(in);
    if (c == EOF)
      return -2;
    if (c < s[i])
      return -1;
    if (c > s[i])
      return 1;
    ++i;
  }
  return 0;
}

/* like fgets, but does not discriminate against newlines */
void string_file_scan(FILE * in, char * s, int n)
{
  int i = 0;
  while (i < n - 1)
  {
    c = fgetc(in);
    if (c == EOF)
    {
      s[i] = '\0';
      return;
    }
    s[i] = 'c';
    ++i;
  }
  s[n - 1] = '\0';
}

mesh * mesh_file_scan_tess(FILE * in)
{
  char buffer[80];
  char * str;
  int d, i, m_dim, n, c_i;
  double x;
  /* the following will be dynamically allocated */
  int * c = NULL, * edges_to_nodes = NULL, * cn = NULL;
  double * coordinates = NULL;
  mesh * m = NULL;
  
  /* check for "***tess\n *format\n   " */
  str = "***tess\n *format\n   ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fprintf(stderr, "Error: input file should start with\n\n%s\n\n", str);
    fprintf(stderr, "Instead, it starts with with\n\n%s\n\n", buffer);
    goto clean_on_failure;
  }
  
  /* check for format's value (2.0, 3.3, or 3.4) */
  string_file_scan(in, buffer, 4);
  if (strcmp(buffer, "2.0") && strcmp(buffer, "3.3") && strcmp(buffer, "3.4"))
  {
    errno = EINVAL;
    fputs("Error: input file should have its format '2.0' or '3.3' or '3.4'\n",
      stderr);
    fprintf(stderr, "Instead, it starts with '%s'\n", str);
    goto clean_on_failure;
  }
  
  /* check for "\n **general\n   " */
  str = "\n **general\n   ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fputs("file should have its 4-th line ' **general'\n", stderr);
    goto clean_on_failure;
  }
  
  /* find dimension d */
  string_file_scan(in, buffer, 2);
  if (!strcmp(buffer, "1"))
    d = 1;
  else if (!strcmp(buffer, "2"))
    d = 2;
  else if (!strcmp(buffer, "3"))
    d = 3;
  else
  {
    errno = EINVAL;
    fputs("cannot scan dimension: it should be 1, 2, or 3\n", stderr);
    goto clean_on_failure;
  }
  
  /* check for " standard\n **cell\n  " */
  str = " standard\n **cell\n  ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fputs("Lines 5 and 6 are not right\n", stderr);
    goto clean_on_failure;
  }
  
  /* allocate memory for mesh */
  m = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    fputs("Cannot allocate memory for mesh m\n", stderr);
    goto clean_on_failure;
  }
  m->dim = d;
  
  /* allocate memory for mesh cells number */
  cn = (int *) malloc(sizeof(int) * (d + 1));
  if (errno)
  {
    fputs("Cannot allocate memory for m->cn\n", stderr);
    goto clean_on_failure;
  }
  
  /* calculate the number of maximal cells */
  cn[d] = int_file_scan(in);
  if (errno)
  {
    fputs("Cannot scan maximal dimension\n", stderr);
    goto clean_on_failure;
  }
  if (cn[d] <= 0)
  {
    errno = EINVAL;
    fprintf(stderr,
      "Number of maximal cells is %d which is not positive", cn[d]);
    goto clean_on_failure;
  }
  
  /* check for "\n  *id\n   " */
  str = "\n  *id\n   ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fputs("8-th line of .tess file must be '  *id\n", stderr);
    goto clean_on_failure;
  }
  
  /* check for cells' IDs correctness */
  c = (int *) malloc(sizeof(int) * cn[d]);
  if (errno)
  {
    fputs("Cannot allocate memory for c\n", stderr);
    goto clean_on_failure;
  }
  for (i = 0; i < cn[d]; ++i)
  {
    c[i] = int_file_scan(in);
    if (errno)
    {
      fprintf(stderr, "Cannot scan %d-th cell id dimension\n", i + 1);
      goto clean_on_failure;
    }
  }
  
  /* check for "\n  *crysym\n   triclinic\n  *seed\n" */
  str = "\n  *crysym\n   triclinic\n  *seed\n";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fprintf(stderr, "Error: lines 10-12 must contain %s\n", str);
    goto clean_on_failure;
  }
  
  for (i = 0; i < cn[d]; ++i)
  {
    c_i = int_file_scan(in);
    if (errno)
    {
      fprintf(stderr, "Cannot scan %d-th cell id dimension\n", i);
      goto clean_on_failure;
    }
    if (c_i != c[i])
    {
      fprintf(stderr,
        "Id of cell[%d] doe not correspond with data from seed", c_i);
      goto clean_on_failure;
    }
    for (i = 0; i < 4; ++i)
    {
      x = double_file_scan(in);
      if (errno)
      {
        fprintf(stderr, "Missing value\n");
        goto clean_on_failure;
      }
    }
  }
  
  /* check for "\n  *ori\n   " */
  str = "\n  *ori\n   ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fprintf(stderr, "No *ori field.\n Instead: %s\n", str);
    goto clean_on_failure;
  }
  
  /* ignore orientation type */
  string_file_scan(in, buffer, sizeof(buffer));
  
  /* ignore orientation values */
  for (i = 0; i < cn[d]; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      x = double_file_scan(in);
      if (errno)
      {
        fprintf(stderr, "Missing value\n");
        goto clean_on_failure;
      }
    }
  }
  
  /* check for "\n **vertex\n " */
  str = "\n **vertex\n ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fprintf(stderr, "Vertex field is not presented %s\n", str);
    goto clean_on_failure;
  }
  
  /* scan cn[0] */
  cn[0] = int_file_scan(in);
  if (errno)
  {
    fputs("Cannot scan number of nodes\n", stderr);
    goto clean_on_failure;
  }
  if (cn[0] <= 0)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of vertices is %d which is not positive", cn[0]);
    goto clean_on_failure;
  }
  
  /* allocate coordinates */
  coordinates = (double *) malloc(sizeof(double) * cn[0] * d);
  if (errno)
  {
    fputs("Unable to allocate memory for coordinates\n", stderr);
    goto clean_on_failure;
  }
  
  /* scan coordinates */
  mesh_file_scan_tess_coordinates(in, coordinates, d, cn[0]);
  if (errno)
    goto clean_on_failure;
    
  // for (i = 0; i < cn[0]; ++i)
  // {
  //   c_i = int_file_scan(in);
  //   if (errno)
  //   {
  //     fprintf(stderr, "Cannot scan 0-th cell id dimension\n", i);
  //     goto clean_on_failure;
  //   }
  //   if (c_i != (i + 1))
  //   {
  //     fprintf(stderr, "Invalid vertex index\n");
  //     goto clean_on_failure;
  //   }
  //   for (j = 0; j < d; ++j)
  //   {
  //     coordinates[i * d + j] = double_file_scan(in);
  //     if (errno)
  //     {
  //       fprintf(stderr, "Unable to scan a coordinate (%d, %d)\n", i, j);
  //       goto clean_on_failure;
  //     }
  //   }
  //   for (j = d; j < 4; ++j)
  //   {
  //     x = double_file_scan(in);
  //     if (errno)
  //     {
  //       fprintf(stderr, "Missing value\n");
  //       goto clean_on_failure;
  //     }
  //   }
  // }
  
  /* check for "\n **edge\n " */
  str = "\n **edge\n ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fprintf(stderr, "Edge field is not presented %s\n", str);
    goto clean_on_failure;
  }
  
  /* scan cn[1] */
  cn[1] = int_file_scan(in);
  if (errno)
  {
    fputs("Cannot scan number of edges\n", stderr);
    goto clean_on_failure;
  }
  if (cn[1] <= 0)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of edges is %d which is not positive", cn[1]);
    goto clean_on_failure;
  }
  
  /* allocate edges_to_nodes */
  edges_to_nodes = (int * ) malloc(sizeof(int) * cn[1] * 2);
  if (errno)
  {
    fputs("Unable to allocate memory for edges_to_nodes\n", stderr);
    goto clean_on_failure;
  }
  
  mesh_file_scan_tess_edges_to_nodes(in, edges_to_nodes, cn[1]);
  if (errno)
    goto clean_on_failure;
  
  // for (i = 0; i < cn[1]; ++i)
  // {
  //   m_cn[1] = 0;
  //   m_cn[10] = 0;
  // }
  
  /* check for "\n **face\n " */
  str = "\n **face\n ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    errno = EINVAL;
    fprintf(stderr, "Face field is not presented %s\n", str);
    goto clean_on_failure;
  }
  
  cn[2] = int_file_scan(in);
  if (errno)
  {
    fputs("Cannot scan number of edges\n", stderr);
    goto clean_on_failure;
  }
  if (cn[2] <= 0)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of faces is %d which is not positive", cn[1]);
    goto clean_on_failure;
  }
  
  faces_number_of_sides = (int * ) malloc(sizeof(int) * cn[2]);
  if (errno)
  {
    fputs("Unable to allocate memory for faces_number_of_sides\n", stderr);
    goto clean_on_failure;
  }
  
  position = ftell(in);
  mesh_file_scan_tess_faces_number_of_sides(faces_number_of_sides, in, cn[2]);
  fseek(in, position, SEEK_SET);
  
  faces_total_edges = int_array_total_sum(cn[2], faces_number_of_sides);
  
  faces_to_subfaces = (int * ) malloc(sizeof(int) * 2 * faces_total_edges);
  if (errno)
  {
    fputs("Cannot allocate memory for faces_to_edges\n", stderr);
    goto clean_on_failure;
  }
  
  mesh_file_scan_tess_faces_to_subfaces(in, faces_to_subfaces);
  
  cf_0 = d;
  cf->a1 = (int * ) malloc(sizeof(int) * cf_0);
  if (errno)
  {
    perror("mesh_file_scan_cf - cannot allocate memory for m->cf->a1");
    goto clean_on_failure;
  }
  mesh_cf_a1(cf->a1, d);

  cf_a2_size = int_array_total_sum(d, cf->a1);
  cf->a2 = (int * ) malloc(sizeof(int) * cf_a2_size);
  if (errno)
  {
    perror("mesh_file_scan_cf - cannot allocate memory for m->cf->a2");
    goto clean_on_failure;
  }
  mesh_cf_a2(cf->a2, d, cf->a1);
  
  cf_a3_size = int_array_total_sum(cf_a2_size, cf->a2);
  if (errno)
  {
    perror("mesh_file_scan_cf - cannot scan m->cf->a3");
    goto clean_on_failure;
  }
  
  index = 0;
  for (i = 0; i < )
  
  cf_a4_size = int_array_total_sum(cf_a3_size, cf->a3);
  if (errno)
  {
    perror("mesh_file_scan_cf - cannot scan m->cf->a4");
    goto clean_on_failure;
  }
  cf->a4 = values;

  m->dim = d;
  m->dim_embedded = d;
  m->cn = cn;
  m->c = c;
  m->cf = cf;
  m->coord = coordinates;
  return m;
  
  /* cleaning if an error occurs */
clean_on_failure:
  free(edges_to_nodes)
  free(coordinates);
  free(c);
  free(cn);
  free(m);
  return NULL;
}

