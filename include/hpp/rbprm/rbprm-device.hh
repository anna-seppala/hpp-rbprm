//
// Copyright (c) 2014 CNRS
// Authors: Steve Tonneau (steve.tonneau@laas.fr)
//
// This file is part of hpp-rbprm.
// hpp-rbprm is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-rbprm is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-core  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef HPP_RBPRM_DEVICE_HH
# define HPP_RBPRM_DEVICE_HH

# include <hpp/rbprm/config.hh>
# include <hpp/model/device.hh>

namespace hpp {

  namespace model {
    /// Dual representation of a robot for Reachability Based planning:
    /// Collision free part of the robot vs Range Of Motion of the limbs.
    ///
    struct RbPrmDevice;
    typedef boost::shared_ptr <RbPrmDevice> RbPrmDevicePtr_t;

    struct HPP_RBPRM_DLLAPI RbPrmDevice
    {
    public:
        static RbPrmDevicePtr_t create (const DevicePtr_t& robotTrunk, const DevicePtr_t& robotRom);

    public:
        /// Get current configuration
        const Configuration_t& currentConfiguration () const;

        /// Set current configuration
        /// \return True if the current configuration was modified and false if
        ///         the current configuration did not change.
        bool currentConfiguration (ConfigurationIn_t configuration);

    public:
      /// Collision free part of the dual representation
      const DevicePtr_t robotTrunk_;
      /// Range Of Motion of the robot
      const DevicePtr_t robotRom_;

    protected:
      RbPrmDevice (const DevicePtr_t& robotTrunk, const DevicePtr_t& robotRom);
    }; // class ConfigValidation
  } // namespace rbprm
} // namespace hpp

#endif // HPP_RBPRM_DEVICE_HH