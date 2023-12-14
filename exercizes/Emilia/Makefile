ARGS=-I/usr/lib/llvm-15/include -std=c++17 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS

.PHONY: clean all

all: emilia

emilia: bin/driver.o bin/parser.o bin/scanner.o bin/emilia.o bin/ifExprAST.o bin/seqAST.o bin/functionAST.o bin/prototypeAST.o bin/exprAST.o bin/numberExprAST.o bin/variableExprAST.o bin/binaryExprAST.o bin/unaryExprAST.o bin/callExprAST.o bin/varExprAST.o bin/whileExprAST.o bin/forExprAST.o bin/arrayAssignExprAST.o bin/arrayExprAST.o
	clang++ -o emilia bin/driver.o bin/parser.o bin/scanner.o bin/emilia.o bin/ifExprAST.o bin/seqAST.o bin/functionAST.o bin/exprAST.o bin/numberExprAST.o bin/prototypeAST.o bin/variableExprAST.o bin/binaryExprAST.o bin/unaryExprAST.o bin/callExprAST.o bin/varExprAST.o bin/whileExprAST.o bin/forExprAST.o bin/arrayAssignExprAST.o bin/arrayExprAST.o `llvm-config --cxxflags --ldflags --libs --libfiles --system-libs` 

bin/emilia.o: src/emilia.cpp src/driver.hpp src/AST/Utils/LogError.hpp
	clang++ -o bin/emilia.o -c src/emilia.cpp $(ARGS)
	
bin/parser.o: src/parser.cpp
	clang++ -o bin/parser.o -c src/parser.cpp $(ARGS)
	
bin/scanner.o: src/scanner.cpp src/parser.hpp
	clang++ -o bin/scanner.o -c src/scanner.cpp  $(ARGS) 
	
bin/driver.o: src/driver.cpp src/parser.hpp src/driver.hpp
	clang++ -o bin/driver.o -c src/driver.cpp $(ARGS) 

bin/ifExprAST.o: src/AST/IfExprAST.cpp src/AST/IfExprAST.hpp 
	clang++ -o bin/ifExprAST.o -c src/AST/IfExprAST.cpp  $(ARGS) 
	
bin/seqAST.o: src/AST/SeqAST.cpp src/AST/SeqAST.hpp 
	clang++ -o bin/seqAST.o -c src/AST/SeqAST.cpp  $(ARGS) 
	
bin/prototypeAST.o: src/AST/PrototypeAST.cpp src/AST/PrototypeAST.hpp 
	clang++ -o bin/prototypeAST.o -c src/AST/PrototypeAST.cpp  $(ARGS) 

bin/functionAST.o: src/AST/FunctionAST.cpp src/AST/FunctionAST.hpp 
	clang++ -o bin/functionAST.o -c src/AST/FunctionAST.cpp  $(ARGS) 
	
bin/exprAST.o: src/AST/ExprAST.cpp src/AST/ExprAST.hpp 
	clang++ -o bin/exprAST.o -c src/AST/ExprAST.cpp  $(ARGS) 
	
bin/numberExprAST.o: src/AST/NumberExprAST.cpp src/AST/NumberExprAST.hpp 
	clang++ -o bin/numberExprAST.o -c src/AST/NumberExprAST.cpp  $(ARGS) 
	
bin/variableExprAST.o: src/AST/VariableExprAST.cpp src/AST/VariableExprAST.hpp 
	clang++ -o bin/variableExprAST.o -c src/AST/VariableExprAST.cpp  $(ARGS) 
	
bin/binaryExprAST.o: src/AST/BinaryExprAST.cpp src/AST/BinaryExprAST.hpp 
	clang++ -o bin/binaryExprAST.o -c src/AST/BinaryExprAST.cpp  $(ARGS) 

bin/unaryExprAST.o: src/AST/UnaryExprAST.cpp src/AST/UnaryExprAST.hpp 
	clang++ -o bin/unaryExprAST.o  -c src/AST/UnaryExprAST.cpp  $(ARGS) 
	
bin/callExprAST.o: src/AST/CallExprAST.cpp src/AST/CallExprAST.hpp 
	clang++ -o bin/callExprAST.o -c src/AST/CallExprAST.cpp  $(ARGS) 
	
bin/forExprAST.o: src/AST/ForExprAST.cpp src/AST/ForExprAST.hpp 
	clang++ -o bin/forExprAST.o -c src/AST/ForExprAST.cpp  $(ARGS) 
	
bin/varExprAST.o: src/AST/VarExprAST.cpp src/AST/VarExprAST.hpp 
	clang++ -o bin/varExprAST.o -c src/AST/VarExprAST.cpp  $(ARGS) 
	
bin/whileExprAST.o: src/AST/WhileExprAST.cpp src/AST/WhileExprAST.hpp 
	clang++ -o bin/whileExprAST.o -c src/AST/WhileExprAST.cpp  $(ARGS) 
	
bin/arrayExprAST.o: src/AST/ArrayExprAST.cpp src/AST/ArrayExprAST.hpp 
	clang++ -o bin/arrayExprAST.o -c src/AST/ArrayExprAST.cpp  $(ARGS) 
	
bin/arrayAssignExprAST.o: src/AST/ArrayAssignExprAST.cpp src/AST/ArrayAssignExprAST.hpp 
	clang++ -o bin/arrayAssignExprAST.o -c src/AST/ArrayAssignExprAST.cpp  $(ARGS) 
	
src/parser.cpp, src/parser.hpp: src/parser.yy 
	bison -o src/parser.cpp src/parser.yy -Wcounterexamples

src/scanner.cpp: src/scanner.ll
	flex -o src/scanner.cpp src/scanner.ll

clean:
	rm -f bin/*.o* src/parser.cpp src/scanner.cpp src/parser.hpp -f
	rm -f emilia run run.o
