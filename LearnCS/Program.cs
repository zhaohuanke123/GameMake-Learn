using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        // 调用一个示例方法
        MyMethod();
    }

    static void MyMethod()
    {
        // 获取当前调用堆栈
        StackTrace stackTrace = new StackTrace();

        // 遍历堆栈帧信息
        for (int i = 0; i < stackTrace.FrameCount; i++)
        {
            StackFrame? stackFrame = stackTrace.GetFrame(i);
            Console.WriteLine($"Method: {stackFrame?.GetMethod()}"); // 获取方法信息
            Console.WriteLine($"File: {stackFrame?.GetFileName()}"); // 获取文件名
            Console.WriteLine($"Line: {stackFrame?.GetFileLineNumber()}"); // 获取行号
            Console.WriteLine();
        }
    }
}