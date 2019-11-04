#include <stdio.h>
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"


constexpr char kInputStream[] = "input_float";
constexpr char kOutputStream[] = "output_float";


std::string slurp_file(const char *fname) {
  FILE* f = fopen(fname, "r");
  if (f) {
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    char* s = new char[size];
    rewind(f);
    fread(s, sizeof(char), size, f);
    std::string str(s);
    return str;
  } else {
    puts("FAIL!!!");
    exit(0);
  }
}

::mediapipe::Status run_graph() {

  size_t timestamp = 0;

  std::string calculator_graph_config_contents = slurp_file("toy/graphs/square.pbtxt");

  mediapipe::CalculatorGraphConfig config =
    mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
        calculator_graph_config_contents);

  std::cout << calculator_graph_config_contents << std::endl;

  mediapipe::CalculatorGraph graph;
  MP_RETURN_IF_ERROR(graph.Initialize(config));
  puts("kuku");


  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
      graph.AddOutputStreamPoller(kOutputStream));
  MP_RETURN_IF_ERROR(graph.StartRun({}));


  MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
        kInputStream, mediapipe::MakePacket<double>(3.0)
        .At(mediapipe::Timestamp(timestamp++))));

  mediapipe::Packet packet;
  auto& output = packet.Get<double>();

  std::cout << output;

  return ::mediapipe::OkStatus();
}


int main(int argc, char **argv) {
  run_graph();
  return 0;
}
