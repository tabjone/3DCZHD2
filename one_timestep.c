#include 

int periodic_boundary(int i, int limit) 
{
    /* Returns 0 if index is limit and limit if index is -1 */
    return (i + limit) % (limit);
}

double central_derivative(float left, float right, float di)
{
    /* Central derivative in di direction */
    return (right - left)/(2.0 * di);
}

void one_timestep(
    double ***rho, double ***rho_prev, double ***P, double ***P_prev, double ***ux, double ***ux_prev,
    double ***uy, double ***uy_prev, double ***uz, double ***uz_prev, double ***S, double ***S_prev,
    double dz, double dx, double dy,
    int nz, int ny, int nx)
{
    // Calculate new values for rho, P, ux, uy, uz, S
    // using the old values rho_prev, P_prev, ux_prev, uy_prev, uz_prev, S_prev
    // and the values of dt, dz, dx, dy
    // and the values of nz, ny, nx

    int j_left, j_right;
    int k_left, k_right;

    double drho_dt, drho_ux_dt, drho_uy_dt, drho_uz_dt;

    double dt = 1.0;
    for (int i=1; i<nz-1; i++)
    {
        for (int j=0; j<ny; j++)
        {
            j_left = periodic_boundary(j-1, ny);
            j_right = periodic_boundary(j+1, ny);
            for (int k=0; k<nx; k++)
            {
                k_left = periodic_boundary(k-1, nx);
                k_right = periodic_boundary(k+1, nx);

                drho_dt = - central_derivative(rho_prev[i][j][k_left]*ux_prev[i][j][k_left], rho_prev[i][j][k_right]*ux_prev[i][j][k_right], dx)
                         - central_derivative(rho_prev[i][j_left][k]*uy_prev[i][j_left][k], rho_prev[i][j_right][k]*uy_prev[i][j_right][k], dy)
                         - central_derivative(rho_prev[i-1][j][k]*uz_prev[i-1][j][k], rho_prev[i+1][j][k]*uz_prev[i+1][j][k], dz);

                rho[i][j][k] = rho_prev[i][j][k] + dt * drho_dt;

                drho_ux_dt = -(central_derivative(rho_prev[i][j][k_left]*ux_prev[i][j][k_left]*ux_prev[i][j][k_left], rho_prev[i][j][k_right]*ux_prev[i][j][k_right]*ux_prev[i][j][k_right], dx)
                             + central_derivative(rho_prev[i][j_left][k]*ux_prev[i][j_left][k]*uy_prev[i][j_left][k], rho_prev[i][j_right][k]*ux_prev[i][j_right][k]*uy_prev[i][j_right][k], dy)
                             + central_derivative(rho_prev[i-1][j][k]*ux_prev[i-1][j][k]*uz_prev[i-1][j][k], rho_prev[i+1][j][k]*ux_prev[i+1][j][k]*uz_prev[i+1][j][k], dz)) - central_derivative(P_prev[i][j][k_left], P_prev[i][j][k_right], dx);
                             
            
                drho_uy_dt = -(central_derivative(rho_prev[i][j][k_left]*uy_prev[i][j][k_left]*ux_prev[i][j][k_left], rho_prev[i][j][k_right]*uy_prev[i][j][k_right]*ux_prev[i][j][k_right], dx)
                             + central_derivative(rho_prev[i][j_left][k]*uy_prev[i][j_left][k]*uy_prev[i][j_left][k], rho_prev[i][j_right][k]*uy_prev[i][j_right][k]*uy_prev[i][j_right][k], dy)
                             + central_derivative(rho_prev[i-1][j][k]*uy_prev[i-1][j][k]*uz_prev[i-1][j][k], rho_prev[i+1][j][k]*uy_prev[i+1][j][k]*uz_prev[i+1][j][k], dz)) - central_derivative(P_prev[i][j_left][k], P_prev[i][j_right][k], dy);
                
                drho_uz_dt = -(central_derivative(rho_prev[i][j][k_left]*uz_prev[i][j][k_left]*ux_prev[i][j][k_left], rho_prev[i][j][k_right]*uz_prev[i][j][k_right]*ux_prev[i][j][k_right], dx)
                             + central_derivative(rho_prev[i][j_left][k]*uz_prev[i][j_left][k]*uy_prev[i][j_left][k], rho_prev[i][j_right][k]*uz_prev[i][j_right][k]*uy_prev[i][j_right][k], dy)
                             + central_derivative(rho_prev[i-1][j][k]*uz_prev[i-1][j][k]*uz_prev[i-1][j][k], rho_prev[i+1][j][k]*uz_prev[i+1][j][k]*uz_prev[i+1][j][k], dz)) - central_derivative(P_prev[i-1][j][k], P_prev[i+1][j][k], dz) - rho_prev[i][j][k]*g[i];

                ux[i][j][k] = ux_prev[i][j][k] + dt * drho_ux_dt;
                uy[i][j][k] = uy_prev[i][j][k] + dt * drho_uy_dt;
                uz[i][j][k] = uz_prev[i][j][k] + dt * drho_uz_dt;

                
            }
        }
    }
}