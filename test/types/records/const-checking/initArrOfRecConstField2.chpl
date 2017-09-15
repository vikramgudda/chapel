record R {
  const c: int;
  var v: int;
}

class C  {
  var A: [1..3] R;

  proc init() {
    var myR = new R(c=1, v=2);
    A = [myR, myR, myR];
    super.init();
  }
}

var myC = new C();

writeln(myC);

delete myC;
