var assert = require('assert');
var hello = require('./build/Release/hello');
assert.equal('world', hello.hello());
console.log('hello.hello() =', hello.hello());