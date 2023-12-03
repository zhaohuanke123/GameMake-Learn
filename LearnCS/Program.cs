using System;
using System.Diagnostics;

class Program : IA, IB
{
    static void Main()
    {
        var p = new Program();
        ((IA)p).MyMethod();
        ((IB)p).MyMethod();
    }
    
    void IA.MyMethod()
    {
        Console.WriteLine("Hello World!");
    }

    void IB.MyMethod()
    {
        Console.WriteLine("Hello World!");
    }
}

public interface IA
{
  public  void MyMethod();
}

public interface IB
{
   public void MyMethod();
}