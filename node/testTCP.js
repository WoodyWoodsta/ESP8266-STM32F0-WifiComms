/*  
  Very simple TCP client to test host/server capabilities 
  of the ESP8266 wifi module.
*/

var net = require('net'); // Load up the required library for TCP stuff

// Create a new TCP socket 
var client = new net.Socket(); 
client.connect(1337, '192.168.1.189', function() { // Connect to the chip
  console.log('Connected');
  client.write('Hello, server! Love, Client. This is a really long stringHello, server! Love, Client. This is a really long stringHello, server! Love, Client. This is a really long stringHello, server! Love, Client. This is a really long stringHello, server! Love, Client. This is a really long string'); // Send some text
  // client.write('This is really really cool!\r\n') // Send some more text
  // console.log('Test string sent');
  // client.write('LEDs ON\r\n');
  // console.log('LEDs On command sent');
  // client.write('LEDs OFF\r\n');
  // console.log('LEDs Off command sent');
});
 
// When data is recieved, call "data()"
client.on('data', data);

// When connection is closed, let us know
client.on('close', function() {
  console.log('Connection closed');
});

// Callback upon receiving data from the server
function data(data) {
  console.log('Received: ' + data);
  // client.destroy(); // kill client after server's response
}