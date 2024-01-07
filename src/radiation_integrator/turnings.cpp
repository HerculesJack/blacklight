#include "radiation_integrator.hpp"
// #include <iostream>

const int MIN_DIFF_N = 10;

void RadiationIntegrator::FindZTurnings(int m, int num_steps, int &n_start, int &z_turnings_count)
{
  double find_1, find_n;

  for (int n = num_steps - MIN_DIFF_N - 1; n >= MIN_DIFF_N; n--)
  {
    find_1 = (sample_pos[adaptive_level](m, n + 1, 3) - sample_pos[adaptive_level](m, n, 3)) *
             (sample_pos[adaptive_level](m, n, 3) - sample_pos[adaptive_level](m, n - 1, 3));
    if (find_1 < 0.)
    {
      z_turnings_count++;
      n -= MIN_DIFF_N;
    }
    else if (find_1 == 0.)
    {
      find_n = (sample_pos[adaptive_level](m, n + MIN_DIFF_N, 3) -
                sample_pos[adaptive_level](m, n, 3)) *
               (sample_pos[adaptive_level](m, n, 3) -
                sample_pos[adaptive_level](m, n - MIN_DIFF_N, 3));
      if (find_n < 0.)
      {
        z_turnings_count++;
        n -= MIN_DIFF_N;
      }
    }
    if (cut_z_turnings >= 0 && n_start < 0 && z_turnings_count == cut_z_turnings + 1)
      n_start = n;
      // std::cout << num_steps << std::endl;
  }

  image[adaptive_level](image_offset_z_turnings, m) = static_cast<double>(z_turnings_count);
}
