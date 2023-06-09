#include <stdlib.h>

void deallocate_3D_array(double ***array) 
{
  free(array[0][0]);
  free(array[0]);
  free(array);
}

void deallocate_all(
    double ***rho, double ***rho_prev, double ***P, double ***P_prev, double ***ux, double ***ux_prev,
    double ***uy, double ***uy_prev, double ***uz, double ***uz_prev, double ***S, double ***S_prev,
    double *g, double *z)
{
  deallocate_3D_array(rho);
  deallocate_3D_array(rho_prev);
  deallocate_3D_array(P);
  deallocate_3D_array(P_prev);
  deallocate_3D_array(ux);
  deallocate_3D_array(ux_prev);
  deallocate_3D_array(uy);
  deallocate_3D_array(uy_prev);
  deallocate_3D_array(uz);
  deallocate_3D_array(uz_prev);
  deallocate_3D_array(S);
  deallocate_3D_array(S_prev);
  free(g);
  free(z);
}