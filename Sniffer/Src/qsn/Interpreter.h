#pragma once
namespace qsn
{
   class Interpreter
   {
      Interpreter() = default;

   public:
      static Interpreter& getInstance()
      {
         static Interpreter logger;
         return logger;
      }

      Interpreter(const Interpreter&) = delete;
      Interpreter& operator= (const Interpreter&) = delete;

      
   };
}

