var assert = require('assert');
var hello = require('./build/Release/hello');
assert.equal('world', hello.hello());
console.log('hello.hello() =', hello.hello());


console.log('hello.detect(123) =', hello.detect(123));

console.log('hello.detect([]) =', hello.detect([]));

console.log('hello.plusNumber(3) =', hello.plusNumber(3));

var buffer = new Buffer(16);

console.log('hello.length(3) =', hello.length(buffer));

console.log('hello.transfer() =', hello.transfer());

console.log('hello.add(1, 3) =', hello.add(1, 3));