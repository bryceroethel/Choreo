// Copyright (c) Choreo contributors

#pragma once

#include <concepts>

#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <units/time.h>

namespace choreo {

/**
 * Enforce equality operators on trajectory sample types.
 */
template <typename T>
concept EqualityComparable = requires(const T& a, const T& b) {
  { a == b } -> std::convertible_to<bool>;
  { a != b } -> std::convertible_to<bool>;
};

/**
 * A concept representing a single robot sample in a Trajectory.
 */
template <typename T>
concept TrajectorySample =
    EqualityComparable<T> &&
    requires(T t, units::second_t time, T tother, int year) {
      { t.GetTimestamp() } -> std::same_as<units::second_t>;
      { t.GetPose() } -> std::same_as<frc::Pose2d>;
      { t.GetChassisSpeeds() } -> std::same_as<frc::ChassisSpeeds>;
      { t.OffsetBy(time) } -> std::same_as<T>;
      { t.Interpolate(tother, time) } -> std::same_as<T>;
      // FIXME: This works around a roboRIO GCC internal compiler error; it
      // can't be fully generic
      { t.template Flipped<2022>() } -> std::same_as<T>;
      { t.template Flipped<2023>() } -> std::same_as<T>;
      { t.template Flipped<2024>() } -> std::same_as<T>;
    };

}  // namespace choreo
