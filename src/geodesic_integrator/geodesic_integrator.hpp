// Blacklight geodesic integrator header

#ifndef GEODESIC_INTEGRATOR_H_
#define GEODESIC_INTEGRATOR_H_

// C++ headers
#include <string>  // string

// Blacklight headers
#include "../blacklight.hpp"                 // enums
#include "../input_reader/input_reader.hpp"  // InputReader
#include "../utils/array.hpp"                // Array

// Forward declarations
struct RadiationIntegrator;

//--------------------------------------------------------------------------------------------------

// Geodesic integrator
struct GeodesicIntegrator
{
  // Constructors and destructor
  GeodesicIntegrator(const InputReader *p_input_reader);
  GeodesicIntegrator(const GeodesicIntegrator &source) = delete;
  GeodesicIntegrator &operator=(const GeodesicIntegrator &source) = delete;
  ~GeodesicIntegrator();

  // Input data - general
  ModelType model_type;

  // Input data - checkpoints
  bool checkpoint_geodesic_save;
  bool checkpoint_geodesic_load;
  std::string checkpoint_geodesic_file;

  // Input data - camera parameters
  Camera camera_type;
  double camera_r;
  double camera_th;
  double camera_ph;
  double camera_urn;
  double camera_uthn;
  double camera_uphn;
  double camera_k_r;
  double camera_k_th;
  double camera_k_ph;
  double camera_rotation;
  double camera_width;
  int camera_resolution;
  bool camera_pole;

  // Input data - ray-tracing parameters
  bool ray_flat;
  RayTerminate ray_terminate;
  double ray_factor;
  double ray_step;
  int ray_max_steps;
  int ray_max_retries;
  double ray_tol_abs;
  double ray_tol_rel;
  double ray_err_factor;
  double ray_min_factor;
  double ray_max_factor;

  // Input data - image parameters
  double image_frequency;
  FrequencyNormalization image_normalization;

  // Input data - adaptive parameters
  int adaptive_max_level;
  int adaptive_block_size;

  // Geometry data
  double bh_m;
  double bh_a;
  double r_terminate;

  // Camera data
  int camera_num_pix;
  double momentum_factor;
  double cam_x[4];
  double u_con[4], u_cov[4];
  double norm_con[4], norm_con_c[4];
  double hor_con_c[4];
  double vert_con_c[4];
  Array<int> *camera_loc = nullptr;
  Array<double> *camera_pos = nullptr;
  Array<double> *camera_dir = nullptr;

  // Geodesic data
  int *geodesic_num_steps = nullptr;
  Array<double> geodesic_pos;
  Array<double> geodesic_dir;
  Array<double> geodesic_len;
  Array<bool> *sample_flags = nullptr;
  Array<int> *sample_num = nullptr;
  Array<double> *sample_pos = nullptr;
  Array<double> *sample_dir = nullptr;
  Array<double> *sample_len = nullptr;

  // Adaptive data
  int adaptive_level;
  int linear_root_blocks;
  int block_num_pix;
  int *block_counts;
  Array<bool> *refinement_flags;

  // External functions
  double Integrate();
  double AddGeodesics(const RadiationIntegrator *p_radiation_integrator);

  // Internal functions - geodesic_checkpoint.cpp
  void SaveGeodesics();
  void LoadGeodesics();

  // Internal functions - camera.cpp
  void InitializeCamera();
  void AugmentCamera();
  void SetPixelPlane(double u_ind, double v_ind, int ind, Array<double> &position,
      Array<double> &direction);
  void SetPixelPinhole(double u_ind, double v_ind, int ind, Array<double> &position,
      Array<double> &direction);

  // Internal functions - geodesics.cpp
  void InitializeGeodesics();
  void IntegrateGeodesics();
  void ReverseGeodesics();
  void GeodesicSubstep(double y[9], double k[9], Array<double> &gcov, Array<double> &gcon,
      Array<double> &dgcon);

  // Internal functions - geodesic_geometry.cpp
  double RadialGeodesicCoordinate(double x, double y, double z);
  void CovariantGeodesicMetric(double x, double y, double z, Array<double> &gcov);
  void ContravariantGeodesicMetric(double x, double y, double z, Array<double> &gcon);
  void ContravariantGeodesicMetricDerivative(double x, double y, double z, Array<double> &dgcon);
};

#endif
