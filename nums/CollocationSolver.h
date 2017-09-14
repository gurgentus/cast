/* author: Gurgen Hayrapetyan.
 * implementation of a collocation with quasilinearization
 * ref: U.Ascher, R. Mattheij, R. Russelll, Numerical Solution of Boundary Value Problems
 * for Ordinary Differential Equations
 * The scheme defaults to a three stage Lobatto method, but can be reset using the SetScheme
 * method.
 * See OrbitTransfer.cpp for usage example.
 */


#ifndef NUMS_COLLOCATIONSOLVER_H
#define NUMS_COLLOCATIONSOLVER_H

#include "Eigen/Dense"
#include "CollocationSolver.h"
#include "DifferentialSystem.h"
#include "FiniteDifferenceGrid.h"
#include "Node.h"

class CollocationSolver {
private:
    int num_nodes_;  // number of grid nodes
    int dim_;  // dimension of the system
    FiniteDifferenceGrid grid_;  // pointer to a grid

    DifferentialSystem* p_ode_;  // pointer to a system to solve
    Eigen::VectorXd sol_vec_; // pointer to the solution vector
    Eigen::VectorXd f_vec; // y'
    std::string filename_;  // allow the user to specify the output file or use a default name

    static constexpr double ERR_TOL = 1e-1; // error tolerance for stopping iterations
    static const int MAX_ITER = 20; // maximum number of iterations before stopping

    /* Collocation Parameters */
    int k = 3;
    Eigen::MatrixXd a = Eigen::MatrixXd(3,3);
    Eigen::VectorXd rho = Eigen::VectorXd(3);
    Eigen::VectorXd b = Eigen::VectorXd(3);

public:
    CollocationSolver(DifferentialSystem *p_ode, int num_nodes, Eigen::VectorXd& init_guess);

    /* sets the collocation scheme */
    void SetScheme(int k, Eigen::VectorXd& rho, Eigen::MatrixXd& a, Eigen::VectorXd& b);

    /* sets the filename if results should be written to a file */
    void set_filename(const std::string& name)
    {
        filename_ = name;
    }

    /* returns grid point value */
    double Step(int i);

    /* runs the solver */
    int Solve();

    /* returns the solution vector */
    Eigen::VectorXd sol_vec() const
    {
        return sol_vec_;
    }
};


#endif //NUMS_COLLOCATIONSOLVER_H
