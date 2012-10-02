#include <igloo/igloo.h>
using namespace igloo;

#include <fstream>
using namespace std;

namespace igloo {

  class ProgressTestListener : public TestListener
  {
    public:
      virtual void TestRunStarting() {}
      virtual void TestRunEnded(const TestResults& results) 
      {
        std::cout << std::endl;
        std::cout << "Run " << results.NumberOfTestsRun() << " tests" << std::endl;
        if (results.FailedTests().size() > 0) {
          std::cout << results.NumberOfFailedTests() << " failed tests:" << std::endl;
          for (TestResults::FailedTestsType::const_iterator it = results.FailedTests().begin();
                                                                it != results.FailedTests().end();
                                                                it++)
          {
            const FailedTestResult& result = *it;
            std::cout << std::endl;
            std::cout << result.GetContextName() << result.GetSpecName() << std::endl;
            std::cout << result.GetErrorMessage();
          }
        }
      }

      virtual void ContextRunStarting(const ContextBase& ) {}
      virtual void ContextRunEnded(const ContextBase& ) {}
      virtual void SpecRunStarting(const ContextBase& , const std::string& ) {}
      virtual void SpecSucceeded(const ContextBase&, const std::string& )
      {
        std::cout << ".";
      }

      virtual void SpecFailed(const ContextBase& , const std::string& )
      {
        std::cout << "F";
      }
  };

}


const char* results_filename = "build/tests.xml";

int main()
{
  fstream file(results_filename, fstream::out);

  XUnitResultsOutput output(file);
  TestRunner runner(output);

  ProgressTestListener listener;
  runner.AddListener(&listener);

  return runner.Run();
}
