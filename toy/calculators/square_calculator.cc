#include "mediapipe/framework/calculator_framework.h"

namespace mediapipe {

double fsquare(double x) {
  return x * x;
}

class SquareCalculator : public CalculatorBase {
  public:
    static ::mediapipe::Status GetContract(CalculatorContract *cc);
    ::mediapipe::Status Process(CalculatorContext *cc) override;
};

REGISTER_CALCULATOR(SquareCalculator);

::mediapipe::Status SquareCalculator::GetContract (
        CalculatorContract *cc) {
  cc->Inputs().Index(0).Set<double>();
  cc->Outputs().Index(0).Set<double>();

  return ::mediapipe::OkStatus();
}

::mediapipe::Status SquareCalculator::Process(
    CalculatorContext *cc) {
  double x = cc->Inputs().Index(0).Get<double>();
  double y = fsquare(x);
  cc->Outputs().Index(0).AddPacket(MakePacket<double>(y));

  return ::mediapipe::OkStatus();
}

}
