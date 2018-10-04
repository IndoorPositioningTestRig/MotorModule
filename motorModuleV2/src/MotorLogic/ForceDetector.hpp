#ifndef FORCE_DETECTOR_HPP
#define FORCE_DETECTOR_HPP

namespace MotorLogic
{
class ForceDetector
{
public:
  ForceDetector() = default;
  void init();
  static void triggerMax();
  static void triggerMin();
  static bool max;
  static bool min;

private:
};
} // namespace MotorLogic

#endif // FORCE_DETECTOR_HPP