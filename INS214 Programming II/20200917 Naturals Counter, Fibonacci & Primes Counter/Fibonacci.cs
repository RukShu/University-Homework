using System;
 
class MainClass {

  public static void Main (string[] args) {
    Func<int> F = BuildFibonacci();
    for(int i = 0; i < 40; i++){
      Console.WriteLine(F());
    }
  }
 
 
  static Func<int> BuildFibonacci(){
    int a = 0;
    int b = 1;
    return () => {
      int temp = a + b;
      a = b;
      b = temp;
      return b - a;
    };
  }
}