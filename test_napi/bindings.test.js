"use strict";

function requireEverytime(mod) {
  delete require.cache[require.resolve(mod)];
  return require(mod);
}

describe("happy path", () => {
  it("should run", () => {
    const bindings = requireEverytime(
      "../build/Debug/napi_edge_nativeclr.node"
    );
    const result = bindings.myFunction("test");
    expect(result).toBe("test");
  });
});
