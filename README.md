# A trivial example of MediaPipe usage

This is a sandbox for experimenting with MediaPipe.

The first goal is to implement a calculator squaring a number and a graph whose
only node is this calculator.  At the moment it compiles successfully, but
there seems to be some problem with a graph: the `ASSIGN_OR_RETURN` macro in
VerifyCalculatorWithContract silently fails.

We use the Bazel build tool as does MediaPipe itself.  To do so, we set up a
Basel workspace by copying MediaPipe’s WORKSPACE file to our root directory. Of
course, in our toy example we won’t need all the packages mentioned there, but
figuring out a minimal subset is not worth the effort.

Likewise, for simplicity, we copy the entire `mediapipe/mediapipe` and
`mediapipe/third_party` directories to our workspace.

