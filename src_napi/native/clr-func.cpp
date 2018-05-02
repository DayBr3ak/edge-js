#include "napi_edge.h"
#using <System.Core.dll>
#using <System.dll>

#define R_OK 0
#define R_FAIL 1
#define THROW_EXCEPTION(x) {}

static System::Reflection::MethodInfo^ Compile(System::String^% code, array<System::String^>^ additionalReferences) {
  System::CodeDom::Compiler::CompilerParameters^ CompilerParams
    = gcnew System::CodeDom::Compiler::CompilerParameters();
  System::String^ outputDirectory = System::IO::Directory::GetCurrentDirectory();

  CompilerParams->GenerateInMemory = true;
  CompilerParams->TreatWarningsAsErrors = false;
  CompilerParams->GenerateExecutable = false;
  CompilerParams->CompilerOptions = "/optimize";

  CompilerParams->ReferencedAssemblies->Add("System.dll");
  if (additionalReferences != nullptr) {
    CompilerParams->ReferencedAssemblies->AddRange(additionalReferences);
  }

  Microsoft::CSharp::CSharpCodeProvider^ provider = gcnew Microsoft::CSharp::CSharpCodeProvider();
  System::CodeDom::Compiler::CompilerResults^ compile = provider->CompileAssemblyFromSource(CompilerParams, code);

  if (compile->Errors->HasErrors) {
    System::Console::WriteLine("HasErrors");
    THROW_EXCEPTION("Compile Errors");
    return nullptr;
  }
  // {
  //     string text = "Compile error: ";
  //     foreach (CompilerError ce in compile.Errors)
  //     {
  //         text += "rn" + ce.ToString();
  //     }
  //     throw new Exception(text);
  // }

  // //ExpoloreAssembly(compile.CompiledAssembly);

  System::Reflection::Module^ module = compile->CompiledAssembly->GetModules()[0];
  System::Type^ mt = nullptr;
  System::Reflection::MethodInfo^ methInfo = nullptr;

  if (module != nullptr) {
    mt = module->GetType("EdgeJS.StartUp");
  }

  if (mt != nullptr) {
    methInfo = mt->GetMethod("Invoke");
  }

  return methInfo;
}

static void Run(System::Reflection::MethodInfo^ methInfo) {
  if (methInfo != nullptr) {
    System::Console::WriteLine(methInfo->Invoke(nullptr, nullptr));
  }
}

// static void CompileAndRun(System::String^% code) {
//   Run(Compile(code));
// }

int CoreClrInit(char* source, size_t sourceLen) {
  DBG("CoreClrInit()");
  DBG("Got source: %s", source);

  System::String^ typeName = "StartUp";
  System::String^ methodName = "Invoke";

  System::String^ mSource = gcnew System::String(
            source, 0, sourceLen, System::Text::Encoding::UTF8);

  System::Console::WriteLine("typeName " + typeName);
  System::Console::WriteLine("mSource " + mSource);

  array<System::String^>^ references = { "System.Windows.Forms.dll" };
  Run(Compile(mSource, references));
  return R_OK;
}
