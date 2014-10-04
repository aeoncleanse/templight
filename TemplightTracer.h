
#ifndef LLVM_CLANG_TEMPLIGHT_TRACER_H
#define LLVM_CLANG_TEMPLIGHT_TRACER_H

#include "clang/Sema/TemplateInstObserver.h"

#include <memory>
#include <string>

namespace clang {


class TemplightTracer : public TemplateInstantiationObserver {
public:
  
  class TracePrinter; // forward-decl.
  
protected:
  
  void initializeImpl(const Sema &TheSema) override;
  void finalizeImpl(const Sema &TheSema) override;
  void atTemplateBeginImpl(const Sema &TheSema, const ActiveTemplateInstantiation& Inst) override;
  void atTemplateEndImpl(const Sema &TheSema, const ActiveTemplateInstantiation& Inst) override;
  
private:
  
  unsigned MemoryFlag : 1;
  unsigned SafeModeFlag : 1;
  unsigned IgnoreSystemFlag : 1;
  
  std::unique_ptr<TracePrinter> TemplateTracePrinter;
  
public:
  
  /// \brief Sets the format type of the template trace file.
  /// The argument can be xml/yaml/text
  TemplightTracer(const Sema &TheSema, 
                  std::string Output = "", 
                  const std::string& Format = "yaml",
                  bool Memory = false, 
                  bool Safemode = false,
                  bool IgnoreSystem = false);
  
  ~TemplightTracer() override;
  
  bool getMemoryFlag() const { return MemoryFlag; };
  bool getSafeModeFlag() const { return SafeModeFlag; };
  
};


}

#endif


