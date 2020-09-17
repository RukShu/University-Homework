using System;
 
class MainClass {

  public static void Main (string[] args) {
    Func<int> F = BuildCounter();
    for(int i = 0; i < 1000; i++){
      Console.WriteLine(F());
    }
  }
 
 
  static Func<int> BuildCounter(){
    int i = 1;
 
    return () => ++i;
  }
}