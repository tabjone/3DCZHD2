void initialize_hydrostatic_equilibrium(
    double ***rho, double ***P, double ***ux, double ***uy, double ***uz, double ***S, double *g, double *z,
    int nz, int ny, int nx)
{
    double M_sun = 1.989 * 1e30;
    double R_sun = 6.58926e+10; //IS THIS CORRECT?

    double G = 6.6743 * 1e-11; // Gravitational constant
    double k_B = 1.380649 * 1e-23; // Boltzmann constant

    for (int i = 0; i < nz; i++)
    {
        z[i] = i;
        g[i] = i;
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nx; k++)
            {
                rho[i][j][k] = i;
                P[i][j][k] = i;
                ux[i][j][k] = i;
                uy[i][j][k] = i;
                uz[i][j][k] = i;
                S[i][j][k] = i;
            }
        }
    }
}