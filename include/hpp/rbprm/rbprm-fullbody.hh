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

#ifndef HPP_RBPRM_FULLBODY_HH
# define HPP_RBPRM_FULLBODY_HH

#include <hpp/rbprm/config.hh>
#include <hpp/rbprm/rbprm-state.hh>
#include <hpp/model/device.hh>
#include <hpp/rbprm/rbprm-limb.hh>
#include  <hpp/core/collision-validation.hh>

#include "hpp/rbprm/stop-watch.hh"

#include  <vector>

namespace timer
{
struct timing
{
    timing(Stopwatch& stopwath)
        : tim(stopwath){}

    Stopwatch& tim;
    std::vector<long double> timePerCall;
    void Stat()
    {
        tim.stop("global");
        worst = std::numeric_limits<long double>::min();
        bst = std::numeric_limits<long double>::max();
        long double total(0);
        for(std::vector<long double>::const_iterator cit = timePerCall.begin();
            cit != timePerCall.end(); ++cit)
        {
            total += *cit;
            if(worst < *cit) worst = *cit;
            if(bst > *cit) bst = *cit;
        }
        avg = total / (long double)(timePerCall.size());
        tim.report("global");
        std::cout << "computation time " << tim.get_total_time("global") << std::endl;
        std::cout << "percentage time " << 100 * total / tim.get_total_time("global") << "%" << std::endl;
        std::cout << "nbstates " << timePerCall.size() << std::endl;
        std::cout << "avg time " << avg << std::endl;
        std::cout << "bst time " << bst  << std::endl;
        std::cout << "worst time " << worst << std::endl;
    }
    long double worst;
    long double bst;
    long double avg;
};

timing& GetTiming();

}

namespace hpp {
  namespace rbprm {
    HPP_PREDEF_CLASS(RbPrmFullBody);

    /// Dual representation of a robot for Reachability Based planning:
    /// Collision free part of the robot vs Range Of Motion of the limbs.
    ///
    class RbPrmFullBody;
    typedef boost::shared_ptr <RbPrmFullBody> RbPrmFullBodyPtr_t;

    class HPP_RBPRM_DLLAPI RbPrmFullBody
    {
    public:
        static RbPrmFullBodyPtr_t create (const model::DevicePtr_t& device);

    public:
        virtual ~RbPrmFullBody();

    public:
        /// Creates a Limb for the robot,
        /// identified by its name. Stores a sample
        /// container, used for requests
        void AddLimb(const std::string& id, const std::string& name, const std::string& effectorName, const fcl::Vec3f &offset,
                     const fcl::Vec3f &normal,const double x, const double y,
                     const model::ObjectVector_t &collisionObjects,
                     const std::size_t nbSamples, const double resolution);

    public:
        typedef std::map<std::string, std::vector<std::string> > T_LimbGroup;

    public:
        const rbprm::T_Limb& GetLimbs() {return limbs_;}
        const T_LimbGroup& GetGroups() {return limbGroups_;}
        const model::DevicePtr_t device_;

    public:
        void SetRefConfiguration(model::ConfigurationIn_t config)
        {
            refConfig_ = config;
        }

    private:
        core::CollisionValidationPtr_t collisionValidation_;
        std::map<std::string, core::CollisionValidationPtr_t> limbcollisionValidations_;
        rbprm::T_Limb limbs_;
        T_LimbGroup limbGroups_;

    public:
        model::Configuration_t refConfig_;

    protected:
      RbPrmFullBody (const model::DevicePtr_t &device);

      ///
      /// \brief Initialization.
      ///
      void init (const RbPrmFullBodyWkPtr_t& weakPtr);

    private:
      RbPrmFullBodyWkPtr_t weakPtr_;
      friend hpp::rbprm::State HPP_RBPRM_DLLAPI ComputeContacts(const hpp::rbprm::RbPrmFullBodyPtr_t& body, model::ConfigurationIn_t configuration,
                                        const model::ObjectVector_t& collisionObjects, const fcl::Vec3f& direction);

      friend hpp::rbprm::State HPP_RBPRM_DLLAPI ComputeContacts(const hpp::rbprm::State& previous, const hpp::rbprm::RbPrmFullBodyPtr_t& body, model::ConfigurationIn_t configuration,
                                        const model::ObjectVector_t& collisionObjects, const fcl::Vec3f& direction, bool& contactMaintained, bool& multipleBreaks, const bool allowFailure);
    }; // class RbPrmDevice

    hpp::rbprm::State HPP_RBPRM_DLLAPI ComputeContacts(const hpp::rbprm::RbPrmFullBodyPtr_t& body, model::ConfigurationIn_t configuration,
                                      const model::ObjectVector_t& collisionObjects, const fcl::Vec3f& direction);

    hpp::rbprm::State HPP_RBPRM_DLLAPI ComputeContacts(const hpp::rbprm::State& previous, const hpp::rbprm::RbPrmFullBodyPtr_t& body, model::ConfigurationIn_t configuration,
                                            const model::ObjectVector_t& collisionObjects, const fcl::Vec3f& direction, bool& contactMaintained, bool& multipleBreaks, const bool allowFailure);
  } // namespace rbprm

} // namespace hpp

#endif // HPP_RBPRM_DEVICE_HH
