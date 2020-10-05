using System;
 
class MainClass {
 
    const int MAX_PRIME = 100000000;
    static bool[] banned = new bool[MAX_PRIME + 1];
 
    public static void Main (string[] args) {
        var F = BuildPrimeFinder();
        while(true){
          int prime = F();
          if(prime == -1) break;
          Console.WriteLine(prime);
        }
  }
 
 
  static Func<int> BuildPrimeFinder(){
    int i = 1;
 
    return () => {
        if(i >= MAX_PRIME) return -1;
        while(i < MAX_PRIME && banned[++i]);
        int c = 1;
        while(i * c < MAX_PRIME){
            banned[i * c] = true;
            c++;
        }
        return i;
    };
  }
}