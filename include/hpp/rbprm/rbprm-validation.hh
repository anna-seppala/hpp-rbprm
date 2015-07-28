//
// Copyright (c) 2014 CNRS
// Authors: Steve Tonneau
//
// This file is part of hpp-rbprm
// hpp-rbprm is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-core is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-core  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef HPP_RBPRM_VALIDATION_HH
# define HPP_RBPRM_VALIDATION_HH

# include <hpp/core/collision-validation-report.hh>
# include <hpp/core/config-validation.hh>
# include <hpp/rbprm/rbprm-device.hh>
# include <hpp/rbprm/config.hh>

namespace hpp {
  namespace rbprm {

    class RbPrmValidation;
    typedef boost::shared_ptr <RbPrmValidation> RbPrmValidationPtr_t;

    /// \addtogroup validation
    /// \{

    /// Validate a configuration with respect to the reachability condition;
    /// a Configuration is valid if the trunk robot is collision free while
    /// the Range Of Motion of the is colliding.
    ///
    class HPP_RBPRM_DLLAPI RbPrmValidation : public core::ConfigValidation
    {
    public:
      static RbPrmValidationPtr_t create (const model::RbPrmDevicePtr_t& robot);

      /// Compute whether the configuration is valid
      ///
      /// \param config the config to check for validity,
      /// \param throwIfInValid if true throw an exception if config is invalid.
      /// \return whether the whole config is valid.
      virtual bool validate (const core::Configuration_t& config,
                 bool throwIfInValid = false);

      /// Compute whether the configuration is valid
      ///
      /// \param config the config to check for validity,
      /// \retval validationReport report on validation (used only for rom shape). This parameter will
      ///         dynamically cast into CollisionValidationReport type,
      /// \param throwIfInValid if true throw an exception if config is invalid,
      /// \return whether the whole config is valid.
      virtual bool validate (const core::Configuration_t& config,
                 core::ValidationReport& validationReport,
                 bool throwIfInValid = false);

      /// Add an obstacle
      /// \param object obstacle added
      /// Store obstacle and build a collision pair with each body of the robot.
      /// \notice This is applied for both trunk and rom shapes. This can be done for a single
      /// shape through trunkValidation_ and romValidation_ attributes.
      virtual void addObstacle (const core::CollisionObjectPtr_t& object);

      /// Remove a collision pair between a joint and an obstacle
      /// \param the joint that holds the inner objects,
      /// \param the obstacle to remove.
      /// \notice This is applied for both trunk and rom shapes. This can be done for a single
      /// shape through trunkValidation_ and romValidation_ attributes.
      virtual void removeObstacleFromJoint
    (const core::JointPtr_t& joint, const core::CollisionObjectPtr_t& obstacle);

    public:
      /// CollisionValidation for the trunk
      const core::CollisionValidationPtr_t trunkValidation_;
      /// CollisionValidation for the range of motion of the limbs
      const core::CollisionValidationPtr_t romValidation_;

    protected:
      RbPrmValidation (const model::RbPrmDevicePtr_t& robot);
    }; // class RbPrmValidation
    /// \}
  } // namespace rbprm
} // namespace hpp

#endif // HPP_RBPRM_VALIDATION_HH
