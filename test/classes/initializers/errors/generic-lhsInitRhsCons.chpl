// Verify behavior when the type with an initializer is generic,
// but the type with a constructor is concrete
class hasInit {
  var x;

  proc init(xVal) {
    x = xVal;
  }
}

class hasConstruct {
  var x: int;

  proc hasConstruct(xVal) {
    x = xVal;
  }
}


var hi: borrowed hasInit(int) = new borrowed hasConstruct(10);
writeln(hi);
