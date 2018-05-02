"use strict";

const bindings = require("./build/Debug/napi_edge_nativeclr.node");

console.log(bindings);

const code = `
namespace EdgeJS {
  public class StartUp {
    public static void Invoke() {
      System.Console.WriteLine("Hello from Invoke");
    }
  }
}
`;

const code2 = `
namespace EdgeJS {
  public class StartUp {
    public static void Invoke() {
      System.Console.WriteLine("Hello from Invoke");
      System.Windows.Forms.SendKeys.SendWait("OLAOLAOLA");
    }
  }
}
`;

bindings.initializeClrFunc(code2);
