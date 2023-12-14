#include <iostream>
#include "driver.hpp"

int main(int argc, char *argv[])
{
    int res = 0;
    driver drv;
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    auto TargetTriple = sys::getDefaultTargetTriple();
    drv.module->setTargetTriple(TargetTriple);
    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
    if (!Target)
    {
        errs() << Error;
        return 1;
    }
    auto CPU = "generic";
    auto Features = "";
    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    drv.module->setDataLayout(TheTargetMachine->createDataLayout());
    drv.module->setTargetTriple(TargetTriple);
    int i = 1;
    std::string file_name = "";
    while (i < argc)
    {
        if (argv[i] == std::string("-p"))
            drv.trace_parsing = true;
        else if (argv[i] == std::string("-s"))
            drv.trace_scanning = true;
        else if (argv[i] == std::string("-v"))
            drv.ast_print = true;
        else if (argv[i] == std::string("-o"))
            file_name = argv[++i] + (std::string) ".o";
        else if (!drv.parse(argv[i]))
        {
            drv.codegen();
            if (file_name != "")
            {
                std::error_code EC;
                raw_fd_ostream dest(file_name, EC, sys::fs::OF_None);
                if (EC)
                {
                    errs() << "Could not open file: " << EC.message();
                    return 1;
                }
                legacy::PassManager pass;
                auto FileType = CGFT_ObjectFile;
                if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
                {
                    errs() << "TheTargetMachine can't emit a file of this type";
                    return 1;
                }
                pass.run(*drv.module);
                dest.flush();
                outs() << "Wrote " << file_name << "\n";
                return 0;
            }
        }
        else
        {
            res = 1;
        }
        i++;
    };
    return res;
}
