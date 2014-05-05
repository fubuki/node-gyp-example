var assert = require('assert');
var hello = require('./build/Release/hello');
assert.equal('world', hello.hello());
console.log('hello.hello() =', hello.hello());


console.log('hello.detect(123) =', hello.detect(123));

console.log('hello.detect([]) =', hello.detect([]));