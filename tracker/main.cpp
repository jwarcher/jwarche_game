
#include "engine.h"

//ImageFactory*  ImageFactory::instance = NULL;
//RenderContext* RenderContext::instance = NULL;

int main(int, char** argv) {
   bool a = (bool)argv[1];
   std::cout << a << std::endl;
   try {
	bool KeepPlaying = true;
	while(KeepPlaying){
      Engine engine(a);
      KeepPlaying = engine.play();
	}
      //delete RenderContext::getInstance();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
